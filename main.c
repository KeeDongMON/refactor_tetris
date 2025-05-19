#include "common.h" //stdint, stdio, stdbool, Windows
#include "blocks.h"
#include "key_driver.h"
#include "console.h"
#include "color.h"
#include "point.h"
#include "cell.h"
#include "sound.h"
#include "board.h"


#define _CRT_SECURE_NO_WARNINGS


//void console_init(windows_console_t* console) {
//    CONSOLE_SCREEN_BUFFER_INFO csbi;
//    console_clear(console);
//
//    // STD_OUTPUT_HANDLE을 통해 콘솔 핸들 가져오기
//    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//
//    // 콘솔 화면 버퍼 정보 가져오기
//    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
//        // 현재 콘솔 창의 크기 정보 얻어오기
//        console->cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
//        console->rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
//
//        // 현재 콘솔 창의 fore, back 색상 정보 알아오기
//        WORD attributes = csbi.wAttributes;
//        console->fore_color = attributes & 0x0F;
//        console->back_color = (attributes >> 4) & 0x0F;
//
//        // 커서 정보 알아내기
//        console->cursor_info.x = csbi.dwCursorPosition.X; // 커서의 X 좌표
//        console->cursor_info.y = csbi.dwCursorPosition.Y; // 커서의 Y 좌표
//
//        console->cursor_info.is_hide = get_cursor_visibility();
//        //set_cursor_visibility(console->cursor_info.is_hide);
//
//        //console_resize(const windows_console_t * console, uint32_t cols, uint32_t rows) {
//        console_resize(&console, RESIZE_COLS, RESIZE_ROWS);
//    }
//    else {
//        printf("Unable to get console window information.\n");
//
//        printf("Error: Unable to get console cursor position.\n");
//        console->cursor_info.x = -1;
//        console->cursor_info.y = -1;
//    }
//    //printf("cosole (cols,rows)= %d,%d", console->cols, console->rows);
//}

//void console_set_size(windows_console_t* console, uint32_t cols, uint32_t rows) {
//    console->cols = cols;
//    console->rows = rows;
//
//    uint8_t dummy_str[128] = { 0, };
//    sprintf(dummy_str, "mode con: cols=%d lines=%d", console->cols, console->rows);
//
//    system(dummy_str);
//    //system("mode con: cols=100 lines=30");//가로크기 100, 세로크기50
//    //printf("%s\r\n", dummy_str);
//
//}

//void console_resize(const windows_console_t* console, uint32_t cols, uint32_t rows) {
//    console_set_size(console, cols, rows);
//}



//void console_display_info(const windows_console_t* console) {
//    static uint8_t dummy_count = 0;
//    printf("This Console information.\r\n");
//    printf("[%d] Size (cols,rows) = (%d,%d)\r\n", ++dummy_count, console->cols, console->rows);
//
//    //printf("[%d] Colors (fore,back) = (%d,%d)\r\n", ++dummy_count, console->fore_color, console->back_color);
//    printf("[%d] Colors (fore,back) = (%s,%s)\r\n", ++dummy_count, get_color_string(console->fore_color), get_color_string(console->back_color));
//    printf("[%d] Cursor (x,y,hide) = %d,%d,%d)\r\n", ++dummy_count, console->cursor_info.x, console->cursor_info.y, console->cursor_info.is_hide);
//}


//void console_set_back_color(windows_console_t* console, uint8_t back_color) {
//    console->back_color = back_color;
//    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), back_color);
//}

//void console_set_color(windows_console_t* console, uint8_t fore_color, uint8_t back_color) {
//    console->fore_color = fore_color;
//    console->back_color = back_color;
//    //void console_set_color(unsigned short text, unsigned short back) {
//    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), console->fore_color | (console->back_color < 4));
//}

//void console_set_default_color(windows_console_t* console) {
//    console_set_color(console, WHITE, BLACK);
//}

//void console_set_fill_color(int background_color) {
//    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 핸들 가져오기
//    CONSOLE_SCREEN_BUFFER_INFO csbi;
//    COORD coord = { 0, 0 }; // 콘솔의 시작 위치 (좌상단)
//    DWORD count;
//
//    // 현재 콘솔 정보 가져오기
//    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
//        printf("Error: Unable to get console screen buffer info.\n");
//        return;
//    }
//
//    // 전체 콘솔 크기 계산 (열 * 행)
//    DWORD console_size = csbi.dwSize.X * csbi.dwSize.Y;
//
//    // 배경색 설정 (foreground: 검정, background: 파랑)
//    WORD attributes = (background_color << 4) | (csbi.wAttributes & 0x0F);
//    SetConsoleTextAttribute(hConsole, attributes);
//
//    // 콘솔 화면을 지정된 색으로 채우기
//    FillConsoleOutputAttribute(hConsole, attributes, console_size, coord, &count);
//
//    // 콘솔 화면을 공백 문자로 채우기
//    FillConsoleOutputCharacter(hConsole, ' ', console_size, coord, &count);
//
//    // 커서를 다시 좌상단으로 이동
//    SetConsoleCursorPosition(hConsole, coord);
//}


