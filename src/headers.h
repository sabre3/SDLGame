//header file for main.c
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

//constants
const int SPRITE_ARRAY_SIZE = 256;

//Structs

struct Sprite {
    void (*act);
    SDL_Texture* texture;
    struct Animate* animes;
    SDL_Rect* source;
    SDL_Rect* size;
    struct Pos* pos;
    int cycle_m; //how many cycles before running act
    int cycle; 
    int move;
    int speed;
};

struct Player {
    int points;
    char* name[];
};

struct Control {
    bool up;
    bool down;
    bool right;
    bool left;
    SDL_Scancode up_t;
    SDL_Scancode down_t;
    SDL_Scancode right_t;
    SDL_Scancode left_t;
};

struct Pos {
    float x;
    float y;
    float move;
};

struct Animate {
    char** textures;
    int cycle_m; //how many cycles before changing to next frame
    int cycle;
    int index; //frame index for textures
    int index_m;
};

//might not be needed
struct Paddle {
    struct Sprite* sprite;
    int x;
    int y;
};

//prototypes
void render(SDL_Renderer*);
void load_texture(SDL_Renderer*, struct Sprite*, char[]);
void init_sprites(SDL_Renderer*);
void keyStates(struct Control*);
bool cycle(struct Sprite*);
void animate(SDL_Renderer*, struct Sprite*);
void act();

