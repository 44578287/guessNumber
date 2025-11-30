#ifndef LED_MATRIX_DRIVER_H
#define LED_MATRIX_DRIVER_H

#include <stm32l0xx.h>
#include "tool.h"
#include <main.h>

// LED 矩阵行列引脚定义
const GPIO_Pin led_matrix_rows[16] = {
    {LedM_R1_GPIO_Port, LedM_R1_Pin},
    {LedM_R2_GPIO_Port, LedM_R2_Pin},
    {LedM_R3_GPIO_Port, LedM_R3_Pin},
    {LedM_R4_GPIO_Port, LedM_R4_Pin},
    {LedM_R5_GPIO_Port, LedM_R5_Pin},
    {LedM_R6_GPIO_Port, LedM_R6_Pin},
    {LedM_R7_GPIO_Port, LedM_R7_Pin},
    {LedM_R8_GPIO_Port, LedM_R8_Pin},
    {LedM_R9_GPIO_Port, LedM_R9_Pin},
    {LedM_R10_GPIO_Port, LedM_R10_Pin},
    {LedM_R11_GPIO_Port, LedM_R11_Pin},
    {LedM_R12_GPIO_Port, LedM_R12_Pin},
    {LedM_R13_GPIO_Port, LedM_R13_Pin},
    {LedM_R14_GPIO_Port, LedM_R14_Pin},
    {LedM_R15_GPIO_Port, LedM_R15_Pin},
    {LedM_R16_GPIO_Port, LedM_R16_Pin}
};

const GPIO_Pin led_matrix_cols[16] = {
    {LedM_C1_GPIO_Port, LedM_C1_Pin},
    {LedM_C2_GPIO_Port, LedM_C2_Pin},
    {LedM_C3_GPIO_Port, LedM_C3_Pin},
    {LedM_C4_GPIO_Port, LedM_C4_Pin},
    {LedM_C5_GPIO_Port, LedM_C5_Pin},
    {LedM_C6_GPIO_Port, LedM_C6_Pin},
    {LedM_C7_GPIO_Port, LedM_C7_Pin},
    {LedM_C8_GPIO_Port, LedM_C8_Pin},
    {LedM_C9_GPIO_Port, LedM_C9_Pin},
    {LedM_C10_GPIO_Port, LedM_C10_Pin},
    {LedM_C11_GPIO_Port, LedM_C11_Pin},
    {LedM_C12_GPIO_Port, LedM_C12_Pin},
    {LedM_C13_GPIO_Port, LedM_C13_Pin},
    {LedM_C14_GPIO_Port, LedM_C14_Pin},
    {LedM_C15_GPIO_Port, LedM_C15_Pin},
    {LedM_C16_GPIO_Port, LedM_C16_Pin}
};

// LED 矩阵IOy查表映射
static uint32_t bsrr_lut_A[16][2]; // [row][0=off, 1=on]
static uint32_t bsrr_lut_C[16][2];


// 初始化LED矩阵的查找表
static inline void led_matrix_init_lut()
{
    for (uint8_t i = 0; i < 16; i++)
    {
        if (led_matrix_rows[i].port == GPIOA)
        {
            bsrr_lut_A[i][1] = led_matrix_rows[i].pin; // ON
            bsrr_lut_A[i][0] = (uint32_t) (led_matrix_rows[i].pin) << 16; // OFF
        } else if (led_matrix_rows[i].port == GPIOC)
        {
            bsrr_lut_C[i][1] = led_matrix_rows[i].pin; // ON
            bsrr_lut_C[i][0] = (uint32_t) (led_matrix_rows[i].pin) << 16; // OFF
        }
    }
}

// 初始化LED矩阵
static inline void led_matrix_init()
{
    led_matrix_init_lut();
    HAL_GPIO_WritePin(BFOE_1_GPIO_Port, BFOE_1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(BFOE_2_GPIO_Port, BFOE_2_Pin, GPIO_PIN_RESET);
}

/*static inline void led_matrix_scan_horizontal(uint16_t *buf)
{
    static uint8_t row = 0;
    SET_PIN_LOW(led_matrix_rows[row].port, led_matrix_rows[row].pin);

    row = (row + 1) & 0x0F;
    uint32_t bsrrB = 0, bsrrD = 0;
    for (uint8_t i = 0; i < 16; i++)
    {
        if (led_matrix_cols[i].port == GPIOB)
            bsrrB |= (buf[row] & (1 << i)) ? led_matrix_cols[i].pin : (led_matrix_cols[i].pin << 16);
        else if (led_matrix_cols[i].port == GPIOD)
            bsrrD |= (buf[row] & (1 << i)) ? led_matrix_cols[i].pin : (led_matrix_cols[i].pin << 16);
    }
    GPIOB->BSRR = bsrrB;
    GPIOD->BSRR = bsrrD;

    SET_PIN_HIGH(led_matrix_rows[row].port, led_matrix_rows[row].pin);
}*/

static inline void led_matrix_scan_vertical(uint16_t *buf)
{
    static uint8_t col = 0;

    // 关闭当前列
    SET_PIN_LOW(led_matrix_cols[col].port, led_matrix_cols[col].pin);

    // 切换到下一列
    col = (col + 1) & 0x0F;

    // 准备当前列的行数据
    uint32_t bsrrA = 0, bsrrC = 0;
    /*for (uint8_t i = 0; i < 16; i++)
    {
        // 从buf中提取第i行第col列的位
        uint8_t bit = (buf[i] & (1 << col)) ? 1 : 0;

        if (led_matrix_rows[i].port == GPIOA)
            bsrrA |= bit ? led_matrix_rows[i].pin : (led_matrix_rows[i].pin << 16);
        else if (led_matrix_rows[i].port == GPIOC)
            bsrrC |= bit ? led_matrix_rows[i].pin : (led_matrix_rows[i].pin << 16);
    }*/
    for (uint8_t i = 0; i < 16; i++)
    {
        uint8_t bit = (buf[i] & (1 << col)) ? 1 : 0;
        bsrrA |= bsrr_lut_A[i][bit];
        bsrrC |= bsrr_lut_C[i][bit];
    }
    // 同时更新所有行引脚
    GPIOA->BSRR = bsrrA;
    GPIOC->BSRR = bsrrC;

    // 打开当前列
    SET_PIN_HIGH(led_matrix_cols[col].port, led_matrix_cols[col].pin);
}

#endif //LED_MATRIX_DRIVER_H