//void clearPreviousPosition(int x, int y) {
//    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//    COORD pos = { x, y };
//    DWORD written;
//    FillConsoleOutputCharacter(hConsole, ' ', 1, pos, &written); // 이전 위치를 공백으로 덮음
//}

//void console_clear_region(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
//    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//    COORD coord;
//    DWORD charsWritten;
//
//    for (int cols = 0; cols < height; cols++) {
//        // Implicit casts should not lower precision
//        coord.X = (SHORT)x; // coord.X, Y는 SHORT의 범위(-32,768 ~ 32,767) 내에 있어야 한다.
//        coord.Y = (SHORT)(y + cols);
//        FillConsoleOutputCharacter(hConsole, ' ', width, coord, &charsWritten);
//    }
//}

//void console_clear(const windows_console_t* console) {
//    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 핸들 가져오기
//    CONSOLE_SCREEN_BUFFER_INFO csbi;
//    DWORD console_size = 0;
//    DWORD chars_written = 0;
//    COORD top_left = { 0, 0 }; // 화면 좌상단 좌표
//
//    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) { // 현재 콘솔 정보 가져오기
//        printf("Error: Unable to get console screen buffer info.\n");
//        return;
//    }
//    console_size = csbi.dwSize.X * csbi.dwSize.Y; // 콘솔의 전체 크기 계산 (열 * 행)
//    FillConsoleOutputCharacter(hConsole, ' ', console_size, top_left, &chars_written); // 콘솔 화면을 공백 문자로 채우기
//    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, console_size, top_left, &chars_written); // 콘솔 화면의 모든 속성을 기본값으로 채우기
//    SetConsoleCursorPosition(hConsole, top_left); // 커서를 화면의 좌상단으로 이동
//}
//
//void setcolor(unsigned short text, unsigned short back) {
//    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
//}



bool running = true;

// ----------------------------------

