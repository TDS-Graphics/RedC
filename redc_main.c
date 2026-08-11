#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <cglm/cglm.h>

#include "math_random.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

static SDL_Renderer *renderer = nullptr;


static void draw_pixel(vec2 pos, vec3 color) {
    SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], 255);
    SDL_RenderPoint(renderer, pos[0], pos[1]);
}

static void draw_line_dda(vec2 start, vec2 end, vec3 color) {
    vec2 delta = {};
    glm_vec2_sub(end, start, delta);

    const int steps = max((int) fabsf(delta[0]), (int) fabsf(delta[1]));
    if (steps == 0) {
        draw_pixel(start, color);
    }

    vec2 increment = {};
    glm_vec2_divs(delta, (float) steps, increment);

    vec2 temp_pos = {start[0], start[1]};
    for (int i = 0; i <= steps; i++) {
        draw_pixel(temp_pos, color);
        glm_vec2_add(temp_pos, increment, temp_pos);
    }
}

static void draw_triangle(vec2 v1, vec2 v2, vec2 v3, vec3 color) {
    draw_line_dda(v1, v2, color);
    draw_line_dda(v2, v3, color);
    draw_line_dda(v3, v1, color);
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

        for (int i = 0; i < 16; i++) {
            vec2 v1 = {
                gen_random_float_range(0.0f, (float) WINDOW_WIDTH),
                gen_random_float_range(0.0f, (float) WINDOW_HEIGHT)
            };
            vec2 v2 = {
                gen_random_float_range(0.0f, (float) WINDOW_WIDTH),
                gen_random_float_range(0.0f, (float) WINDOW_HEIGHT)
            };
            vec2 v3 = {
                gen_random_float_range(0.0f, (float) WINDOW_WIDTH),
                gen_random_float_range(0.0f, (float) WINDOW_HEIGHT)
            };
            vec3 color = {
                (float) gen_random_int_range(0, 256),
                (float) gen_random_int_range(0, 256),
                (float) gen_random_int_range(0, 256)
            };

            draw_triangle(v1, v2, v3, color);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
