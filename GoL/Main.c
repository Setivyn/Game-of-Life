#include<stdio.h>
#include<conio.h>
#include<stdbool.h>
#include<SDL.h>

//Convert x, y coordinate to index in single dimensional Array
#define IX(x,y,N) ((x) + (y * N))
//playSpace Definition
struct playSpace
{
    Uint32 size;
    bool* cells;
    bool stable;
};
typedef struct playSpace playSpace;

playSpace* playSpaceCreate(Uint32 size)
{
    playSpace* grid = malloc(sizeof(*grid));

    grid->size = size;
    grid->cells = calloc(size * size, sizeof(bool));
    grid->stable = false;

    return grid;
}


//Define and Free playSpace structures

void playSpaceFree(playSpace* space)
{
    free(space->cells);
    free(space->stable);
    free(space);
}

int main()
{
    Uint32 gridSize = 1000;
    SDL_Window* Game_Display;
    SDL_Renderer* Renderer;

    playSpace* state;
    playSpace* state0;

    bool LMBDown = false;

    int mousex;
    int mousey;

    //Initialise GameSpaces & Rendering

    SDL_Init(SDL_INIT_EVERYTHING);
    Game_Display = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, gridSize, gridSize, 0);
    Renderer = SDL_CreateRenderer(Game_Display, -1, 0);
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);
    SDL_RenderClear(Renderer);
    SDL_RenderPresent(Renderer);

    state = playSpaceCreate(gridSize);
    state0 = NULL;
    

    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);

    //


    //Main Game Loop
    
    SDL_Event event;
    bool quit = false;
    int GameState = 0;

    while (!quit)
    {
        //Quit Logic
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) { quit = true; break; }
        
        //Game Logic
        switch (GameState)
        {
            //Pre-Game
            case 0:
            {
                switch (event.type)
                {
                case SDL_MOUSEBUTTONUP:
                    if (event.button.button == SDL_BUTTON_LEFT)
                        LMBDown = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT)
                        LMBDown = true;
                case SDL_MOUSEMOTION:
                    if (LMBDown)
                    {
                        mousex = event.motion.x;
                        mousey = event.motion.y;
                        SDL_RenderDrawPoint(Renderer, mousex, mousey);
                    }
                    break;
                }
                case SDL_KEYDOWN:
                {
                    if (event.key.keysym.sym == SDLK_SPACE)
                    {
                        GameState = 1;
                        break;
                    }
                    if (event.key.keysym.sym == SDLK_BACKSPACE)
                    {
                        SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);
                        SDL_RenderClear(Renderer);
                        SDL_RenderPresent(Renderer);
                        SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
                        break;
                    }
                }
            }

            //Mid-Game
            case 1:
            {

            }

            //Post-Game
            case 2:
            {

            }
        }

        SDL_RenderPresent(Renderer);
    }
    //
    
    //Quit Clean-up
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Game_Display);

    SDL_Quit();
    playSpaceFree(state);
    playSpaceFree(state0);

    free(gridSize);
    free(LMBDown);
    free(mousex);
    free(mousey);
    free(quit);
    free(GameState);

    //
    return 0;
}