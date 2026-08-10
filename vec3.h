#ifndef VEC3_H
#define VEC3_H

#include <math.h>
#include <stdio.h>

typedef struct
{
    double e[3];
} vec3;

static inline vec3 vec3_zero(void)
{
    return (vec3){ {0.0, 0.0, 0.0} };
}

static inline vec3 vec3_init(double e0, double e1, double e2)
{
    return (vec3){ {e0, e1, e2} };
}




static inline double vec3_x(vec3 v) { return v.e[0]; }
static inline double vec3_y(vec3 v) { return v.e[1]; }
static inline double vec3_z(vec3 v) { return v.e[2]; }




static inline vec3 vec3_neg(vec3 v)
{
    return (vec3){ {-(v.e[0]), -(v.e[1]), -(v.e[2])} };
}

static inline void vec3_inplace_add(vec3 *u, vec3 v)
{
    u->e[0] += v.e[0];
    u->e[1] += v.e[1];
    u->e[2] += v.e[2];
}

static inline void vec3_inplace_mul(vec3 *v, double t)
{
    v->e[0] *= t;
    v->e[1] *= t;
    v->e[2] *= t;
}

static inline void vec3_inplace_div(vec3 *v, double t)
{
    vec3_inplace_mul(v, 1.0 / t);
}




static inline double vec3_length_squared(vec3 v)
{
    return v.e[0] * v.e[0] + v.e[1] * v.e[1] + v.e[2] * v.e[2];
}

static inline double vec3_length(vec3 v)
{
    return sqrt(vec3_length_squared(v));
}




typedef vec3 point3;

static inline void vec3_print(FILE *stream, vec3 v)
{
    fprintf(stream, "%f %f %f", v.e[0], v.e[1], v.e[2]);
}

static inline vec3 vec3_add(vec3 u, vec3 v)
{
    return (vec3){ {u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]} };
}

static inline vec3 vec3_sub(vec3 u, vec3 v)
{
    return (vec3){ {u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]} };
}

static inline vec3 vec3_mul(vec3 u, vec3 v)
{
    return (vec3){ {u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]} };
}

static inline vec3 vec3_scale(vec3 v, double t)
{
    return (vec3){ {v.e[0] * t, v.e[1] * t, v.e[2] * t} };
}

static inline vec3 vec3_div(vec3 v, double t)
{
    return vec3_scale(v, 1/t);
}

static inline double vec3_dot(vec3 u, vec3 v)
{
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

static inline vec3 vec3_cross(vec3 u, vec3 v)
{
    return (vec3){ {u.e[1] * v.e[2] - u.e[2] * v.e[1],
                    u.e[2] * v.e[0] - u.e[0] * v.e[2],
                    u.e[0] * v.e[1] - u.e[1] * v.e[0]} };
}

static inline vec3 vec3_unit(vec3 v)
{
    return vec3_div(v, vec3_length(v));
}

#endif