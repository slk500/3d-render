#include <stdbool.h>

int const window_width = 800;
int const window_height = 600;
int const number_of_pixels = window_width * window_height;
uint32_t const pixels_colors_size = sizeof(int32_t) * number_of_pixels;

uint32_t *pixels_colors = NULL;
SDL_Texture *pixels_colors_texture = NULL;

bool is_running = false;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

void destroy_window(void);
void render_color_buffer();
void draw_grid();
void draw_rectangle();

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


void clear_pixels_colors(void) {
    memset(
            pixels_colors, 0, pixels_colors_size
    );
}

void render(void) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);

    draw_grid();
    draw_rectangle(200,300,100,100,0xFFFF00);
    render_color_buffer();
    clear_pixels_colors();

    SDL_RenderPresent(renderer);
}

void draw_pixel(int x, int y, uint32_t color) {
    pixels_colors[(window_width * y) + x] = color;
}

void draw_grid(void) {
    for(int y=0; y < window_height; y+=10){
        for(int x=0; x < window_width; x+=10)
            draw_pixel(x,y,0xFF0000);
    }
}

void draw_rectangle(int x, int y, int width, int height, uint32_t color) {
    for(int temp_y = y; temp_y <= (y + height); temp_y++) {
        for (int temp_x = x; temp_x <= (x + width); temp_x++) {
            draw_pixel(temp_x,temp_y, color);
        }
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

void destroy_window() {
    free(pixels_colors);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}