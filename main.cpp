#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <cstdio>
#include <cstring>

#include "types.h"
#include "globals.h"
#include "events.h"
#include "sprite.h"
#include "project.h"
#include "sound.h"
#include "operators.h"
#include "ui1.h"
#include "khoeini1.h"
#include "khoeini2.h"
#include "khoeini3.h"

static app_looks gAppLooks;
static bool gUseLooksUI = true;

static bool initSDL(void) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL init failed: %s\n", SDL_GetError());
        return false;
    }
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        printf("SDL_image init failed\n");
    }
    if (TTF_Init() < 0) {
        printf("SDL_ttf init failed: %s\n", TTF_GetError());
        return false;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer init failed: %s\n", Mix_GetError());
    }
    return true;
}

static void cleanupSDL(void) {
    if (gUseLooksUI) {
        Looks_Shutdown(&gAppLooks);
    }
    if (gFont) TTF_CloseFont(gFont);
    if (gRenderer) SDL_DestroyRenderer(gRenderer);
    if (gWindow) SDL_DestroyWindow(gWindow);
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;

    if (!initSDL()) return 1;

    gWindow = SDL_CreateWindow("Scratch-like", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
    if (!gWindow) {
        printf("Window create failed: %s\n", SDL_GetError());
        cleanupSDL();
        return 1;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!gRenderer) {
        printf("Renderer create failed: %s\n", SDL_GetError());
        cleanupSDL();
        return 1;
    }

    gFont = TTF_OpenFont("arial.ttf", 16);
    if (!gFont) {
        gFont = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 16);
    }

    initProject();

    if (gUseLooksUI) {
        Looks_Init(&gAppLooks, gRenderer, WINDOW_WIDTH, WINDOW_HEIGHT);
    }

    gRunning = true;
    Uint32 lastTicks = SDL_GetTicks();

    while (gRunning) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                gRunning = false;
            }
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
                gRunning = false;
            }

            if (gUseLooksUI) {
                Looks_HandleEvent(&gAppLooks, e);
            } else {
                gMouseX = e.type == SDL_MOUSEMOTION ? e.motion.x : gMouseX;
                gMouseY = e.type == SDL_MOUSEMOTION ? e.motion.y : gMouseY;
                if (e.type == SDL_MOUSEBUTTONDOWN) gMouseDown = true;
                if (e.type == SDL_MOUSEBUTTONUP) gMouseDown = false;
            }
        }

        Uint32 now = SDL_GetTicks();
        float dt = (now - lastTicks) / 1000.0f;
        lastTicks = now;

        if (gUseLooksUI) {
            Looks_Update(&gAppLooks, dt);
            Looks_Render(&gAppLooks);
        } else {
            render();
        }

        SDL_RenderPresent(gRenderer);
    }

    cleanupSDL();
    return 0;
}
