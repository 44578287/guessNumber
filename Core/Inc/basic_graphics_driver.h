#ifndef BASIC_GRAPHICS_DRIVER_H
#define BASIC_GRAPHICS_DRIVER_H
#include <stdint.h>
#include <stdlib.h>


static uint16_t screen_buffer[16] = {0}; // 16*16 bit

static inline void screen_clear()
{
    for (uint8_t i = 0; i < 16; i++)
        screen_buffer[i] = 0;
}

static inline void screen_clear_specified(uint8_t x, uint8_t y, uint8_t w, uint8_t h)
{
    uint8_t max_row = (y + h > 16) ? 16 : (y + h);
    uint8_t max_col = (x + w > 16) ? 16 : (x + w);

    for (uint8_t r = y; r < max_row; r++)
    {
        uint16_t mask = (0xFFFF >> (16 - (max_col - x))) << x;
        screen_buffer[r] &= ~mask;
    }
}

static inline void screen_fill()
{
    for (uint8_t i = 0; i < 16; i++)
        screen_buffer[i] = 0xFFFF;
}

static inline void screen_set_pixel(uint8_t x, uint8_t y, uint8_t bit)
{
    if (bit)
        screen_buffer[y] |= (1 << x);
    else
        screen_buffer[y] &= ~(1 << x);
}

static inline void screen_draw_pixel(uint8_t x, uint8_t y)
{
    screen_buffer[y] |= (1 << x);
}

static inline void screen_clear_pixel(uint8_t x, uint8_t y)
{
    screen_buffer[y] &= ~(1 << x);
}

static inline void screen_draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2; // error value e_xy

    while (1)
    {
        screen_draw_pixel(x0, y0);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        } // e_xy+e_x > 0
        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        } // e_xy+e_y < 0
    }
}

static inline void screen_draw_rectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
    screen_draw_line(x0, y0, x1, y0);
    screen_draw_line(x0, y1, x1, y1);
    screen_draw_line(x0, y0, x0, y1);
    screen_draw_line(x1, y0, x1, y1);
}

static inline void screen_fill_rectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
    for (uint8_t y = y0; y <= y1; y++)
    {
        for (uint8_t x = x0; x <= x1; x++)
        {
            screen_draw_pixel(x, y);
        }
    }
}

static inline void screen_push_data_u16(uint8_t x, uint8_t y, uint16_t *data, uint8_t len, uint8_t cover)
{
    uint8_t max_row = (y + len > 16) ? 16 : (y + len);

    for (uint8_t r = 0; r < max_row - y; r++)
    {
        uint16_t shifted_data = data[r] << x;

        if (cover)
        {
            uint16_t mask = (x == 0) ? 0xFFFF : ((0xFFFF >> (16 - (16 - x))) << x);
            screen_buffer[y + r] &= ~mask;
        }

        screen_buffer[y + r] |= shifted_data;
    }
}

static inline void screen_push_data_u8(uint8_t x, uint8_t y, uint8_t *data, uint8_t len, uint8_t cover)
{
    uint8_t max_row = (y + len > 16) ? 16 : (y + len);

    for (uint8_t r = 0; r < max_row - y; r++)
    {
        uint16_t shifted_data = ((uint16_t) data[r]) << x;

        // printf_bin(data[0]);
        // printf_bin((uint16_t)data[r]);
        // printf_bin(shifted_data);

        if (cover)
        {
            uint16_t mask = ((uint16_t) 0xFF) << x;
            screen_buffer[y + r] &= ~mask;
        }

        screen_buffer[y + r] |= shifted_data;

        //printf_bin(screen_buffer[0]);
    }
}

static inline uint8_t reverse_bits_u8(uint8_t n)
{
    n = ((n & 0xF0) >> 4) | ((n & 0x0F) << 4); // 高低4位交换
    n = ((n & 0xCC) >> 2) | ((n & 0x33) << 2); // 每2位交换
    n = ((n & 0xAA) >> 1) | ((n & 0x55) << 1); // 每1位交换
    return n;
}

static inline uint16_t reverse_bits_u16(uint16_t n)
{
    n = ((n & 0xFF00) >> 8) | ((n & 0x00FF) << 8); // 高低8位交换
    n = ((n & 0xF0F0) >> 4) | ((n & 0x0F0F) << 4); // 每4位交换
    n = ((n & 0xCCCC) >> 2) | ((n & 0x3333) << 2); // 每2位交换
    n = ((n & 0xAAAA) >> 1) | ((n & 0x5555) << 1); // 每1位交换
    return n;
}

static inline void screen_push_data_u8_vertical(uint8_t x, uint8_t y, const uint8_t *data, uint8_t len, uint8_t cover)
{
    const uint8_t max_row = 8;
    const uint8_t max_col = (x + len > 16) ? 16 : (x + len);

    for (uint8_t i = 0; i < len && (x + i) < max_col; i++)
    {
        uint8_t col_data = reverse_bits_u8(data[i]); // 不改原data
        for (uint8_t r = y; r < max_row; r++)
        {
            uint8_t bit_pos = r - y;
            uint8_t bit = (col_data >> bit_pos) & 0x01;

            if (cover)
                screen_buffer[r] &= ~(1 << (x + i)); // 清零

            if (bit)
                screen_buffer[r] |= (1 << (x + i)); // 设置
        }
    }
}

static inline void screen_push_data_u16_vertical(uint8_t x, uint8_t y, const uint16_t *data, uint8_t len, uint8_t cover)
{
    const uint8_t max_row = 16;
    const uint8_t max_col = (x + len > 16) ? 16 : (x + len);

    for (uint8_t i = 0; i < len && (x + i) < max_col; i++)
    {
        uint16_t col_data = reverse_bits_u16(data[i]); // 使用临时变量，不修改原始data
        for (uint8_t r = y; r < max_row; r++)
        {
            uint8_t bit_pos = r - y;
            uint8_t bit = (col_data >> bit_pos) & 0x01;

            if (cover)
                screen_buffer[r] &= ~(1 << (x + i)); // 清零

            if (bit)
                screen_buffer[r] |= (1 << (x + i)); // 设置
        }
    }
}

// Let users realize it themselves
static inline void screen_show(void);

#endif //BASIC_GRAPHICS_DRIVER_H
