#ifndef GAME_H
#define GAME_H
#include <stdint.h>
#include "basic_graphics_driver.h"
#include "stm32l0xx_hal.h"
#include "tool.h"


uint8_t number_5x7[12][7] =
{
    {0x0E, 0x11, 0x19, 0x15, 0x13, 0x11, 0x0E}, // 0
    {0x04, 0x06, 0x04, 0x04, 0x04, 0x04, 0x0E}, // 1
    {0x0E, 0x11, 0x10, 0x08, 0x04, 0x02, 0x1F}, // 2
    {0x1F, 0x08, 0x04, 0x08, 0x10, 0x11, 0x0E}, // 3
    {0x08, 0x0C, 0x0A, 0x09, 0x1F, 0x08, 0x08}, // 4
    {0x1F, 0x01, 0x0F, 0x10, 0x10, 0x11, 0x0E}, // 5
    {0x0C, 0x02, 0x01, 0x0F, 0x11, 0x11, 0x0E}, // 6
    {0x1F, 0x10, 0x08, 0x04, 0x02, 0x02, 0x02}, // 7
    {0x0E, 0x11, 0x11, 0x0E, 0x11, 0x11, 0x0E}, // 8
    {0x0E, 0x11, 0x11, 0x1E, 0x10, 0x08, 0x06}, // 9
    {0x00, 0x11, 0x0a, 0x1f, 0x0a, 0x11, 0x00}, // *
    {0x00, 0x0a, 0x1f, 0x0a, 0x1f, 0x0a, 0x00} // #
};

uint8_t gopher[2] = {0x03, 0x03};
uint8_t game_map[8] = {0x24, 0x24, 0xff, 0x24, 0x24, 0xff, 0x24, 0x24};
/*  地鼠定位
    0,0 3,0 6,0
    0,3 3,3 6,3
    0,6 3,6 6,6
*/
typedef struct
{
    uint8_t row;
    uint8_t col;
} gopher_location;

gopher_location gopher_loc[9] = {
    {0, 0}, {3, 0}, {6, 0},
    {0, 3}, {3, 3}, {6, 3},
    {0, 6}, {3, 6}, {6, 6},
};

static inline void show_game_time(uint8_t time)
{
    uint8_t h = 7 - (time / 5);
    screen_clear_specified(10, 0, 2, h);
    if (h < 7)
        screen_draw_rectangle(10, 6, 11, h);
}

static inline void show_game_level(uint8_t level)
{
    if (level > 4)
        return;
    screen_clear_specified(14, 0, 1, 7);
    for (uint8_t i = 1; i <= level; i++)
    {
        screen_draw_pixel(14, 8 - i * 2);
    }
}

static inline void show_game_score(uint8_t score)
{
    uint8_t T = score / 10, U = score % 10;
    screen_push_data_u8(2, 9, number_5x7[T], 7, 1);
    screen_push_data_u8(9, 9, number_5x7[U], 7, 1);
}

static inline void show_game_map_and_gopher(uint8_t i)
{
    screen_push_data_u8(0, 0, game_map, 8, 1);
    if (i == 0)
        return;
    screen_push_data_u8(gopher_loc[i - 1].row, gopher_loc[i - 1].col, gopher, 2, 0);
}

typedef struct
{
    uint8_t level;
    uint16_t refresh_speed;
} game_config;

typedef struct
{
    uint8_t score;
    uint8_t time;
    uint8_t gopher_location;
    uint8_t gopher_score;
    uint8_t play;
} game_status;


static inline void set_game_level(game_config *c, uint8_t level)
{
    if (level < 1 || level >= 4)
        level = 1;
    c->level = level;
    c->refresh_speed = 1000 / level;
}

static inline void rset_game_struct(game_status *s)
{
    s->gopher_location = 0;
    s->score = 0;
    s->time = 30;
    s->play = 0;
    s->gopher_score = 0;
}

