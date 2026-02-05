#include "snake.h"
#include <stdlib.h>
#include <time.h>

// Инициализация игры
void init_game(Game* game) {
    // Инициализация генератора случайных чисел
    srand(time(NULL));
    
    // Начальная позиция змейки - по центру поля
    game->snake.length = INITIAL_LENGTH;
    game->snake.direction = 'R'; // Начинаем движение вправо
    
    // Устанавливаем начальные сегменты змейки
    for(int i = 0; i < game->snake.length; i++) {
        game->snake.body[i].x = WIDTH/2 - i;
        game->snake.body[i].y = HEIGHT/2;
    }
    
    // Генерируем первую еду
    generate_food(game);
    
    game->score = 0;
    game->game_over = false;
}

// Генерация еды на случайной позиции
void generate_food(Game* game) {
    bool on_snake;
    
    do {
        on_snake = false;
        // Генерируем случайные координаты
        game->food.x = rand() % WIDTH;
        game->food.y = rand() % HEIGHT;
        
        // Проверяем, не попала ли еда на змейку
        for(int i = 0; i < game->snake.length; i++) {
            if(game->snake.body[i].x == game->food.x && 
               game->snake.body[i].y == game->food.y) {
                on_snake = true;
                break;
            }
        }
    } while(on_snake);
}

// Проверка столкновений
bool check_collision(Game* game) {
    Point head = game->snake.body[0];
    
    // Проверка столкновения со стенами
    if(head.x < 0 || head.x >= WIDTH || head.y < 0 || head.y >= HEIGHT) {
        return true;
    }
    
    // Проверка столкновения с собой
    for(int i = 1; i < game->snake.length; i++) {
        if(head.x == game->snake.body[i].x && head.y == game->snake.body[i].y) {
            return true;
        }
    }
    
    return false;
}

// Обновление состояния игры
void update_game(Game* game) {
    if(game->game_over) return;
    
    // Сохраняем старую позицию хвоста
    Point old_tail = game->snake.body[game->snake.length - 1];
    
    // Двигаем тело змейки (кроме головы)
    for(int i = game->snake.length - 1; i > 0; i--) {
        game->snake.body[i] = game->snake.body[i - 1];
    }
    
    // Двигаем голову в зависимости от направления
    Point new_head = game->snake.body[0];
    
    switch(game->snake.direction) {
        case 'U': new_head.y--; break;
        case 'D': new_head.y++; break;
        case 'L': new_head.x--; break;
        case 'R': new_head.x++; break;
    }
    
    game->snake.body[0] = new_head;
    
    // Проверка столкновения
    if(check_collision(game)) {
        game->game_over = true;
        return;
    }
    
    // Проверка, съела ли змейка еду
    if(new_head.x == game->food.x && new_head.y == game->food.y) {
        // Увеличиваем змейку
        game->snake.length++;
        game->snake.body[game->snake.length - 1] = old_tail;
        
        // Увеличиваем счет
        game->score += 10;
        
        // Генерируем новую еду
        generate_food(game);
    }
}