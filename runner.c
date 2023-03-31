#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define CHAR_WIDTH 64
#define CHAR_HEIGHT 64
#define OBSTACLE_WIDTH 32
#define OBSTACLE_HEIGHT 32
#define OBSTACLE_SPEED 5
#define CHAR_SPEED 5

typedef struct {
    SDL_Texture *texture;
    SDL_Rect rect;
    int speed;
} Background;

typedef struct {
    SDL_Texture *texture;
    SDL_Rect rect;
    int speed;
} Obstacle;

typedef struct {
    SDL_Texture *texture;
    SDL_Rect rect;
    int score;
} Character;

void handle_events(SDL_Event event, int *done, Character *character);
void move_character(Character *character, int up, int down);
void move_background(Background *background);
void move_obstacle(Obstacle *obstacle);
int check_collision(Character *character, Obstacle *obstacle);
void render_score(SDL_Renderer *renderer, Character *character);
void cleanup(SDL_Window *window, SDL_Renderer *renderer, Background *background, Character *character, Obstacle *obstacle);

int main()
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *background_texture = NULL, *character_texture = NULL, *obstacle_texture = NULL;
    SDL_Rect background_rect, character_rect, obstacle_rect;
    Background background;
    Character character;
    Obstacle obstacle;
    int done = 0, up = 0, down = 0;

    srand(time(NULL));

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Runner Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (!window) {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        fprintf(stderr, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        fprintf(stderr, "SDL_image could not initialize! SDL_Error: %s\n", IMG_GetError());
        return 1;
    }

    background_texture = IMG_LoadTexture(renderer, "background.png");
    character_texture = IMG_LoadTexture(renderer, "character.png");
    obstacle_texture = IMG_LoadTexture(renderer, "obstacle.png");

    if (!background_texture || !character_texture || !obstacle_texture) {
        fprintf(stderr, "Image(s) could not be loaded! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

        background.rect = (SDL_Rect) {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    background.speed = 2;
    background.texture = background_texture;

    character.rect = (SDL_Rect) {100, SCREEN_HEIGHT / 2 - CHAR_HEIGHT / 2, CHAR_WIDTH, CHAR_HEIGHT};
    character.score = 0;
    character.texture = character_texture;

    obstacle.rect = (SDL_Rect) {SCREEN_WIDTH, rand() % (SCREEN_HEIGHT - OBSTACLE_HEIGHT), OBSTACLE_WIDTH, OBSTACLE_HEIGHT};
    obstacle.speed = OBSTACLE_SPEED;
    obstacle.texture = obstacle_texture;

    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            handle_events(event, &done, &character);
        }

        move_background(&background);
        move_obstacle(&obstacle);

        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, background.texture, NULL, &background.rect);
        SDL_RenderCopy(renderer, character.texture, NULL, &character.rect);
        SDL_RenderCopy(renderer, obstacle.texture, NULL, &obstacle.rect);

        if (check_collision(&character, &obstacle)) {
            printf("Game over! Final score: %d\n", character.score);
            done = 1;
        } else {
            character.score++;
            render_score(renderer, &character);
        }

        SDL_RenderPresent(renderer);
    }

    cleanup(window, renderer, &background, &character, &obstacle);

    return 0;
}

void handle_events(SDL_Event event, int *done, Character *character)
{
    switch (event.type) {
        case SDL_QUIT:
            *done = 1;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    move_character(character, 1, 0);
                    break;
                case SDLK_DOWN:
                    move_character(character, 0, 1);
                    break;
            }
            break;
    }
}

void move_character(Character *character, int up, int down)
{
    if (up) {
        if (character->rect.y > 0) {
            character->rect.y -= CHAR_SPEED;
        }
    }
    if (down) {
        if (character->rect.y < SCREEN_HEIGHT - CHAR_HEIGHT) {
            character->rect.y += CHAR_SPEED;
        }
    }
}

void move_background(Background *background)
{
    background->rect.x -= background->speed;

    if (background->rect.x < -SCREEN_WIDTH) {
        background->rect.x = 0;
    }
}

void move_obstacle(Obstacle *obstacle)
{
    obstacle->rect.x -= obstacle->speed;

    if (obstacle->rect.x < -OBSTACLE_WIDTH) {
        obstacle->rect.x = SCREEN_WIDTH;
        obstacle->rect.y = rand() % (SCREEN_HEIGHT - OBSTACLE_HEIGHT);
    }
}

int check_collision(Character *character, Obstacle *obstacle)
{
    int left1, left2, right1, right2, top1, top2, bottom1, bottom2;

    left1 = character->rect.x;
    right1 = character->rect.x + character->rect.w;
    top1 = character->rect.y;
    bottom1 = character->rect.y + character->rect.h;

    left2 = obstacle->rect.x;
    right2 = obstacle->rect.x + obstacle->rect.w;
    top2 = obstacle->rect.y;
    bottom2 = obstacle->rect.y + obstacle->rect.h;

    if (bottom1 <= top2 || top1 >= bottom2) {
        return 0;
    }

    if (right1 <= left2 || left1 >= right2) {
        return 0;
    }

    return 1;
}

