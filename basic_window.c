#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 320 
#define DISPLAY_WIDTH 64
#define DISPLAY_HEIGHT 32
#define DISPLAY_PIXEL_SIZE 10

//initializes SDL, the window to draw to,
//and the renderer that will do the drawing
//returns false if any step fails 
bool init(SDL_Window** window, SDL_Renderer** renderer);

//fills an array with random boolean values
void init_random_array(bool* buffer, int count);

//destroys created objects before program closes
bool cleanup(SDL_Window* window, SDL_Renderer* renderer);


int main(int argc, char* args[]){

    //**TODO**
    //   -clean code up into functions

    SDL_Window* window = NULL;
    //renderer to draw pixels
    SDL_Renderer* renderer = NULL;
    SDL_Event event;
    srand(time(NULL)); //seed rng with current time
    bool display[DISPLAY_WIDTH * DISPLAY_HEIGHT] = {false};

    bool init_success = init(&window, &renderer);

    if(init_success){

        //fill window with white
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        
        init_random_array(display, DISPLAY_WIDTH * DISPLAY_HEIGHT);

        //position to start drawing from
        //to center the display pixels
        int x_pos_start = (WINDOW_WIDTH / 2) - 
                          ((DISPLAY_WIDTH * DISPLAY_PIXEL_SIZE) / 2);
        int y_pos_start = (WINDOW_HEIGHT / 2) - 
                          ((DISPLAY_HEIGHT * DISPLAY_PIXEL_SIZE) / 2);

        //set color of 'pixels' to black
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        for(int i = 0; i < DISPLAY_WIDTH; i++){
            for(int j = 0; j < DISPLAY_HEIGHT; j++){

                //draw display
                SDL_Rect rect = {.x = i * DISPLAY_PIXEL_SIZE, 
                                 .y = j * DISPLAY_PIXEL_SIZE, 
                                 .w = DISPLAY_PIXEL_SIZE, 
                                 .h = DISPLAY_PIXEL_SIZE};

                if(display[j + (i * DISPLAY_HEIGHT)]){
                    SDL_RenderFillRect(renderer, &rect);
                    SDL_RenderDrawRect(renderer, &rect);
                }
            }
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

void init_random_array(bool* buffer, int count){
    for(int i = 0; i < count; i++){
        int random_num = rand();
        buffer[i] = random_num > RAND_MAX / 2 ? true : false;
    }
}


bool cleanup(SDL_Window* window, SDL_Renderer* renderer){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
