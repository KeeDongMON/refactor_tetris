#ifndef __CELL_H__
#define __CELL_H__

#include "common.h"
#include "color.h"
#include "point.h"
#include "blocks.h"
#include "console.h"

typedef struct _cell_t {
    point_t point; // cell�� ��ġ
    color_t color; // cell�� ����
    cell_attributes_t att; // cell�� �Ӽ�
} cell_t;

#endif
