#include <SDL2/SDL.h>
#include <stdint.h>
#include "display.c"
#include "input.c"

void setup(void) {
    pixels_colors = (uint32_t *) malloc(pixels_colors_size);
    pixels_colors_texture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_ABGR8888,
            SDL_TEXTUREACCESS_STREAMING,
            window_width,
            window_height
            );
}

int main(void) {
    is_running = initialize_application_window();

    setup();

    while (is_running) {
        process_input();
        render();
    }

    destroy_window();

    return 0;
}
