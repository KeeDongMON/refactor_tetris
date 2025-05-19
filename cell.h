#ifndef __CELL_H__
#define __CELL_H__

#include "common.h"
#include "color.h"
#include "point.h"
#include "blocks.h"
#include "console.h"

typedef struct _cell_t {
    point_t point; // cell의 위치
    color_t color; // cell의 색상
    cell_attributes_t att; // cell의 속성
} cell_t;

#endif
