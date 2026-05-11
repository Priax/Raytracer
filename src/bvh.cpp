/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** bvh
*/

#include "bvh.hpp"
#include <limits>

bvh_node::bvh_node(hittable_list list)
    : bvh_node(list.objects, 0, list.objects.size())
{
}

bvh_node::bvh_node(std::vector<std::shared_ptr<hittable>>& objects, size_t start, size_t end)
{
    bbox = Boxes::empty;
    for (size_t i = start; i < end; i++)
        bbox = Boxes(bbox, objects[i]->bounding_box());

    size_t span = end - start;

    if (span == 1) {
        left = right = objects[start];
    } else if (span == 2) {
        left = objects[start];
        right = objects[start + 1];
    } else {
        // SAH (Surface Area Heuristic) split
        static const int N_BUCKETS = 12;

        struct BucketInfo {
            int count = 0;
            Boxes bbox = Boxes::empty;
        };

        double best_cost = std::numeric_limits<double>::infinity();
        int best_axis = 0;
        int best_bucket = 0;
        double parent_area = bbox.surface_area();

        for (int try_axis = 0; try_axis < 3; try_axis++) {
            const interval& ax = bbox.axis_interval(try_axis);
            if (ax.size() < 1e-10) continue;

            BucketInfo buckets[N_BUCKETS];
            for (size_t i = start; i < end; i++) {
                const Boxes& obj_bbox = objects[i]->bounding_box();
                double centroid = (obj_bbox.axis_interval(try_axis).min
                                 + obj_bbox.axis_interval(try_axis).max) * 0.5;
                int b = static_cast<int>(N_BUCKETS * (centroid - ax.min) / ax.size());
                if (b < 0) b = 0;
                if (b >= N_BUCKETS) b = N_BUCKETS - 1;
                buckets[b].count++;
                buckets[b].bbox = Boxes(buckets[b].bbox, obj_bbox);
            }

            // Left-to-right sweep: cumulative area and count
            double left_area[N_BUCKETS - 1];
            int    left_count[N_BUCKETS - 1];
            Boxes  left_bbox = Boxes::empty;
            int    left_cnt  = 0;
            for (int i = 0; i < N_BUCKETS - 1; i++) {
                left_bbox    = Boxes(left_bbox, buckets[i].bbox);
                left_cnt    += buckets[i].count;
                left_area[i]  = left_bbox.surface_area();
                left_count[i] = left_cnt;
            }

            // Right-to-left sweep
            double right_area[N_BUCKETS - 1];
            int    right_count[N_BUCKETS - 1];
            Boxes  right_bbox = Boxes::empty;
            int    right_cnt  = 0;
            for (int i = N_BUCKETS - 1; i > 0; i--) {
                right_bbox       = Boxes(right_bbox, buckets[i].bbox);
                right_cnt       += buckets[i].count;
                right_area[i-1]  = right_bbox.surface_area();
                right_count[i-1] = right_cnt;
            }

            // Evaluate SAH cost for each candidate split (C_trav=0.125, C_isect=1.0)
            for (int i = 0; i < N_BUCKETS - 1; i++) {
                if (left_count[i] == 0 || right_count[i] == 0) continue;
                double cost = 0.125
                    + (left_area[i]  * left_count[i]
                    +  right_area[i] * right_count[i]) / parent_area;
                if (cost < best_cost) {
                    best_cost   = cost;
                    best_axis   = try_axis;
                    best_bucket = i;
                }
            }
        }

        // Partition objects around the chosen bucket boundary
        const interval& best_ax = bbox.axis_interval(best_axis);
        auto mid_it = std::partition(objects.begin() + start, objects.begin() + end,
            [&](const std::shared_ptr<hittable>& obj) {
                const Boxes& obj_bbox = obj->bounding_box();
                double centroid = (obj_bbox.axis_interval(best_axis).min
                                 + obj_bbox.axis_interval(best_axis).max) * 0.5;
                int b = static_cast<int>(N_BUCKETS * (centroid - best_ax.min) / best_ax.size());
                if (b < 0) b = 0;
                if (b >= N_BUCKETS) b = N_BUCKETS - 1;
                return b <= best_bucket;
            });

        size_t mid = static_cast<size_t>(mid_it - objects.begin());
        if (mid == start || mid == end)
            mid = start + span / 2;

        left  = std::make_shared<bvh_node>(objects, start, mid);
        right = std::make_shared<bvh_node>(objects, mid, end);
    }
}

// Returns the ray entry t into the box, or +inf if no intersection within ray_t.
static double aabb_t_near(const Boxes& box, const ray& r, interval ray_t)
{
    const vec3& inv = r.inv_dir();
    for (int axis = 0; axis < 3; axis++) {
        const interval& ax = box.axis_interval(axis);
        double t0 = (ax.min - r.origin()[axis]) * inv[axis];
        double t1 = (ax.max - r.origin()[axis]) * inv[axis];
        if (t0 > t1) std::swap(t0, t1);
        if (t0 > ray_t.min) ray_t.min = t0;
        if (t1 < ray_t.max) ray_t.max = t1;
        if (ray_t.max <= ray_t.min)
            return std::numeric_limits<double>::infinity();
    }
    return ray_t.min;
}