static inline void random_gopher(game_status *s)
{
    uint8_t gopher = RNG_GetRange(1,9);
    printf("地鼠刷新:%d\r\n", gopher);
    // while (s->gopher_location == gopher)
    // {
    //     gopher = RNG_GetRange(1,9);
    // }
    s->gopher_location = gopher;
    s->gopher_score = 0;
    show_game_map_and_gopher(s->gopher_location);
}


uint8_t mode = 0, pressedKeyNum = 0xFF;

static inline void game_mode_0()
{
    for (int i = 0; i < 3; i++)
    {
        screen_fill();
        HAL_Delay(500);
        screen_clear();
        HAL_Delay(500);
    }
    mode = 1;
}

static inline void game_mode_1()
{
    screen_push_data_u8(1, 0, number_5x7[2], 7, 1);
    screen_push_data_u8(9, 0, number_5x7[0], 7, 1);

    screen_push_data_u8(1, 8, number_5x7[2], 7, 1);
    screen_push_data_u8(9, 8, number_5x7[5], 7, 1);
    mode = 2;
}

static inline void game_mode_2()
{
    while (1)
    {
        if (pressedKeyNum == 10) // '*'
        {
            mode = 3;
            pressedKeyNum = 0xFF;
            break;
        } else if (pressedKeyNum != 0xFF)
        {
            screen_clear();
            screen_push_data_u8(0, 0, number_5x7[pressedKeyNum], 7, 1);
            pressedKeyNum = 0xFF;
        }
        HAL_Delay(100);
    }
}

game_status status = {0, 30, 0, 0, 0};
game_config config = {1, 1000};


static inline void play_whack_a_mole_tick()
{
    static uint16_t refresh_num = 0, time_num = 0;
    if (status.play == 1)
    {
        if (config.refresh_speed < refresh_num * 10)
        {
            refresh_num = 0;
            random_gopher(&status);
        }
        if (time_num >= 100)
        {
            time_num = 0;
            if (status.time > 0)
                --status.time;
            show_game_time(status.time);
            // printf("游戏时间:%d\r\n", status.time);
        }
        refresh_num++;
        time_num++;
    }
}

static inline void play_whack_a_mole(game_config *c, game_status *s)
{
    show_game_time(status.time);
    show_game_level(config.level);
    show_game_score(status.score);
    while (1)
    {
        if (pressedKeyNum == 0 || status.time == 0)
        {
            pressedKeyNum = 0xFF;
            printf("游戏结束! 最终得分:%d\r\n", s->score);
            rset_game_struct(s);
            show_game_map_and_gopher(0);
            show_game_time(s->time);
            return;
        }
        if (pressedKeyNum != 0xFF)
        {
            if (s->gopher_location == pressedKeyNum && s->gopher_score == 0)
            {
                pressedKeyNum = 0xFF;
                s->gopher_score = 1;
                s->score++;
                show_game_score(s->score);
                show_game_map_and_gopher(0);
                printf("得分! 当前分数:%d\r\n", s->score);
            }
        }
        //HAL_Delay(0);
    }
}

static inline void game_mode_3()
{
    screen_clear();
    show_game_map_and_gopher(status.gopher_location);
    show_game_time(status.time);
    show_game_level(config.level);
    show_game_score(status.score);
    while (1)
    {
        if (pressedKeyNum == 11)
        {
            set_game_level(&config, ++config.level);
            show_game_level(config.level);
            pressedKeyNum = 0XFF;
            printf("当前难度:%d\r\n", config.level);
        } else if (pressedKeyNum == 10)
        {
            status.play = 1;
            printf("游戏开始! 当前难度:%d\r\n", config.level);
            play_whack_a_mole(&config, &status);
            pressedKeyNum = 0XFF;
        }
        HAL_Delay(100);
    }
}

typedef void (*FuncPtr)(void);

FuncPtr game_mode[] = {game_mode_0, game_mode_1, game_mode_2, game_mode_3};

static inline void game()
{
    uint8_t temp_mode = 255;
    while (1)
    {
        if (temp_mode != mode)
        {
            temp_mode = mode;
            pressedKeyNum = 0xFF;
            game_mode[mode]();
        } else
        {
            HAL_Delay(100);
        }
    }
}

#endif //GAME_H
