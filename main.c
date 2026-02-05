#include "snake.h"
#include <unistd.h> // для usleep

#ifdef _WIN32
#include <windows.h>
#define SLEEP(ms) Sleep(ms)
#else
#define SLEEP(ms) usleep(ms * 1000)
#endif

int main() {
    Game game;
    
    // Инициализация игры
    init_game(&game);
    
    printf("Snake Game - Starting...\n");
    printf("Use WASD keys to control the snake\n");
    printf("Press any key to start...\n");
    getchar();
    
    // Главный игровой цикл
    while(!game.game_over) {
        // Обработка ввода
        process_input(&game);
        
        // Обновление состояния игры
        update_game(&game);
        
        // Отрисовка игры
        draw_game(&game);
        
        // Задержка для контроля скорости игры
        SLEEP(200); // 200ms задержка
    }
    
    // Финальное сообщение
    draw_game(&game);
    printf("\nFinal Score: %d\n", game.score);
    printf("Thanks for playing!\n");
    
    return 0;
}