#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "headers.h"

//globals
bool run = true;

int main(int argc, char* argv[]) {

    printf("Debug info:\n\n");
    printf("Args: %s %s\n", argv[0], argv[1]);
    printf("\n");

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = NULL;
    if (argc == 2 && !strcmp("-w", argv[1])) {
        //run windowed mode
        window = SDL_CreateWindow("Gamer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 576, SDL_WINDOW_SHOWN);
    } else {
        window = SDL_CreateWindow("Gamer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_FULLSCREEN_DESKTOP);
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);


    //debug
    struct Sprite* tS = (struct Sprite*)malloc(sizeof(struct Sprite));
    //tS->source.h = NULL; check later
    tS->size.h = 420;
    tS->size.w = 300;
    tS->size.x = 100;
    tS->size.y = 100;
    load_texture(renderer, tS, "assets/zn.png");


    while (run) {
        render(renderer, tS);
    }

    
    //exit
    return 0;
}

void render(SDL_Renderer *renderer, struct Sprite* test) {
    
    //clear
    SDL_RenderClear(renderer);

    //background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    //sprites
    SDL_RenderCopy(renderer, test->texture, NULL, &test->size);

    //render
    SDL_RenderPresent(renderer);

}

void load_texture(SDL_Renderer *renderer, struct Sprite* sprite, char dir[]) {

    SDL_Surface* tmp = IMG_Load(dir);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);
    sprite->texture = tex;
}