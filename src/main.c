#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdint.h>

#include <SDL2/SDL.h>

#include "./renderer.h"
#include "./texture.h"

bool running = false;
#define FPS  (60)
#define TICK (1000 / FPS)

SDL_Window*   win = NULL;
SDL_Renderer* ren = NULL;
SDL_Texture*  tex = NULL;

int D_WIDTH  = 0;
int D_HEIGHT = 0;

#define R_WIDTH  (1280)
#define R_HEIGHT (720)

colorbuffer* cbuffer = NULL;

unsigned deltatime = 0;
unsigned lastframe = 0;

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

    cbuffer = create_colorbuffer(R_WIDTH, R_HEIGHT); 

    if(!cbuffer) goto abort;

    srand(time(NULL));
    running = true;
abort:
    const char* err;
    err = SDL_GetError();
    printf("%s\n", err);
    return false;
}

void update(void){
    int now = SDL_GetTicks();      
    int sleeptime = now - lastframe;

    if (sleeptime > 0 && sleeptime < TICK){
       SDL_Delay(sleeptime);
    }

    deltatime = now - lastframe;
    lastframe = now;
}

void input(void){
    SDL_Event evt;
    while(SDL_PollEvent(&evt)){
        if(evt.type == SDL_QUIT || (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_ESCAPE)){
            running = false;
        }

        if(evt.type == SDL_KEYDOWN){
            SDL_Keysym key = evt.key.keysym;

            switch(key.sym){}
        }
    }
}

void blit(){
    SDL_UpdateTexture(
        tex,
        NULL,
        cbuffer->buffer,
        (int)(sizeof(uint32_t) * cbuffer->width)
    );

    SDL_Rect src_rect = {
        0, 0, R_WIDTH, R_HEIGHT
    };

    float scale_x = D_WIDTH  / (float)R_WIDTH;
    float scale_y = D_HEIGHT / (float)R_HEIGHT;

    float scale = scale_y < scale_x ? scale_x : scale_y;

    int xsize = (int)(R_WIDTH  * scale);
    int ysize = (int)(R_HEIGHT * scale);

    SDL_Rect dst_rect = {
        D_WIDTH  / 2 - (xsize / 2),
        D_HEIGHT / 2 - (ysize / 2),
        xsize,
        ysize
    };

    SDL_RenderCopy(
        ren,
        tex,
        &src_rect,
        &dst_rect
    );

    SDL_RenderPresent(
        ren
    );
}

void render(void){
    clear_color(cbuffer, BG);

    int ax = R_WIDTH / 2;
    int ay = (R_HEIGHT / 4) * 1;

    int bx = (R_WIDTH / 4) * 3;
    int by = (R_HEIGHT / 4) * 3;

    draw_line(cbuffer, ax, ay, bx, by, 0xff000000);

    ax = bx;
    ay = by;

    bx = (R_WIDTH / 4) * 1;

    draw_line(cbuffer, ax, ay, bx, by, 0xff000000);

    ax = bx;
    ay = by;

    bx = R_WIDTH / 2;
    by = (R_HEIGHT / 4) * 1;

    draw_line(cbuffer, ax, ay, bx, by, 0xff000000);
    
    blit();
}

int main(){
    init();

    while(running){
        input();
        update();
        render();
    }

    return 0;
}