bool bvh_node::hit(const ray& r, interval ray_t, hit_record& rec) const
{
    if (!bbox.hit(r, ray_t))
        return false;

    const Boxes left_box  = left->bounding_box();
    const Boxes right_box = right->bounding_box();

    double t_left  = aabb_t_near(left_box,  r, ray_t);
    double t_right = aabb_t_near(right_box, r, ray_t);

    const bool has_left  = t_left  < std::numeric_limits<double>::infinity();
    const bool has_right = t_right < std::numeric_limits<double>::infinity();

    if (!has_left && !has_right) return false;
    if (!has_left)  return right->hit(r, ray_t, rec);
    if (!has_right) return left->hit(r, ray_t, rec);

    // Both children's AABBs intersect: visit the nearer child first.
    // The first hit tightens the interval, often allowing the farther child to be
    // rejected immediately by its own bbox test.
    const std::shared_ptr<hittable>& first  = (t_left <= t_right) ? left  : right;
    const std::shared_ptr<hittable>& second = (t_left <= t_right) ? right : left;

    bool h1 = first->hit(r, ray_t, rec);
    bool h2 = second->hit(r, interval(ray_t.min, h1 ? rec.t : ray_t.max), rec);
    return h1 || h2;
}

Boxes bvh_node::bounding_box() const
{
    return bbox;
}

int bvh_node::max_depth() const {
    auto depth_of = [](const std::shared_ptr<hittable>& h) -> int {
        auto n = std::dynamic_pointer_cast<bvh_node>(h);
        return n ? n->max_depth() : 0;
    };
    return 1 + std::max(depth_of(left), depth_of(right));
}

size_t bvh_node::node_count() const {
    auto count_of = [](const std::shared_ptr<hittable>& h) -> size_t {
        auto n = std::dynamic_pointer_cast<bvh_node>(h);
        return n ? n->node_count() : 1;
    };
    return 1 + count_of(left) + count_of(right);
}

bool bvh_node::box_compare(const std::shared_ptr<hittable>& a, const std::shared_ptr<hittable>& b, int axis)
{
    return a->bounding_box().axis_interval(axis).min < b->bounding_box().axis_interval(axis).min;
}

// ─── FlatTriangle ─────────────────────────────────────────────────────────────

bool FlatTriangle::hit(const ray& r, interval ray_t, hit_record& rec) const
{
    vec3 edge1 = v1 - v0;
    vec3 edge2 = v2 - v0;
    vec3 h = r.direction().cross(edge2);
    double a = edge1.dot(h);

    if (fabs(a) < 1e-8)
        return false;

    double f = 1.0 / a;
    vec3 s = r.origin() - v0;
    double u = f * s.dot(h);
    if (u < 0.0 || u > 1.0) return false;

    vec3 q = s.cross(edge1);
    double v = f * r.direction().dot(q);
    if (v < 0.0 || u + v > 1.0) return false;

    double t = f * edge2.dot(q);
    if (!ray_t.surrounds(t)) return false;

    rec.t = t;
    rec.p = r.at(t);
    rec.set_face_normal(r, normal);
    rec.mat = mat;

    if (has_uvs) {
        double w = 1.0 - u - v;
        rec.u = w * uv0.x() + u * uv1.x() + v * uv2.x();
        rec.v = w * uv0.y() + u * uv1.y() + v * uv2.y();
    } else {
        rec.u = u;
        rec.v = v;
    }
    return true;
}

// ─── LinearBVH – build (SAH, DFS pre-order) ──────────────────────────────────

