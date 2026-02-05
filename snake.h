#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>

// Константы игры
#define WIDTH 20
#define HEIGHT 20
#define INITIAL_LENGTH 3

// Структура для координат
typedef struct {
    int x;
    int y;
} Point;

// Структура для змейки
typedef struct {
    Point body[WIDTH * HEIGHT]; // Максимально возможная длина
    int length;
    char direction; // 'U' - up, 'D' - down, 'L' - left, 'R' - right
} Snake;

// Структура игры
typedef struct {
    Snake snake;
    Point food;
    int score;
    bool game_over;
} Game;

// Прототипы функций
void init_game(Game* game);
void draw_game(Game* game);
void update_game(Game* game);
void process_input(Game* game);
bool check_collision(Game* game);
void generate_food(Game* game);

#endif