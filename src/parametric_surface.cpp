#include "parametric_surface.hpp"

parametric_surface::SurfacePoint
parametric_surface::evaluate(double u, double v) const
{
    constexpr double h = 1e-5;
    point3 P = fn(u, v);
    point3 Ph = fn(u + h, v);
    point3 Pv = fn(u, v + h);
    return { P, (Ph - P) / h, (Pv - P) / h };
}

void parametric_surface::compute_bbox()
{
    point3 mn(infinity, infinity, infinity);
    point3 mx(-infinity, -infinity, -infinity);

    for (int i = 0; i <= u_steps; i++) {
        for (int j = 0; j <= v_steps; j++) {
            point3 p = fn(double(i) / u_steps, double(j) / v_steps);
            for (int c = 0; c < 3; c++) {
                mn[c] = fmin(mn[c], p[c]);
                mx[c] = fmax(mx[c], p[c]);
            }
        }
    }
    vec3 pad(bbox_pad, bbox_pad, bbox_pad);
    bbox = Boxes(mn - pad, mx + pad);
}

void parametric_surface::build_accel()
{
    hittable_list mesh;
    mesh.objects.reserve(2 * u_steps * v_steps);

    for (int i = 0; i < u_steps; i++) {
        for (int j = 0; j < v_steps; j++) {
            double u0 = double(i)   / u_steps,  u1 = double(i+1) / u_steps;
            double v0 = double(j)   / v_steps,  v1 = double(j+1) / v_steps;

            SurfacePoint sp00 = evaluate(u0, v0);
            SurfacePoint sp10 = evaluate(u1, v0);
            SurfacePoint sp01 = evaluate(u0, v1);
            SurfacePoint sp11 = evaluate(u1, v1);

            vec3 uv00(u0, v0, 0), uv10(u1, v0, 0), uv01(u0, v1, 0), uv11(u1, v1, 0);

            auto make_normal = [](const SurfacePoint& sp) -> vec3 {
                vec3 n = sp.du.cross(sp.dv);
                double len = n.length();
                return (len > 1e-12) ? n / len : vec3(0, 1, 0);
            };
            vec3 n00 = make_normal(sp00), n10 = make_normal(sp10);
            vec3 n01 = make_normal(sp01), n11 = make_normal(sp11);

            mesh.add(std::make_shared<triangle>(
                sp00.P, sp10.P, sp11.P,
                uv00, uv10, uv11,
                n00, n10, n11,
                mat
            ));

            mesh.add(std::make_shared<triangle>(
                sp00.P, sp11.P, sp01.P,
                uv00, uv11, uv01,
                n00, n11, n01,
                mat
            ));
        }
    }

    accel = std::make_shared<LinearBVH>(mesh);
}

parametric_surface::parametric_surface(SurfaceFn fn, std::shared_ptr<material> mat, int u_steps, int v_steps, double epsilon) : fn(std::move(fn)), mat(std::move(mat)), u_steps(u_steps), v_steps(v_steps), epsilon(epsilon), bbox_pad(epsilon * 10.0)
{
    compute_bbox();
    build_accel();
}

bool parametric_surface::hit(const ray& r, interval ray_t, hit_record& rec) const
{
    if (!accel->hit(r, ray_t, rec))
        return false;

    if (!use_newton_refinement)
        return true;

    double u = rec.u, v = rec.v, t = rec.t;
    if (newton_refine(r, u, v, t)) {
        if ((fn(u, v) - r.at(t)).length_squared() < 1e-8) {
            rec.t = t;
            rec.p = r.at(t);
            rec.u = u;
            rec.v = v;
            SurfacePoint sp = evaluate(u, v);
            vec3 n = sp.du.cross(sp.dv);
            double len = n.length();
            if (len > 1e-12)
                rec.set_face_normal(r, n / len);
        }
    }
    return true;
}

Boxes parametric_surface::bounding_box() const { return bbox; }

bool parametric_surface::newton_refine(const ray& r, double& u, double& v, double& t) const
{
    const interval unit(0.0, 1.0);
    constexpr int MAX_ITER = 20;

    for (int iter = 0; iter < MAX_ITER; iter++) {
        SurfacePoint sp = evaluate(u, v);
        vec3 Fd = -r.direction();
        vec3 residual =  sp.P - r.at(t);

        if (residual.length_squared() < epsilon * epsilon)
            return (u >= 0.0 && u <= 1.0 && v >= 0.0 && v <= 1.0);

        // Cramer's rule on J = [Fu | Fv | Fd]
        double det = sp.du.dot(sp.dv.cross(Fd));
        if (fabs(det) < 1e-12) return false;

        vec3 neg_res = -residual;
        double du = neg_res.dot(sp.dv.cross(Fd)) / det;
        double dv = sp.du.dot(neg_res.cross(Fd)) / det;
        double dt = sp.du.dot(sp.dv.cross(neg_res)) / det;

        u += du;  v += dv;  t += dt;
        u = unit.clamp(u);
        v = unit.clamp(v);
    }
    return false;
}