int LinearBVH::build(std::vector<std::shared_ptr<hittable>>& objs,
                     size_t start, size_t end)
{
    int node_idx = (int)nodes.size();
    nodes.push_back({});               // Reserve slot; will be filled below

    // Bounding box of this range
    Boxes bounds = Boxes::empty;
    for (size_t i = start; i < end; i++)
        bounds = Boxes(bounds, objs[i]->bounding_box());

    size_t span = end - start;

    if (span <= 2) {
        int prim_offset = (int)prims.size();
        for (size_t i = start; i < end; i++) {
            auto tri = std::dynamic_pointer_cast<triangle>(objs[i]);
            if (tri) {
                prims.emplace_back(*tri);
                mat_owner.push_back(tri->get_mat());
            }
        }
        nodes[node_idx] = {bounds, prim_offset, (uint16_t)span, 0, 0};
        return node_idx;
    }

    static const int N_BUCKETS = 12;
    struct BucketInfo { int count = 0; Boxes bbox = Boxes::empty; };

    double best_cost   = std::numeric_limits<double>::infinity();
    int    best_axis   = 0;
    int    best_bucket = 0;
    double parent_area = bounds.surface_area();

    for (int try_axis = 0; try_axis < 3; try_axis++) {
        const interval& ax = bounds.axis_interval(try_axis);
        if (ax.size() < 1e-10) continue;

        BucketInfo buckets[N_BUCKETS];
        for (size_t i = start; i < end; i++) {
            const Boxes obj_bbox = objs[i]->bounding_box();
            double centroid = (obj_bbox.axis_interval(try_axis).min
                             + obj_bbox.axis_interval(try_axis).max) * 0.5;
            int b = static_cast<int>(N_BUCKETS * (centroid - ax.min) / ax.size());
            if (b < 0) b = 0;
            if (b >= N_BUCKETS) b = N_BUCKETS - 1;
            buckets[b].count++;
            buckets[b].bbox = Boxes(buckets[b].bbox, obj_bbox);
        }

        double left_area[N_BUCKETS - 1];
        int    left_count[N_BUCKETS - 1];
        Boxes  lb = Boxes::empty; int lc = 0;
        for (int i = 0; i < N_BUCKETS - 1; i++) {
            lb = Boxes(lb, buckets[i].bbox); lc += buckets[i].count;
            left_area[i] = lb.surface_area(); left_count[i] = lc;
        }

        double right_area[N_BUCKETS - 1];
        int    right_count[N_BUCKETS - 1];
        Boxes  rb = Boxes::empty; int rc = 0;
        for (int i = N_BUCKETS - 1; i > 0; i--) {
            rb = Boxes(rb, buckets[i].bbox); rc += buckets[i].count;
            right_area[i-1] = rb.surface_area(); right_count[i-1] = rc;
        }

        for (int i = 0; i < N_BUCKETS - 1; i++) {
            if (left_count[i] == 0 || right_count[i] == 0) continue;
            double cost = 0.125
                + (left_area[i]  * left_count[i]
                +  right_area[i] * right_count[i]) / parent_area;
            if (cost < best_cost) {
                best_cost = cost; best_axis = try_axis; best_bucket = i;
            }
        }
    }

    // Partition
    const interval& best_ax = bounds.axis_interval(best_axis);
    auto mid_it = std::partition(objs.begin() + start, objs.begin() + end,
        [&](const std::shared_ptr<hittable>& obj) {
            const Boxes obj_bbox = obj->bounding_box();
            double centroid = (obj_bbox.axis_interval(best_axis).min
                             + obj_bbox.axis_interval(best_axis).max) * 0.5;
            int b = static_cast<int>(N_BUCKETS * (centroid - best_ax.min) / best_ax.size());
            if (b < 0) b = 0;
            if (b >= N_BUCKETS) b = N_BUCKETS - 1;
            return b <= best_bucket;
        });

    size_t mid = static_cast<size_t>(mid_it - objs.begin());
    if (mid == start || mid == end) mid = start + span / 2;

    // Left child is always node_idx+1 in DFS pre-order (no need to store its index).
    build(objs, start, mid);
    int right_idx = build(objs, mid, end);

    nodes[node_idx] = {bounds, right_idx, 0, (uint8_t)best_axis, 0};
    return node_idx;
}

// ─── LinearBVH – constructor ──────────────────────────────────────────────────

LinearBVH::LinearBVH(hittable_list& mesh)
{
    if (mesh.objects.empty()) return;
    // Upper bound: at most N nodes (N/2 leaves + N/2-1 internal) for max-2-prim leaves
    nodes.reserve(mesh.objects.size());
    prims.reserve(mesh.objects.size());
    build(mesh.objects, 0, mesh.objects.size());
}

// ─── LinearBVH – iterative traversal ─────────────────────────────────────────

bool LinearBVH::hit(const ray& r, interval ray_t, hit_record& rec) const
{
    if (nodes.empty()) return false;

    bool hit_anything = false;
    int  stack[64];
    int  stack_ptr = 0;
    int  idx       = 0;

    while (true) {
        const Node& node = nodes[idx];

        if (!node.bounds.hit(r, ray_t)) {
            // AABB miss – pop stack
            if (stack_ptr == 0) break;
            idx = stack[--stack_ptr];
            continue;
        }

        if (node.n_prims > 0) {
            // ── Leaf: test all primitives ────────────────────────────────────
            for (int i = 0; i < node.n_prims; i++) {
                if (prims[node.offset + i].hit(r, ray_t, rec)) {
                    hit_anything = true;
                    ray_t.max = rec.t;   // Tighten interval for remaining tests
                }
            }
            if (stack_ptr == 0) break;
            idx = stack[--stack_ptr];
        } else {
            // ── Inner node: front-to-back ordering via split axis ────────────
            // Objects with smaller coordinates went left during build, so:
            //   positive ray direction → left (idx+1) is nearer → visit left first
            //   negative ray direction → right is nearer → visit right first
            if (r.direction()[node.split_axis] >= 0) {
                stack[stack_ptr++] = node.offset;   // Push right child
                idx = idx + 1;                       // Visit left child next
            } else {
                stack[stack_ptr++] = idx + 1;        // Push left child
                idx = node.offset;                   // Visit right child next
            }
        }
    }
    return hit_anything;
}

// ─── LinearBVH – bounding_box ─────────────────────────────────────────────────

Boxes LinearBVH::bounding_box() const
{
    return nodes.empty() ? Boxes::empty : nodes[0].bounds;
}
