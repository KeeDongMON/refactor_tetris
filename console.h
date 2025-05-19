#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <windows.h>

#include "key_driver.h"
#include "blocks.h"
#include "common.h"
#include "point.h"
#include "cursor.h"
#include "color.h"


#define DEFAULT_COLS 120
#define DEFAULT_ROWS 30

#define RESIZE_COLS (DEFAULT_COLS-30) //=90
#define RESIZE_ROWS 30



typedef struct _windows_console_t {
    uint32_t cols;
    uint32_t rows;

    color_t fore_color;
    color_t back_color;

    cursor_info_t cursor_info;
} windows_console_t;


void console_clear(windows_console_t* console);
void console_set_cursor(windows_console_t* console, uint32_t x, uint32_t y, bool value);
void console_init(windows_console_t* console);
void console_set_size(windows_console_t* console, uint32_t cols, uint32_t rows);
void console_resize(const windows_console_t* console, uint32_t cols, uint32_t rows);
void console_display_info(const windows_console_t* console);
void console_set_fore_color(windows_console_t* console, uint8_t fore_color);
void console_set_back_color(windows_console_t* console, uint8_t back_color);
void console_set_color(windows_console_t* console, uint8_t fore_color, uint8_t back_color);
void console_set_default_color(windows_console_t* console);
void console_set_fill_color(int background_color);
void console_clear_region(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
void console_clear(const windows_console_t* console);
void setcolor(unsigned short text, unsigned short back);


#endif

