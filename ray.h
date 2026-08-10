#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct
{
    point3 orig;
    vec3 dir;
} ray;

static inline point3 ray_origin(const ray *r)
{
    return r->orig;
}

static inline vec3 ray_direction(const ray *r)
{
    return r->dir;
}

static inline point3 ray_at(const ray *r, double t)
{
    return r->orig + t * r->dir;
    return vec3_add(r->orig, vec3_scale(r->dir, t));
}

#endif