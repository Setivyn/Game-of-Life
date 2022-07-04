#include<stdio.h>
#include<conio.h>
#include<stdbool.h>
#include<SDL.h>

//Convert x, y coordinate to index in single dimensional Array
#define IX(x,y,N) ((x) + (y * N))
//playSpace Definition
struct playSpace
{
    int size;
    bool* cells;
    bool stable;
};
typedef struct playSpace playSpace;

playSpace* playSpaceCreate(int size)
{
    playSpace* grid = malloc(sizeof(*grid));
    int N = size;

    grid->size = size;
    grid->cells = calloc(N * N, sizeof(bool));
    grid->stable = false;

    return grid;
}


bool initGame(SDL_Window* Display, SDL_Renderer* renderer, playSpace* state, playSpace* state0, int size)
{
    //Initialise SDL Window
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return false;
    }

    Display = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);

    if (Display == NULL)
    {
        return false;
    }

    renderer = SDL_CreateRenderer(Display, -1, 0);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderPresent(renderer);

    //
    //Initialise PlaySpace

    state = playSpaceCreate(size);
    state0 = NULL;

    if (state == NULL)
    {
        return false;
    }

    return true;
}

//Define and Free playSpace structures

SDL_Surface initDisplay(int size)
{


}

void playSpaceFree(playSpace* space)
{
    free(space->cells);
    free(space->stable);
    free(space);
}

int main()
{
    int gridSize = 100;
    SDL_Window* Game_Display;
    SDL_Renderer* renderer;

    playSpace* state;
    playSpace* state0;

    if (initGame(&Game_Display, &renderer, &state, &state0, gridSize))
    {
        bool close = false;

        while (!close) {
            SDL_Event event;

            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                case SDL_QUIT:
                    close = true;
                    break;
                }
            }
        }
    }
    return 0;
}