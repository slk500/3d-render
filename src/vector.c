float fov_factor = 120;

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
            .x = fov_factor * point.x,
            .y = fov_factor * point.y
    };
    return projected_point;
}