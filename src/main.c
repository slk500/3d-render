#include <SDL2/SDL.h>
#include <stdint.h>
#include "display.c"
#include "input.c"
#include "vector.c"

#define N_POINTS (9 * 9 * 9) //int const - dosen't work
vec3_t cube_points[N_POINTS];
vec2_t projected_points[N_POINTS];

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
                projected_point.x + window_width / 2,
                projected_point.y + window_height / 2,
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
    for (int i=0; i < N_POINTS; i++) {
            vec3_t point = cube_points[i];
            vec2_t project_point = project(point);
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
