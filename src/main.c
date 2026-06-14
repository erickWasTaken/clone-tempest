#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdint.h>

// IO
#include <sys/stat.h>
#include <dlfcn.h>
#include <unistd.h>

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

const char* dll_path = "module.so";
const char* dll_load_path = "module_load.so";

typedef bool (*init_func)(int width, int height);
typedef void (*input_func)(SDL_Event evt);
typedef void (*update_func)(float time, float deltatime);
typedef void (*render_func)(colorbuffer* cbuffer);

init_func init_module;
input_func input_module;
update_func update_module;
render_func render_module;

void update_dll();

#ifdef VIEWER
#include "./modules/viewer.h"
#endif

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

    update_dll();

    srand(time(NULL));
    success &= init_module(R_WIDTH, R_HEIGHT);

    running = success;
abort:
    const char* err;
    err = SDL_GetError();
    printf("%s\n", err);
    return false;
}

long long get_file_timestamp(const char* filepath){
    struct stat filestat = {};
    stat(filepath, &filestat);
    return filestat.st_mtime;
}

size_t get_filesize(FILE* file){
    if(!file){
        printf("Could not assert file size\nNull pointer\n");
        return 0;
    }

    size_t res;
    fseek(file, 0, SEEK_END);
    res = ftell(file);
    fseek(file, 0, SEEK_SET);

    return res;
}

void read_file(FILE* file, size_t fsize, char* buffer){
    fread(buffer, sizeof(char), fsize, file);
    buffer[fsize] = '/0';
}

bool copy_file(const char* src_path, const char* dst_path){
    char errormsg[256];
    FILE* src = fopen(src_path, "r");

    if(!src){
        sprintf(errormsg, "Could not open file: %s", src_path);
        printf("%s\n", errormsg);
        // goto abort;
        return false;
    }

    size_t fsize = get_filesize(src);
    char buffer[fsize + 1];
    read_file(src, fsize, buffer);

    fclose(src);

    FILE* dst = fopen(dst_path, "w");
    if(!dst){
        sprintf(errormsg, "Could not open file: %s", dst_path);
        printf("%s\n", errormsg);
        // goto abort;
        return false;
    }

    bool success = (bool)fwrite(buffer, sizeof(char), fsize, dst);
    fclose(dst);
    if(!success){
        sprintf(errormsg, "Could not write to file: %s", dst_path);
        printf("%s\n", errormsg);
        // goto abort;
        return false;
    }

    return success; 

abort:
    printf("%s", errormsg);
    return false;
}

void* load_dynamic_function(void* dll, const char* funcname){
    void* proc = dlsym(dll, funcname);
    if(!proc){
        printf("%s\n", dlerror());
        return NULL;
    }

    return proc;
}

void update_dll(){
    static void* dll;
    static long long dlltimestamp;
    
    long long curr = get_file_timestamp(dll_path);

    if(curr > dlltimestamp){
        if(dll){
            bool closed = (bool)dlclose(dll); 
            dll = NULL;
        }

        while(!copy_file(dll_path, dll_load_path)){
            sleep(10);
        }

        char path[256];
        sprintf(path, "./%s", dll_load_path);
        dll = dlopen(path, RTLD_NOW); 

        if(!dll){
            printf("%s\n", dlerror());
            return;
        } 

        init_module   = (init_func)load_dynamic_function(dll, "module_init");
        input_module  = (input_func)load_dynamic_function(dll, "module_input");
        update_module = (update_func)load_dynamic_function(dll, "module_update");
        render_module = (render_func)load_dynamic_function(dll, "module_render");

        if(!render_module){
            printf("%s\n", dlerror());
            return;
        }

        dlltimestamp = curr;
    }
}

void update(void){
    // update dll here
    update_dll();

    int now = SDL_GetTicks();      
    int sleeptime = now - lastframe;

    if (sleeptime > 0 && sleeptime < TICK){
       SDL_Delay(sleeptime);
    }

    deltatime = now - lastframe;
    lastframe = now;

    update_module(lastframe, deltatime);
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

        input_module(evt);
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
    render_module(cbuffer);
    blit();
}

int main(){
    init();
    printf("successfully initialized all modules");

    while(running){
        input();
        update();
        render();
    }

    return 0;
}
