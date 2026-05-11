#ifndef PARAMETRIC_SURFACE_H
#define PARAMETRIC_SURFACE_H

#include "hittable.hpp"
#include "bvh.hpp"
#include <functional>
#include <memory>

/**
 * @brief Parametric surface defined by a user-supplied function P(u,v) → point3.
 *
 * At construction the surface is tessellated into 2*(u_steps*v_steps) triangles
 * and handed to a LinearBVH, so ray-intersection costs O(log N) instead of
 * O(N²) Newton iterations per ray.
 *
 * If use_newton_refinement is set to true, the BVH hit is used as a warm start
 * for a Newton-Raphson step that recovers the exact smooth-surface (u,v,t).
 * This is only worth enabling for mirror-like surfaces where facetting is
 * visible.
 */
class parametric_surface : public hittable {
public:
    using SurfaceFn = std::function<point3(double u, double v)>;

    /**
     * @param fn        Surface function P(u,v).
     * @param mat       Material to apply.
     * @param u_steps   Grid resolution along u (default 64).
     * @param v_steps   Grid resolution along v (default 64).
     * @param epsilon   Convergence threshold for Newton and bbox padding.
     */
    parametric_surface(
        SurfaceFn fn,
        std::shared_ptr<material> mat,
        int u_steps  = 64,
        int v_steps  = 64,
        double epsilon = 1e-6
    );

    bool  hit(const ray& r, interval ray_t, hit_record& rec) const override;
    Boxes bounding_box() const override;
    bool use_newton_refinement = false;

private:
    SurfaceFn fn;
    std::shared_ptr<material> mat;
    int u_steps, v_steps;
    double epsilon;
    double bbox_pad;
    Boxes  bbox;

    std::shared_ptr<LinearBVH> accel;

    /**
     * @brief Evaluate P(u,v) and its partial derivatives in 3 fn calls
     *        (forward differences).
     */
    struct SurfacePoint {
        point3 P;   ///< Position on surface
        vec3   du;  ///< ∂P/∂u  (forward difference)
        vec3   dv;  ///< ∂P/∂v  (forward difference)
    };
    SurfacePoint evaluate(double u, double v) const;
    void compute_bbox();
    void build_accel();

    /**
     * @brief Newton-Raphson refinement of (u,v,t).
     *
     * Solves P(u,v) - r.at(t) = 0 starting from the provided initial guess.
     * Returns true if convergence was reached within the [0,1]² domain.
     */
    bool newton_refine(const ray& r, double& u, double& v, double& t) const;
};

#endif
