#include "math.h"

float fov_factor = 640; //scaleing

typedef struct {
    float x;
    float y;
} vec2_t;

typedef struct {
    float x;
    float y;
    float z;
} vec3_t;

vec2_t project(vec3_t point) {
    vec2_t projected_point = {
            .x = fov_factor * point.x / point.z,
            .y = fov_factor * point.y / point.z
    };
    return projected_point;
}

vec3_t vec3_rotate_x(vec3_t v, float angle) {
    vec3_t rotated_vector = {
            .x = v.x,
            .y = v.y * cos(angle) - v.z * sin(angle),
            .z = v.y * sin(angle) + v.z * cos(angle)
    };
    return rotated_vector;
}

vec3_t vec3_rotate_y(vec3_t v, float angle) {
    vec3_t rotated_vector = {
            .x = v.x * cos(angle) - v.z * sin(angle),
            .y = v.y,
            .z = v.x * sin(angle) + v.z * cos(angle)
    };
    return rotated_vector;
}

vec3_t vec3_rotate_z(vec3_t v, float angle) {
    vec3_t rotated_vector = {
            .x = v.x * cos(angle) - v.y * sin(angle),
            .y = v.x * sin(angle) + v.y * cos(angle),
            .z = v.z
    };
    return rotated_vector;
}