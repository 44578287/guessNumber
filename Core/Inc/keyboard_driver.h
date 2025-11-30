#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

#include <stm32l0xx.h>

#include "main.h"
#include "tool.h"

#define DEBOUNCE_TIME 200  // ms 防抖时间

GPIO_Pin keyboard_rows[4] = {
    {Key_R0_GPIO_Port, Key_R0_Pin},
    {Key_R1_GPIO_Port, Key_R1_Pin},
    {Key_R2_GPIO_Port, Key_R2_Pin},
    {Key_R3_GPIO_Port, Key_R3_Pin}
};

GPIO_Pin keyboard_cols[3] = {
    {Key_C0_GPIO_Port, Key_C0_Pin},
    {Key_C1_GPIO_Port, Key_C1_Pin},
    {Key_C2_GPIO_Port, Key_C2_Pin},
};

typedef struct
{
    uint8_t row;
    uint8_t col;
    char key;
    uint8_t number;
} keyboard_key;

static keyboard_key key_map[4][3] = {
    {{0, 0, '1', 1}, {0, 1, '2', 2}, {0, 2, '3', 3}}, // '1','2','3'
    {{1, 0, '4', 4}, {1, 1, '5', 5}, {1, 2, '6', 6}}, // '4','5','6'
    {{2, 0, '7', 7}, {2, 1, '8', 8}, {2, 2, '9', 9}}, // '7','8','9'
    {{3, 0, '*', 10}, {3, 1, '0', 0}, {3, 2, '#', 11}} // '*','0','#'
};

static keyboard_key button_currently_pressed;

static inline char get_keyboard_currently_pressed_char()
{
    return key_map[button_currently_pressed.row][button_currently_pressed.col].key;
}

static inline uint8_t get_keyboard_currently_pressed_number()
{
    return key_map[button_currently_pressed.row][button_currently_pressed.col].number;
}

static inline void keyboard_scan()
{
    static uint8_t rows = 0;
    SET_PIN_LOW(keyboard_rows[rows].port, keyboard_rows[rows].pin);
    rows = (rows + 1) & 0x03;
    SET_PIN_HIGH(keyboard_rows[rows].port, keyboard_rows[rows].pin);
    button_currently_pressed.row = rows;
}

static inline void keyboard_EXTI_callback(uint16_t GPIO_Pin)
{
    uint32_t now = HAL_GetTick();
    static uint32_t last_interrupt_time = 0;

    switch (GPIO_Pin)
    {
        case Key_C0_Pin:
            button_currently_pressed.col = 0;
            break;
        case Key_C1_Pin:
            button_currently_pressed.col = 1;
            break;
        case Key_C2_Pin:
            button_currently_pressed.col = 2;
            break;
    }

    if (now - last_interrupt_time < DEBOUNCE_TIME)
        return; // 防抖
    last_interrupt_time = now;

    pressedKeyNum = get_keyboard_currently_pressed_number();
    printf("input:%c \n", get_keyboard_currently_pressed_char());
}


#endif //KEYBOARD_DRIVER_H
