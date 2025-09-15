#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT= 480;

int main(int argc, char* args[]){
    SDL_Window* window = NULL;

    //surface contained by window
    SDL_Surface* screen_surface = NULL;

    //initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL could not initialize! SDL_Error: %s\n", 
               SDL_GetError());
    }
    else{
        //create window
        window = SDL_CreateWindow("SDL Tutorial", 
                                  SDL_WINDOWPOS_UNDEFINED, 
                                  SDL_WINDOWPOS_UNDEFINED, 
                                  SCREEN_WIDTH, 
                                  SCREEN_HEIGHT, 
                                  SDL_WINDOW_SHOWN);

        if(window == NULL){
            printf("Window could not be created! SDL_Error: %s\n", 
                   SDL_GetError());
        }
        else{
            //Get window surface
            screen_surface = SDL_GetWindowSurface(window);

            //fill the surface with white
            SDL_FillRect(screen_surface, 
                         NULL, 
                         SDL_MapRGB(screen_surface->format, 
                                    0xFF, 
                                    0xFF, 
                                    0xFF));

            //update the surface
            SDL_UpdateWindowSurface(window);

            //hack to get the window to stay up?
            SDL_Event e;
            bool quit = false;
            while(quit == false){
                while(SDL_PollEvent(&e)){
                    if(e.type == SDL_QUIT){
                        quit = true;
                    }
                }
            }
        }
    }

    //Destroy window
    SDL_DestroyWindow(window);

    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}
