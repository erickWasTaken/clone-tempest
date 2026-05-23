#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include <SDL2/SDL.h>

SDL_Window*   win = NULL;
SDL_Renderer* ren = NULL;
SDL_Texture*  tex = NULL;

int D_WIDTH  = 0;
int D_HEIGHT = 0;

#define R_WIDTH  (1280)
#define R_HEIGHT (720)

bool init(){
    bool success = !SDL_Init(SDL_INIT_EVERYTHING);  
    if(success) printf("SDL successfully initialized\n");
    else goto abort;

    SDL_DisplayMode mode;
    SDL_GetCurrentDisplayMode(0, &mode);

    D_WIDTH  = mode.w; 
    D_HEIGHT = mode.h; 

    win = SDL_CreateWindow(
        NULL, 
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        D_WIDTH,
        D_HEIGHT,
        SDL_WINDOW_BORDERLESS
    );

    if(!win) goto abort;

    ren = SDL_CreateRenderer(win, -1, 0);

    if(!ren) goto abort;

    tex = SDL_CreateTexture(
        ren,
        SDL_PIXELFORMAT_RGBA32,
        SDL_TEXTUREACCESS_STREAMING,
        R_WIDTH, 
        R_HEIGHT 
    );

    if(!tex) goto abort;

    srand(time(NULL));

abort:
    const char* err;
    err = SDL_GetError();
    printf("%s\n", err);
    return false;
}

int main(){
    init();
    printf("SUCCESSFULLY INITIALIZED!\n");
    return 0;
}
