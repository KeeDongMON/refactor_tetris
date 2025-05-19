#ifndef __CURSOR_H__
#define __CURSOR_H__
#include "common.h"
#include "point.h"

typedef struct _cursor_info_t {
    uint32_t x;
    uint32_t y;
    bool is_hide;
} cursor_info_t;

#endif
