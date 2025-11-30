#ifndef TOOL_H
#define TOOL_H
#include <stdio.h>
#include <stm32l0xx.h>
#include "usart.h"

int _write(int file, char *ptr, int len)
{
    HAL_UART_Transmit(&huart2, (uint8_t *)ptr, len, HAL_MAX_DELAY);
    return len;
}

#define SET_PIN_HIGH(port, pin) ((port)->BSRR = (pin))
#define SET_PIN_LOW(port, pin)  ((port)->BSRR = (uint32_t)(pin) << 16)

typedef struct
{
    GPIO_TypeDef *port;
    uint16_t pin;
} GPIO_Pin;


uint32_t RNG_GetRange(uint32_t min, uint32_t max)
{
    uint32_t rnd;
    HAL_RNG_GenerateRandomNumber(&hrng, &rnd);
    return min + (rnd % (max - min + 1));
}

/*static inline void printf_bin(int num)
{
    int j, k;
    unsigned char *p = (unsigned char*)&num + 3;//p先指向num后面第3个字节的地址，即num的最高位字节地址

    for (int i = 0; i < 4; i++) //依次处理4个字节(32位）
    {
        j = *(p - i); //取每个字节的首地址，从高位字节到低位字节，即p p-1 p-2 p-3地址处
        for (int k = 7; k >= 0; k--) //处理每个字节的8个位，注意字节内部的二进制数是按照人的习惯存储！
        {
            if (j & (1 << k))//1左移k位，与单前的字节内容j进行或运算，如k=7时，00000000&10000000=0 ->该字节的最高位为0
                printf("1");
            else
                printf("0");
        }
        printf(" ");//每8位加个空格，方便查看
    }
    printf("\r\n");
}

static inline void copy(uint8_t *array, uint8_t *target, uint8_t size)
{
    for (int i = 0; i < size; i++)
    {
        target[i] = array[i];
    }
}

static inline void sort(uint8_t *array, uint8_t size)
{
    uint8_t temp = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

static inline uint16_t sum_up(uint8_t *array, uint8_t size)
{
    uint16_t sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += array[i];
    }
    return sum;
}*/

#endif //TOOL_H