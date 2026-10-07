#!/usr/bin/env bash
#
# Raytracer benchmark: BVH vs brute force, OpenMP static vs dynamic.
#
# Builds an instrumented copy of src/ in a temp dir (src/ is never modified):
#   - NO_BVH=1        -> meshes go in a plain hittable_list instead of LinearBVH
#   - OMP_SCHEDULE    -> render loop uses schedule(runtime)
#   - hot-reload watcher polls every 10ms instead of 500ms (removes timing bias)
#
# Usage: bench/benchmark.sh [-n RUNS] [--quick]
#   -n RUNS   runs per configuration (default 3)
#   --quick   small scenes, low spp/depth, no bunny schedule test (~3 min)
#             default profile takes ~45 min (schedule tests use the scenes as-is)
#
# Output: bench/results/<date>/summary.txt + raw/ (one log per run)

set -euo pipefail

RUNS=3
QUICK=0
while [ $# -gt 0 ]; do
    case "$1" in
        -n) RUNS=$2; shift 2 ;;
        --quick) QUICK=1; shift ;;
        -h|--help) sed -n '3,15p' "$0" | sed 's/^# \{0,1\}//'; exit 0 ;;
        *) echo "unknown option: $1" >&2; exit 1 ;;
    esac
done

ROOT=$(cd "$(dirname "$0")/.." && pwd)
cd "$ROOT"

STAMP=$(date +%Y-%m-%d_%H%M%S)
OUT="$ROOT/bench/results/$STAMP"
RAW="$OUT/raw"
SUMMARY="$OUT/summary.txt"
mkdir -p "$RAW"

TMP=$(mktemp -d)
trap 'rm -rf "$TMP"' EXIT
BIN="$TMP/raytracer_bench"

echo "Building instrumented copy..." >&2
cp -r src "$TMP/src"

sed -i 's/schedule(dynamic, 1)/schedule(runtime)/' "$TMP/src/camera.cpp"
sed -i 's/auto lbvh = std::make_shared<LinearBVH>(mesh);/std::shared_ptr<hittable> lbvh = getenv("NO_BVH") ? std::static_pointer_cast<hittable>(std::make_shared<hittable_list>(mesh)) : std::static_pointer_cast<hittable>(std::make_shared<LinearBVH>(mesh));/' "$TMP/src/new_parser.cpp"
sed -i '0,/milliseconds(500)/s//milliseconds(10)/' "$TMP/src/main.cpp"

grep -q 'schedule(runtime)' "$TMP/src/camera.cpp" \
    || { echo "patch failed: schedule pragma not found in camera.cpp" >&2; exit 1; }
[ "$(grep -c 'getenv("NO_BVH")' "$TMP/src/new_parser.cpp")" -ge 1 ] \
    || { echo "patch failed: LinearBVH construction not found in new_parser.cpp" >&2; exit 1; }

SRCS=$(sed -n '/^SRC =/,/^$/p' Makefile | grep -o 'src/[^ ]*\.cpp' | sed "s|^|$TMP/|")
g++ -W -Wall -Wextra -O2 -fopenmp -o "$BIN" $SRCS \
    -lconfig++ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio 2>"$TMP/build.log" \
    || { cat "$TMP/build.log" >&2; exit 1; }

