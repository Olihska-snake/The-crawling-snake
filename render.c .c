#include "snake.h"
#include <stdio.h>

// Отрисовка игрового поля
void draw_game(Game* game) {
    // Очищаем экран (работает в большинстве терминалов)
    printf("\033[2J\033[1;1H");
    
    // Верхняя граница
    for(int i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\n");
    
    // Игровое поле
    for(int y = 0; y < HEIGHT; y++) {
        printf("#"); // Левая граница
        
        for(int x = 0; x < WIDTH; x++) {
            // Проверяем, что находится в текущей клетке
            bool is_snake = false;
            bool is_head = false;
            
            for(int i = 0; i < game->snake.length; i++) {
                if(game->snake.body[i].x == x && game->snake.body[i].y == y) {
                    is_snake = true;
                    if(i == 0) is_head = true;
                    break;
                }
            }
            
            // Проверяем, находится ли здесь еда
            bool is_food = (game->food.x == x && game->food.y == y);
            
            // Отрисовываем символ в зависимости от содержимого клетки
            if(is_head) {
                printf("O"); // Голова змейки
            } else if(is_snake) {
                printf("o"); // Тело змейки
            } else if(is_food) {
                printf("@"); // Еда
            } else {
                printf(" "); // Пустая клетка
            }
        }
        
        printf("#\n"); // Правая граница
    }
    
    // Нижняя граница
    for(int i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\n");
    
    // Информация о игре
    printf("Score: %d\n", game->score);
    printf("Length: %d\n", game->snake.length);
    
    if(game->game_over) {
        printf("\nGAME OVER! Press 'q' to quit.\n");
    } else {
        printf("Use WASD to move, 'q' to quit\n");
    }
}

// Обработка ввода пользователя
void process_input(Game* game) {
    char input;
    
    // Проверяем, есть ли ввод
    if(kbhit()) {
        input = getch();
        
        // Обрабатываем ввод
        switch(input) {
            case 'w':
            case 'W':
                if(game->snake.direction != 'D') game->snake.direction = 'U';
                break;
            case 's':
            case 'S':
                if(game->snake.direction != 'U') game->snake.direction = 'D';
                break;
            case 'a':
            case 'A':
                if(game->snake.direction != 'R') game->snake.direction = 'L';
                break;
            case 'd':
            case 'D':
                if(game->snake.direction != 'L') game->snake.direction = 'R';
                break;
            case 'q':
            case 'Q':
                game->game_over = true;
                break;
        }
    }
}

// Вспомогательные функции для работы с клавиатурой
#ifdef _WIN32
#include <conio.h>
#else
// Для Linux/Mac потребуются дополнительные функции
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

int kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

int getch() {
    struct termios oldt, newt;
    int ch;
    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    
    ch = getchar();
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    
    return ch;
}
#endif