int main(void) {
    //const char* file_path = "sample1.wav";
    //sound_play(file_path);

    // 콘솔 초기화
    // 콘솔 정보를 console 구조체에 담자
    // 콘솔 초기값으로 세팅된다.
    windows_console_t console;
    console_init(&console);
    set_cursor_visible(&console, false);
    //console_display_info(&console);

    //console_set_pos(&console, 32, 32); // 이게 되나? 윈도 바탕화면에서 콘솔의 위치를 결정함
    console_set_fore_color(&console, GREEN); // back_color 신경쓰기 귀찮을때, 
    //console_set_back_color(&console, RED);
    //console_set_color(&console, RED, YELLOW);
    //console_set_default_color(&console); // 콘솔 초기 칼라로 설정 white, black
    //console_set_xy(&console, 32, 32); // 커서의 x,y위치를 설정함
    //cnosole_hide_cursor(true); // 커서 감추기

    /*
        console_display_info(&console);
    ;   // 기본 윈도우 콘솔값 (Default)
        //This Console information.
        //[1] Size(cols, rows) = (120, 30)
        //[2] Colors(fore, back) = (white, black)
        //[3] Cursor(x, y, hide) = 0, 0, 1)
        printf("Press Enter...");
        getchar();

        // 내가원하는 사이즈, 색상으로 변경하자.
        // 윈도우 콘솔 사이즈 변경
        console_set_size(&console, 100, 50);
        console_set_color(&console, RED, BLUE);
        console_set_cursor(&console, 11, 22, false);
        console_clear(&console);
        console_display_info(&console);
        printf("Press Enter...");
        getchar();


        console_set_size(&console, 160, 40);
        console_set_color(&console, BLACK, PURPLE);
        console_clear(&console);
        console_display_info(&console);
        printf("Press Enter...");
        getchar();


        console_set_size(&console, DEFAULT_COLS, DEFAULT_ROWS);
        console_set_color(&console, WHITE, BLACK);
        console_set_fill_color(BLACK);
        console_set_default_color(&console);
        console_display_info(&console);

        printf("Press Enter...");
        getchar();
    */

    console_set_cursor(&console, 0, 0, false);
    console_set_fill_color(BLACK);

    cell_draw_test(&console); // 테스트용, 지워도 무방하지만 종종 테스트 및 좌표 계산때문에 필요하다.
    // 최종 릴리즈에서 지워도 된다. 보기 불편하다면 주석처리
    //getchar();

    board_init(board_data_attributes); // 보드 데이터로 보드를 초기화 한다.

    block_t my_block; // 테스트용 블럭 하나 만들고
    block_init(&my_block, BLOCK_S); // 초기화
    //block_set_xy(&my_block, 0, 0);

    //cell_t my_cell;
    //cell_init(&my_cell, 0, 0, N, RED); // 좌표계 점검용 테스트 코드
    //board_insert_cell(gboard, &my_cell, 10, 19);
    //board_insert_cell(gboard, &my_cell, 1, 0);
    //board_insert_cell(gboard, &my_cell, 1, 19);
    //board_insert_cell(gboard, &my_cell, 10, 0);
    //cell_draw(&my_cell, 0, 0); // 좌상단

    //block_rotate(&my_block);
    board_clear_data(&gboard); // 보드를 지운다. (정확히 말하자면, 보드 데이터 내의 내용을 지운다. 화면을 지우는게 아니라.)
    board_insert_block(gboard, &my_block, 2, 2);
    board_draw(&console, gboard);

    //getchar();

    /*
        block_t block_I; // 테스트용으로 블럭을 7개 만들어 봤다.
        block_t block_J;
        block_t block_L;
        block_t block_O;
        block_t block_S;
        block_t block_T;
        block_t my_block;

        block_init(&block_I, BLOCK_I);
        block_init(&my_block, BLOCK_J);
        //block_init(&my_block, BLOCK_L);
        block_init(&block_O, BLOCK_O);
        block_init(&block_S, BLOCK_S);
        block_init(&block_T, BLOCK_T);
        //block_init(&my_block, BLOCK_Z);

        //block_display_info(&block_I, true);
        //block_display_info(&block_J, true);
        //block_display_info(&block_L, true);
        //block_display_info(&block_O, true);
        //block_display_info(&block_S, true);
        //block_display_info(&block_T, true);
        //block_display_info(&block_Z, true);

        block_set_xy(&my_block, 4, 4);
        block_draw(&my_block);
*/
    key_init();
    uint16_t key_code = 0;

    while (running) {
        key_code = key_get_code();

        switch (key_code) {
        case KEY_UP: // // 블럭을 위(UP)로 이동, 최종적으로는 블럭을 회전(rotate)
            board_move_block(&console, gboard, &my_block, DIR_UP);
            //move_block_on_board(&gboard, &my_block, DIR_UP);
            //board_block_rotate(&my_block); // 반시계방향으로 이동하므로, 인자를 더 줄 필요는 없다.
            break;

        case KEY_LEFT: // 블럭을 왼쪽(LEFT)로 이동
            // old 기존 코드
            // 비교 차원에서 남겨놓는다.

            // 방법(1) 전체를 모두 지우고, 다시 그리는 경우, 플리커링이 심해서 방법 (2)를 쓰자.
            //console_clear(&console);
            //block_set_xy(&my_block, my_block.x - 1, my_block.y); // 좌표 이동및
            //block_draw(&my_block); // 블럭 다시 그리기

            // 방법(2) 전체를 지우지는 않고, 해당 블럭 영역만 지움는 방법, 플리커링이 덜해진다.
            //console_clear_region(my_block.x, my_block.y, my_block.x + (BLOCK_WIDTH * 2), my_block.y + BLOCK_HEIGHT); // 일정 지역만 지우면 플리커링이 덜해진다.
            //block_set_xy(&my_block, my_block.x - 1, my_block.y); // 좌표 이동및
            //block_draw(&my_block); // 블럭 다시 그리기

            // 방법 (3) 하지만, 이방법 모두 좋지 않은데, 그리기 및 충돌 체크가 용이하지 않다.
            // 보드 데이터 내에서 데이터를 insert, clear한 후 이 정보만으로 그리는게 여러 면에서 좋다.
            //board_clear_data(&gboard);
            //my_block.x -= 1; // move 함수로 만드는게 좋다. 충돌 체크등 때문에..
            //board_insert_block(gboard, &my_block, my_block.x, my_block.y);
            //board_draw(&console, gboard);

            // 방법 (4) 아래와 같이 보드 내 데이터를 갱신하는게 좋다.
            // 함수로 만들면 보기가 더 깔끔하다.
            board_move_block(&console, gboard, &my_block, DIR_LEFT);
            break;

        case KEY_RIGHT: // 블럭을 오른쪽으로 이동
            board_move_block(&console, gboard, &my_block, DIR_RIGHT);
            break;

        case KEY_DOWN: // 블럭을 아래로 이동
            board_move_block(&console, gboard, &my_block, DIR_DOWN);
            break;


        case KEY_SPACE: // 블럭을 떨어뜨리기 block drop

            break;
        }
    }

    return 0;
}