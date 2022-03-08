#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include "headers.h"

//globals
bool run = true; //main game loop
float scaleX;
float scaleY;
struct Sprite* sprites[256] = {NULL};

//main
int main(int argc, char* argv[]) {

    //debug info
    printf("Debug info:\n\n");
    printf("Args: %s %s\n", argv[0], argv[1]);
    printf("\n");

    //SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = NULL;
    if (argc == 2 && !strcmp("-w", argv[1])) {
        //run windowed mode
        window = SDL_CreateWindow("Gamer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 576, SDL_WINDOW_SHOWN);
        scaleX = 1024.0 / 1920.0;
        scaleY = 576.0 / 1080.0;
    } else {
        window = SDL_CreateWindow("Gamer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_FULLSCREEN_DESKTOP);
        scaleX = 1.0;
        scaleY = 1.0;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    init_sprites(renderer);

    //debug control
    struct Control* test = (struct Control*)malloc(sizeof(struct Control));
    test->up_t = SDL_SCANCODE_W;
    test->down_t = SDL_SCANCODE_S;
    test->right_t = SDL_SCANCODE_D;
    test->left_t = SDL_SCANCODE_A;


    while (run) {

        //multiple press input

        keyStates(test);

        struct Sprite* s = sprites[0];

        bool moveit = cycle(s);

        s->pos->y = s->pos->y - (s->pos->move * test->up * moveit);
        s->pos->y = s->pos->y + (s->pos->move * test->down * moveit);
        s->pos->x = s->pos->x + (s->pos->move * test->right * moveit);
        s->pos->x = s->pos->x - (s->pos->move * test->left * moveit);

        //s->size->y = s->size->y - (s->move * test->up * cycle);
        //s->size->y = s->size->y + (s->move * test->down * cycle);
        //s->size->x = s->size->x + (s->move * test->right * cycle);
        //s->size->x = s->size->x - (s->move * test->left * cycle);

        //animate(s);
        animate(renderer, s);

        //render
        render(renderer);
    }

    
    //exit
    return 0;
}

//render everything
void render(SDL_Renderer *renderer) {
    
    //clear
    SDL_RenderClear(renderer);

    //background color
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    //sprites
    //SDL_RenderCopy(renderer, test->texture, test->source, test->size);
    //(sizeof(sprites) / sizeof(struct Sprite*))
    for (int i = 0; i < SPRITE_ARRAY_SIZE; i++) {

        //null check since we changed to a static array
        if (!sprites[i])
            break;

        struct Sprite* sprite = sprites[i];

        //scale pos xy to real xy
        sprite->size->x = (int) sprite->pos->x * scaleX;
        sprite->size->y = (int) sprite->pos->y * scaleY;


        SDL_RenderCopy(renderer, sprite->texture, sprite->source, sprite->size);
    }

    //render
    SDL_RenderPresent(renderer);

}

void load_texture(SDL_Renderer *renderer, struct Sprite* s, char dir[]) {

    SDL_Surface* tmp = IMG_Load(dir);
    s->texture = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);
    //sprite->texture = tex;
}

void init_sprites(SDL_Renderer* renderer) {
    
    //debug
    struct Sprite* tS = (struct Sprite*)malloc(sizeof(struct Sprite));

    tS->source = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    tS->size = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    tS->pos = (struct Pos*)malloc(sizeof(struct Pos));
    tS->animes = (struct Animate*)malloc(sizeof(struct Animate));

    tS->source->h = 1010; //height to cut from y
    tS->source->w = 721; //width to cut from x
    tS->source->x = 0; //cut start position x
    tS->source->y = 0; //cut start position y

    tS->size->h = (int) 420 * scaleY; //scale y
    tS->size->w = (int) 300 * scaleX; //scale x
    tS->size->x = 100; //screen positon x
    tS->size->y = 100; //screen psoiton y

    tS->pos->x = 100.0; //float position 0-1920
    tS->pos->y = 100.0; //float poition 0-1080
    tS->pos->move = 1.0; //movement amount 1.0 = 1 pixel

    tS->cycle_m = 15; //on how many cycle to move
    tS->cycle = 0;

    tS->move = 1; // how many pixels to move on a cycle, probably should be left as 1
    tS->speed = 10; //cycle fraction to move out of 100, ex: 10 -> cycles % 10, must end in 0 or 5 because cycles resets to 0


    tS->animes->cycle = 0;
    tS->animes->cycle_m = 2500;
    //tS->animes->textures = calloc(4, sizeof(struct SDL_Texture*));
    tS->animes->textures = calloc(4, sizeof(char*));

    tS->animes->textures[0] = "assets/zna/zna1.png";
    tS->animes->textures[1] = "assets/zna/zna2.png";
    tS->animes->textures[2] = "assets/zna/zna3.png";
    tS->animes->textures[3] = "assets/zna/zna4.png";

    load_texture(renderer, tS, tS->animes->textures[0]);

    //load_texture(renderer, tS->animes->textures[0], "assets/zna/zna1.png");
    //load_texture(renderer, tS->animes->textures[1], "assets/zna/zna2.png");
    //load_texture(renderer, tS->animes->textures[2], "assets/zna/zna3.png");
    //load_texture(renderer, tS->animes->textures[3], "assets/zna/zna4.png");

    tS->animes->index = 0;
    tS->animes->index_m = 4;

    //tS->texture = tS->animes->textures[3];

    SDL_Surface* tmp = IMG_Load("assets/zna/zna1.png");
    tS->texture = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);

    //load_texture(renderer, tS, "assets/zn.png");

    //this will allocate sprites on heap which is less effecient so I changed sprites to a 256 static array
    //sprites = calloc(1, sizeof(struct Sprite*));
    sprites[0] = tS;

}

void keyStates(struct Control* control) {
    SDL_PumpEvents();
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    control->up = state[control->up_t];
    control->down = state[control->down_t];
    control->right= state[control->right_t];
    control->left = state[control->left_t];
}

bool cycle(struct Sprite* sprite) {
    if (sprite->cycle_m == sprite->cycle) {
        sprite->cycle = 0;
        return true;
    }

    sprite->cycle++;
    return false;
}

void animate(SDL_Renderer* renderer, struct Sprite* sprite) {
    if (sprite->animes->cycle_m == sprite->animes->cycle) {
        sprite->animes->cycle = 0;

        if (sprite->animes->index_m == sprite->animes->index)
            sprite->animes->index = 0;

        //SDL_DestroyTexture(sprite->texture);
        load_texture(renderer, sprite, sprite->animes->textures[sprite->animes->index]);

        sprite->animes->index++;
        return;
    }

    sprite->animes->cycle++;
}