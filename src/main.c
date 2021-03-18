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

uint32_t *pixels_colors = NULL;

void destroy_window(void);

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
    pixels_colors = (uint32_t *) malloc(sizeof(int32_t) * number_of_pixels);
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

void render(void) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);

    //...

    SDL_RenderPresent(renderer);
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
