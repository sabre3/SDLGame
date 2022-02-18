//header file for main.c
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

//Structs

struct Sprite {
    void (*act);
    SDL_Texture* texture;
    SDL_Rect source;
    SDL_Rect size;
};

struct Player {
    int points;
    char name[16];
};

struct Paddle {
    int x;
    int y;
};

//prototypes
void render(SDL_Renderer*, struct Sprite*);
void load_texture(SDL_Renderer*, struct Sprite*, char[]);
void act();