# scene_variant NAME SOURCE [WIDTH HEIGHT SPP DEPTH]  (no params = scene as-is)
scene_variant() {
    if [ $# -eq 2 ]; then cp "scenes/$2.cfg" "$TMP/$1.cfg"; return; fi
    sed -E "s/width = [0-9]+, height = [0-9]+/width = $3, height = $4/; s/rate = [0-9.]+/rate = $5.0/; s/max = [0-9.]+/max = $6.0/" \
        "scenes/$2.cfg" > "$TMP/$1.cfg"
}
# BVH tests stay at low resolution: without BVH every ray tests every triangle.
if [ "$QUICK" -eq 1 ]; then
    scene_variant teapot_bench   teapot     160 120  4 5
    scene_variant bunny_bench    bunny_only 120  90  1 3
    scene_variant showcase_sched showcase   300 300 16 8
else
    scene_variant teapot_bench   teapot     200 150 16 8
    scene_variant bunny_bench    bunny_only 100  75 16 8
    scene_variant showcase_sched showcase
    scene_variant bunny_sched    bunny_only
fi

# run_series TAG SCENE ENV... -> prints one wall time per line, saves raw logs
run_series() {
    local tag=$1 scene=$2; shift 2
    local i log
    for i in $(seq 1 "$RUNS"); do
        log="$RAW/${tag}_run$i.log"
        {
            echo "\$ $* ./raytracer $scene.cfg"
            env -u NO_BVH -u OMP_SCHEDULE "$@" /usr/bin/time -f 'wall=%e user=%U sys=%S' \
                "$BIN" "$TMP/$scene.cfg" 2>&1 >/dev/null \
                | sed 's/\r/\n/g; s/\x1b\[[0-9;]*[mK]//g' | grep -v '^Rendering\.\.\.' | grep -v '^ *$'
        } > "$log"
        printf '  %-28s run %d/%d  %ss\n' "$tag" "$i" "$RUNS" \
            "$(sed -n 's/^wall=\([0-9.]*\).*/\1/p' "$log")" >&2
        sed -n 's/^wall=\([0-9.]*\).*/\1/p' "$log"
    done
}

# stats < times -> "mean min max stddev"
stats() {
    awk '{ s+=$1; ss+=$1*$1; if(NR==1||$1<mn)mn=$1; if(NR==1||$1>mx)mx=$1 }
         END { m=s/NR; v=ss/NR-m*m; if(v<0)v=0; printf "%.2f %.2f %.2f %.2f", m, mn, mx, sqrt(v) }'
}

# user CPU time of a series (mean), from raw logs
user_mean() {
    cat "$RAW/$1"_run*.log | sed -n 's/.*user=\([0-9.]*\).*/\1/p' | awk '{s+=$1} END {printf "%.1f", s/NR}'
}

load_time() {
    sed -n 's/.*in \([0-9.e-]*\)s$/\1/p' "$RAW/$1_run1.log" | awk '{s+=$1} END {printf "%.2f", s}'
}

triangles() {
    sed -n 's/.*→ \([0-9]*\) triangles/\1/p' "$RAW/$1_run1.log" | head -1
}

# "800x600, 9 spp, depth 3" as reported by the renderer itself
render_params() {
    sed -n 's/^Rendering \([0-9x]*\) spp=\([0-9]*\) depth=\([0-9]*\)$/\1, \2 spp, depth \3/p' "$RAW/$1_run1.log"
}

line() { printf '%*s\n' 72 '' | tr ' ' '-'; }

# row LABEL "mean min max sd" [EXTRA]
row() {
    read -r m mn mx sd <<< "$2"
    printf '  %-16s %8s s %8s s %8s s %7s s  %s\n' "$1" "$m" "$mn" "$mx" "$sd" "${3:-}"
}
header() { printf '  %-16s %10s %10s %10s %9s\n' "" "moyenne" "min" "max" "écart-type"; }

ratio() { awk -v a="$1" -v b="$2" 'BEGIN { printf "x%.1f", a/b }'; }

# ---------------------------------------------------------------- runs

declare -A S U
bench() { # KEY SCENE ENV...
    local key=$1; shift
    S[$key]=$(run_series "$key" "$@" | stats)
    U[$key]=$(user_mean "$key")
}

echo "Running ($RUNS runs per config)..." >&2
bench teapot_bvh       teapot_bench
bench teapot_nobvh     teapot_bench   NO_BVH=1
bench bunny_bvh        bunny_bench
bench bunny_nobvh      bunny_bench    NO_BVH=1
bench showcase_static  showcase_sched OMP_SCHEDULE=static
bench showcase_dynamic showcase_sched OMP_SCHEDULE=dynamic,1
if [ "$QUICK" -eq 0 ]; then
    bench bunny_static   bunny_sched OMP_SCHEDULE=static
    bench bunny_dynamic  bunny_sched OMP_SCHEDULE=dynamic,1
fi
[ "$QUICK" -eq 1 ] && PROFILE="quick (scènes réduites)" || PROFILE="complet"
[ "$QUICK" -eq 1 ] && SCHED_SRC="scène réduite" || SCHED_SRC="scène d'origine"


mean() { echo "${S[$1]}" | cut -d' ' -f1; }

{
    echo "RAYTRACER BENCHMARK"
    line
    printf '  %-10s %s\n' \
        date    "$(date '+%Y-%m-%d %H:%M')" \
        commit  "$(git rev-parse --short HEAD)$(git diff --quiet -- src || echo ' (+ modifs locales)')" \
        cpu     "$(lscpu | sed -n 's/^Model name: *//p') ($(nproc) threads)" \
        build   "$(g++ --version | head -1 | sed 's/ ([^)]*)//'), -O2 -fopenmp" \
        profil  "$PROFILE" \
        runs    "$RUNS par configuration, temps réel (wall clock)"
    echo

    echo "1. BVH vs LISTE BRUTE"
    line
    echo "  teapot - $(triangles teapot_bvh) triangles, $(render_params teapot_bvh)"
    header
    row "avec BVH"  "${S[teapot_bvh]}"
    row "sans BVH"  "${S[teapot_nobvh]}"
    echo "  => BVH $(ratio "$(mean teapot_nobvh)" "$(mean teapot_bvh)") plus rapide"
    echo
    echo "  bunny - $(triangles bunny_bvh) triangles, $(render_params bunny_bvh)"
    header
    row "avec BVH"  "${S[bunny_bvh]}"   "(dont $(load_time bunny_bvh)s chargement + construction BVH)"
    row "sans BVH"  "${S[bunny_nobvh]}"
    echo "  => BVH $(ratio "$(mean bunny_nobvh)" "$(mean bunny_bvh)") plus rapide"
    echo

    echo "2. OPENMP SCHEDULE (boucle sur les lignes)"
    line
    echo "  showcase ($SCHED_SRC) - $(render_params showcase_static)"
    header
    row "static"     "${S[showcase_static]}"  "cpu user ${U[showcase_static]}s"
    row "dynamic,1"  "${S[showcase_dynamic]}" "cpu user ${U[showcase_dynamic]}s"
    echo "  => dynamic $(ratio "$(mean showcase_static)" "$(mean showcase_dynamic)") plus rapide"
    if [ "$QUICK" -eq 0 ]; then
        echo
        echo "  bunny ($SCHED_SRC) - $(render_params bunny_static)"
        header
        row "static"     "${S[bunny_static]}"  "cpu user ${U[bunny_static]}s"
        row "dynamic,1"  "${S[bunny_dynamic]}" "cpu user ${U[bunny_dynamic]}s"
        echo "  => dynamic $(ratio "$(mean bunny_static)" "$(mean bunny_dynamic)") plus rapide"
    fi
    echo

    echo "RÉSUMÉ"
    line
    printf '  %-34s %10s %10s %9s\n' "test" "avant" "après" "gain"
    printf '  %-34s %9ss %9ss %9s\n' "teapot: sans BVH -> BVH" \
        "$(mean teapot_nobvh)" "$(mean teapot_bvh)" "$(ratio "$(mean teapot_nobvh)" "$(mean teapot_bvh)")"
    printf '  %-34s %9ss %9ss %9s\n' "bunny: sans BVH -> BVH" \
        "$(mean bunny_nobvh)" "$(mean bunny_bvh)" "$(ratio "$(mean bunny_nobvh)" "$(mean bunny_bvh)")"
    printf '  %-34s %9ss %9ss %9s\n' "showcase: static -> dynamic,1" \
        "$(mean showcase_static)" "$(mean showcase_dynamic)" "$(ratio "$(mean showcase_static)" "$(mean showcase_dynamic)")"
    if [ "$QUICK" -eq 0 ]; then
        printf '  %-34s %9ss %9ss %9s\n' "bunny: static -> dynamic,1" \
            "$(mean bunny_static)" "$(mean bunny_dynamic)" "$(ratio "$(mean bunny_static)" "$(mean bunny_dynamic)")"
    fi
    echo
    echo "  logs bruts : bench/results/$STAMP/raw/"
} | tee "$SUMMARY"
