#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "redc_math.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

static SDL_Renderer *renderer = nullptr;


static void draw_pixel(vec2f pos, vec3i color) {
    SDL_SetRenderDrawColor(renderer, color.x, color.y, color.z, 255);
    SDL_RenderPoint(renderer, pos.x, pos.y);
}

static void draw_line_dda(vec2f start, vec2f end, vec3i color) {
    const vec2f delta = sub_vec2f(end, start);
    const int steps = max((int) fabsf(delta.x), (int) fabsf(delta.y));
    const vec2f increment = div_vec2f_scaler(delta, (float) steps);

    vec2f temp_pos = start;
    for (int i = 0; i <= steps; i++) {
        draw_pixel(temp_pos, color);
        temp_pos = add_vec2f(temp_pos, increment);
    }
}

int main(int argc, char *argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init Error: %s", SDL_GetError());
        return 1;
    }

    SDL_Window *window = nullptr;
    if (!SDL_CreateWindowAndRenderer("RedC Renderer", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer)) {
        SDL_Log("Window/Renderer Creation Error: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (int i = 0; i < 128; i++) {
            vec2f start = {
                .x = gen_random_float_range(0.0f, (float) WINDOW_WIDTH),
                .y = gen_random_float_range(0.0f, (float) WINDOW_HEIGHT)
            };
            vec2f end = {
                .x = gen_random_float_range(0.0f, (float) WINDOW_WIDTH),
                .y = gen_random_float_range(0.0f, (float) WINDOW_HEIGHT)
            };
            vec3i color = {
                .x = gen_random_int_range(0, 256),
                .y = gen_random_int_range(0, 256),
                .z = gen_random_int_range(0, 256)
            };

            draw_line_dda(start, end, color);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
