#include <SDL2/SDL.h>
#include <stdint.h>
#include "display.c"
#include "input.c"
#include "vector.c"

#define N_POINTS (9 * 9 * 9) //int const - dosen't work
vec3_t cube_points[N_POINTS];
vec2_t projected_points[N_POINTS];

vec3_t camera_position = {.x = 0, .y = 0, .z = -5 };
vec3_t cube_rotation = {.x = 0, .y = 0, .z = 0 };

void setup(void) {
    pixels_colors = (uint32_t *) malloc(pixels_colors_size);
    pixels_colors_texture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_ABGR8888,
            SDL_TEXTUREACCESS_STREAMING,
            window_width,
            window_height
            );

    int point_count = 0;

    for (float x = -1; x <= 1; x += 0.25) {
        for (float y = -1; y <= 1; y += 0.25) {
            for (float z = -1; z <= 1; z += 0.25) {
                vec3_t new_point = { .x = x, .y = y, .z = z };
                cube_points[point_count++] = new_point;
            }
        }
    }
}

void render(void) {

    for (int i=0; i < N_POINTS; i++) {
        vec2_t projected_point = projected_points[i];
        draw_rectangle(
                projected_point.x +
                    window_width / 2, //translate
                projected_point.y +
                    window_height / 2, //translate
                4,
                4,
                0xFFFFFF00
                );
    }

    render_pixels();
    clear_pixels_colors();

    SDL_RenderPresent(renderer);
}

void update(void) {
    cube_rotation.y += 0.01;
    cube_rotation.x += 0.01;
    cube_rotation.z += 0.01;

    for (int i=0; i < N_POINTS; i++) {
            vec3_t point = cube_points[i];
            vec3_t transformed_point = vec3_rotate_y(point, cube_rotation.y);
            transformed_point = vec3_rotate_x(transformed_point, cube_rotation.x);
            transformed_point = vec3_rotate_z(transformed_point, cube_rotation.z);

            //translate the points away from the camera
            transformed_point.z -= camera_position.z;
            vec2_t project_point = project(transformed_point);
            projected_points[i] = project_point;
    }
}

int main(void) {
    is_running = initialize_application_window();

    setup();

    while (is_running) {
        process_input();
        update();
        render();
    }

    destroy_window();

    return 0;
}
