#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>

bool is_running = false;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

int const window_width = 800;
int const window_height = 600;
int const number_of_pixels = window_width * window_height;
uint32_t const pixels_colors_size = sizeof(int32_t) * number_of_pixels;

uint32_t *pixels_colors = NULL;
SDL_Texture *pixels_colors_texture = NULL;

void destroy_window(void);

void render_color_buffer();

void draw_grid();

bool initialize_application_window(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        return false;
    }

    window = SDL_CreateWindow(
            NULL,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            window_width,
            window_height,
            SDL_WINDOW_BORDERLESS
    );
    if (!window) {
        fprintf(stderr, "Error creating SDL window.\n");
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fprintf(stderr, "Error creating SDL renderer.\n");
        return false;
    }

    return true;
}

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

void process_input(void) {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            is_running = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                is_running = false;
            break;
    }
}

void update(void) {
    // TODO:
}

void clear_pixels_colors(void) {
    memset(
            pixels_colors, 0, pixels_colors_size
    );
}

void render(void) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);

    draw_grid();
    render_color_buffer();
    clear_pixels_colors();

    SDL_RenderPresent(renderer);
}

void draw_grid(void) {
    for(int y=0; y < window_height; y+=10){
        for(int x=0; x < window_width; x+=10)
            pixels_colors[(window_width * y) + x ] = 0xFFFF0000;
    }
}

void render_color_buffer() {
    SDL_UpdateTexture(
            pixels_colors_texture,
            NULL,
            pixels_colors,
            (int) (window_width * sizeof(uint32_t))
            );

    SDL_RenderCopy(
            renderer,
            pixels_colors_texture,
            NULL,
            NULL
            );
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

void destroy_window() {
    free(pixels_colors);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
