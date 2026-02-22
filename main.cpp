#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Drawlayer.h"
#include "Pen.h"
#include "UI.h"
#include "UICallback.h"
#include "Costumes.h"

#include <cstdio>

static SDL_Texture* makeStampTexture(SDL_Renderer* r) {
    // Simple 32x32 RGBA circle stamp
    SDL_Surface* s = SDL_CreateRGBSurfaceWithFormat(0, 32, 32, 32, SDL_PIXELFORMAT_RGBA32);
    if (!s) return nullptr;

    SDL_LockSurface(s);
    Uint32 clear = SDL_MapRGBA(s->format, 0, 0, 0, 0);
    Uint32 white = SDL_MapRGBA(s->format, 255, 255, 255, 200);

    // clear
    for (int y = 0; y < 32; ++y) {
        for (int x = 0; x < 32; ++x) {
            ((Uint32*)s->pixels)[y * 32 + x] = clear;
        }
    }

    // circle
    int cx = 16, cy = 16, rad = 12;
    for (int y = 0; y < 32; ++y) {
        for (int x = 0; x < 32; ++x) {
            int dx = x - cx;
            int dy = y - cy;
            if (dx * dx + dy * dy <= rad * rad) {
                ((Uint32*)s->pixels)[y * 32 + x] = white;
            }
        }
    }

    SDL_UnlockSurface(s);

    SDL_Texture* t = SDL_CreateTextureFromSurface(r, s);
    SDL_FreeSurface(s);
    if (t) SDL_SetTextureBlendMode(t, SDL_BLENDMODE_BLEND);
    return t;
}

int main(int argc, char** argv) {
    (void)argc; (void)argv;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::printf("SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    if ((IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)) {
        std::printf("IMG_Init failed: %s\n", IMG_GetError());
        // continue: still usable without image loading
    }

    if (TTF_Init() != 0) {
        std::printf("TTF_Init failed: %s\n", TTF_GetError());
        // continue
    }

    const int W = 1000;
    const int H = 700;

    SDL_Window* win = SDL_CreateWindow("Paint + Costumes (fixed)",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       W, H,
                                       SDL_WINDOW_SHOWN);
    if (!win) {
        std::printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!ren) {
        std::printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    // Modules
    initDrawLayer(ren, W, H);

    penInit();
    penEn();
    setPenSize(3);

    costumeINit(ren);

    haveUI(ren, W, H);

    SDL_Texture* stamp = makeStampTexture(ren);
    UIsetSpr(stamp);

    bool running = true;
    bool leftDown = false;
    int lastX = 0, lastY = 0;

    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            } else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                leftDown = true;
                lastX = e.button.x;
                lastY = e.button.y;

                // UI click always has priority
                handleUIClick(e.button.x, e.button.y);

                // Start drawing only if panel is not open
                if (!uiIsOk()) {
                    penDown();
                }
            } else if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
                leftDown = false;
                penUp();
            } else if (e.type == SDL_MOUSEMOTION) {
                if (leftDown && !uiIsOk()) {
                    int x = e.motion.x;
                    int y = e.motion.y;
                    drawLine(ren, lastX, lastY, x, y);
                    lastX = x;
                    lastY = y;
                }
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                } else if (e.key.keysym.sym == SDLK_s) {
                    // Stamp at current mouse position
                    int mx, my;
                    SDL_GetMouseState(&mx, &my);
                    onStampXY(ren, mx, my);
                }
            }
        }

        // Render
        SDL_SetRenderDrawColor(ren, 30, 30, 30, 255);
        SDL_RenderClear(ren);

        drawBkD(ren);
        drawSprite(ren);

        drawLayerPresent(ren);

        // Optional: show preview/editor frames
        drawPreview(ren);
        drawEditorPlace(ren);

        drawUI(ren);

        SDL_RenderPresent(ren);
    }

    // Cleanup
    if (stamp) SDL_DestroyTexture(stamp);

    Shutdown();
    costumeShtingdown(ren);
    freeDrawLayer();

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    return 0;
}