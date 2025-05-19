#include "cell.h"

//GeunU PART
//cell
void cell_init(cell_t* cell, int x, int y, cell_attributes_t att, color_t color) {
    cell->point.x = x;
    cell->point.y = y;
    cell->att = att;
    cell->color = color;
}


//cell
//void draw_one_cell(cell_t* cell, uint32_t x, uint32_t y) {
void cell_draw(cell_t* cell, uint32_t x, uint32_t y) {
    cell->point.x = x;
    cell->point.y = y;

    COORD pos;
    pos.X = (short)cell->point.x;
    pos.Y = (short)cell->point.y;
    pos.X *= 2;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, pos);
    printf("■");
}

//cell
void cell_draw_test(windows_console_t* console) {
    cell_t my_cell;
    cell_init(&my_cell, 0, 0, N, YELLOW); // 좌표계 점검용 테스트 코드
    console_set_fore_color(console, my_cell.color);
    //console->fore_color(my_cell.color);
    cell_draw(&my_cell, 0, 0); // 좌상단
    cell_draw(&my_cell, RESIZE_COLS / 2 - 1, 0); // 우상단
    cell_draw(&my_cell, RESIZE_COLS / 2 - 1, RESIZE_ROWS - 1); // 우하단
    cell_draw(&my_cell, 0, RESIZE_ROWS - 1); // 좌하단
    cell_draw(&my_cell, (RESIZE_COLS / 2 - 1) / 2, (RESIZE_ROWS - 1) / 2); // 정중앙
}