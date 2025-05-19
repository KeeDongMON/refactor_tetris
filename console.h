#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include "common.h"
#include "point.h"
#include "cursor.h"
#include "color.h"

typedef struct _windows_console_t {
    uint32_t cols;
    uint32_t rows;

    color_t fore_color;
    color_t back_color;

    cursor_info_t cursor_info;
} windows_console_t;


#endif