#include "UI.h"
#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>

using namespace std ;


UIButtons extensionButton;
bool extensionPanelOpen = false;

void  drawExtensionButton(SDL_Renderer * renderer) {

    if ( extensionButton.visible == false) {
        return;
    }
   if (extensionPanelOpen == true) {

       SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
       SDL_RenderFillRect(renderer, );
       SDL_RenderDrawRect(renderer, NULL);
   }
    if (extensionPanelOpen == false) {
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x50);
        SDL_RenderFillRect(renderer, NULL);
        SDL_RenderDrawRect(renderer, NULL);
    }
}





void drawUI(SDL_Renderer * renderer) {

}















