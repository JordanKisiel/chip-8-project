#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 320 
#define DISPLAY_WIDTH 64
#define DISPLAY_HEIGHT 32

//initializes SDL, the window to draw to,
//and the renderer that will do the drawing
//returns false if any step fails
bool init(SDL_Window** window, SDL_Renderer** renderer);

//destroys created objects before program closes
bool cleanup(SDL_Window* window, SDL_Renderer* renderer);


int main(int argc, char* args[]){
    //TODO: draw a grid of pixels (randomly on or off)
    //      to emulate display

    SDL_Window* window = NULL;
    //renderer to draw pixels
    SDL_Renderer* renderer = NULL;
    SDL_Event event;

    bool init_success = init(&window, &renderer);

    if(init_success){

        //fill window with white
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        //draw a diagonal line
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        for(int i = 0; i < WINDOW_WIDTH; i++){
            SDL_RenderDrawPoint(renderer, i, i);
        }

        //show drawing
        SDL_RenderPresent(renderer);

        //keep window open until exit
        while(true){
            if(SDL_PollEvent(&event) && event.type == SDL_QUIT){
                break;
            }
        }
    }

    cleanup(window, renderer);

    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}


bool init(SDL_Window** window, SDL_Renderer** renderer){

    bool success = true;

    //initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL could not initialize! SDL_Error: %s\n",
               SDL_GetError());

        success = false;
    }

    if(success){
        //create window
        *window = SDL_CreateWindow("Chip-8-Emu",
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  WINDOW_WIDTH,
                                  WINDOW_HEIGHT,
                                  SDL_WINDOW_SHOWN);

        if(*window == NULL){
            printf("Window could not be created! SDL_Error: %s\n",
                   SDL_GetError());
            success = false;
        }
    }

    if(success){
        *renderer = SDL_CreateRenderer(*window, 
                                       -1, 
                                       SDL_RENDERER_ACCELERATED);

        if(*renderer == NULL){
            printf("Renderer could not be created! SDL_Error: %s\n",
                   SDL_GetError());
            success = false;
        }
    }

    return success;
}


bool cleanup(SDL_Window* window, SDL_Renderer* renderer){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
