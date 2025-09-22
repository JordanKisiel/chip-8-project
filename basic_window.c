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

//draws rectangle representing pixels to the screen
//depending on the boolean value of the display
//array provided
void render_display(SDL_Renderer* renderer, 
                    bool display[], 
                    SDL_Color bg, 
                    SDL_Color fg);

//destroys created objects before program closes
bool cleanup(SDL_Window* window, SDL_Renderer* renderer);


int main(int argc, char* args[]){

    /*
        *TODO:
        *  -allow for colors (and other future settings)
        *   to be done through config fill
        *
        *
        *
        * 
    */

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL; //renderer does drawing
    SDL_Event exit_event; //used to keep window open until exit event
    bool display[DISPLAY_WIDTH * DISPLAY_HEIGHT] = {false};
    SDL_Color bg = {200, 200, 200, 255};
    SDL_Color fg = {45, 45, 45, 255};

    bool init_success = init(&window, &renderer);

    if(init_success){

        init_random_array(display, DISPLAY_WIDTH * DISPLAY_HEIGHT);

        render_display(renderer, display, bg, fg);

        //show display
        SDL_RenderPresent(renderer);

        //keep window open until exit
        while(true){
            if(SDL_PollEvent(&exit_event) && exit_event.type == SDL_QUIT){
                break;
            }
        }
    }

    cleanup(window, renderer);

    //quit SDL subsystems
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


void render_display(SDL_Renderer* renderer, 
                    bool display[], 
                    SDL_Color bg, 
                    SDL_Color fg){

    //seed rng with current time
    srand(time(NULL));

    //render bg
    //fill window with background color
    SDL_SetRenderDrawColor(renderer, bg.r, bg.g, bg.b, bg.a);
    SDL_RenderClear(renderer);

    //position to start drawing from
    //to center the display pixels
    int x_pos_start = (WINDOW_WIDTH / 2) - 
                      ((DISPLAY_WIDTH * DISPLAY_PIXEL_SIZE) / 2);
    int y_pos_start = (WINDOW_HEIGHT / 2) - 
                      ((DISPLAY_HEIGHT * DISPLAY_PIXEL_SIZE) / 2);

    //set color of 'pixels' to foreground color
    SDL_SetRenderDrawColor(renderer, fg.r, fg.g, fg.b, fg.a);

    //draw a rectangle (representing a pixel)
    //where ever the display has a true value
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
}


bool cleanup(SDL_Window* window, SDL_Renderer* renderer){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
