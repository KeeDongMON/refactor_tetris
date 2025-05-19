#include "console.h"

void console_clear(windows_console_t* console);

void console_set_cursor(windows_console_t* console, uint32_t x, uint32_t y, bool value) {
    console->cursor_info.x = x;
    console->cursor_info.y = y;
    console->cursor_info.is_hide = value;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 핸들 가져오기
    CONSOLE_CURSOR_INFO cursorInfo;

    if (GetConsoleCursorInfo(hConsole, &cursorInfo)) {
        cursorInfo.bVisible = console->cursor_info.is_hide; // TRUE: 표시, FALSE: 숨김
        SetConsoleCursorInfo(hConsole, &cursorInfo);
    }
    else {
        printf("Error: Unable to set console cursor visibility.\n");
    }
}

void console_init(windows_console_t* console) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    console_clear(console);

    // STD_OUTPUT_HANDLE을 통해 콘솔 핸들 가져오기
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // 콘솔 화면 버퍼 정보 가져오기
    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        // 현재 콘솔 창의 크기 정보 얻어오기
        console->cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        console->rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        // 현재 콘솔 창의 fore, back 색상 정보 알아오기
        WORD attributes = csbi.wAttributes;
        console->fore_color = attributes & 0x0F;
        console->back_color = (attributes >> 4) & 0x0F;

        // 커서 정보 알아내기
        console->cursor_info.x = csbi.dwCursorPosition.X; // 커서의 X 좌표
        console->cursor_info.y = csbi.dwCursorPosition.Y; // 커서의 Y 좌표

        console->cursor_info.is_hide = get_cursor_visibility();
        //set_cursor_visibility(console->cursor_info.is_hide);

        //console_resize(const windows_console_t * console, uint32_t cols, uint32_t rows) {
        console_resize(&console, RESIZE_COLS, RESIZE_ROWS);
    }
    else {
        printf("Unable to get console window information.\n");

        printf("Error: Unable to get console cursor position.\n");
        console->cursor_info.x = -1;
        console->cursor_info.y = -1;
    }
    //printf("cosole (cols,rows)= %d,%d", console->cols, console->rows);
}
void console_set_size(windows_console_t* console, uint32_t cols, uint32_t rows) {
    console->cols = cols;
    console->rows = rows;

    uint8_t dummy_str[128] = { 0, };
    sprintf(dummy_str, "mode con: cols=%d lines=%d", console->cols, console->rows);

    system(dummy_str);
    //system("mode con: cols=100 lines=30");//가로크기 100, 세로크기50
    //printf("%s\r\n", dummy_str);

}

void console_resize(const windows_console_t* console, uint32_t cols, uint32_t rows) {
    console_set_size(console, cols, rows);
}

void console_display_info(const windows_console_t* console) {
    static uint8_t dummy_count = 0;
    printf("This Console information.\r\n");
    printf("[%d] Size (cols,rows) = (%d,%d)\r\n", ++dummy_count, console->cols, console->rows);

    //printf("[%d] Colors (fore,back) = (%d,%d)\r\n", ++dummy_count, console->fore_color, console->back_color);
    printf("[%d] Colors (fore,back) = (%s,%s)\r\n", ++dummy_count, get_color_string(console->fore_color), get_color_string(console->back_color));
    printf("[%d] Cursor (x,y,hide) = %d,%d,%d)\r\n", ++dummy_count, console->cursor_info.x, console->cursor_info.y, console->cursor_info.is_hide);
}

//console
void console_set_fore_color(windows_console_t* console, uint8_t fore_color) {
    console->fore_color = fore_color;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fore_color);
}

void console_set_back_color(windows_console_t* console, uint8_t back_color) {
    console->back_color = back_color;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), back_color);
}

void console_set_color(windows_console_t* console, uint8_t fore_color, uint8_t back_color) {
    console->fore_color = fore_color;
    console->back_color = back_color;
    //void console_set_color(unsigned short text, unsigned short back) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), console->fore_color | (console->back_color << 4));
}

void console_set_default_color(windows_console_t* console) {
    console_set_color(console, WHITE, BLACK);
}

void console_set_fill_color(int background_color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 핸들 가져오기
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    COORD coord = { 0, 0 }; // 콘솔의 시작 위치 (좌상단)
    DWORD count;

    // 현재 콘솔 정보 가져오기
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        printf("Error: Unable to get console screen buffer info.\n");
        return;
    }

    // 전체 콘솔 크기 계산 (열 * 행)
    DWORD console_size = csbi.dwSize.X * csbi.dwSize.Y;

    // 배경색 설정 (foreground: 검정, background: 파랑)
    WORD attributes = (background_color << 4) | (csbi.wAttributes & 0x0F);
    SetConsoleTextAttribute(hConsole, attributes);

    // 콘솔 화면을 지정된 색으로 채우기
    FillConsoleOutputAttribute(hConsole, attributes, console_size, coord, &count);

    // 콘솔 화면을 공백 문자로 채우기
    FillConsoleOutputCharacter(hConsole, ' ', console_size, coord, &count);

    // 커서를 다시 좌상단으로 이동
    SetConsoleCursorPosition(hConsole, coord);
}

void console_clear_region(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;
    DWORD charsWritten;

    for (int cols = 0; cols < height; cols++) {
        // Implicit casts should not lower precision
        coord.X = (SHORT)x; // coord.X, Y는 SHORT의 범위(-32,768 ~ 32,767) 내에 있어야 한다.
        coord.Y = (SHORT)(y + cols);
        FillConsoleOutputCharacter(hConsole, ' ', width, coord, &charsWritten);
    }
}

void console_clear(const windows_console_t* console) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 핸들 가져오기
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD console_size = 0;
    DWORD chars_written = 0;
    COORD top_left = { 0, 0 }; // 화면 좌상단 좌표

    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) { // 현재 콘솔 정보 가져오기
        printf("Error: Unable to get console screen buffer info.\n");
        return;
    }
    console_size = csbi.dwSize.X * csbi.dwSize.Y; // 콘솔의 전체 크기 계산 (열 * 행)
    FillConsoleOutputCharacter(hConsole, ' ', console_size, top_left, &chars_written); // 콘솔 화면을 공백 문자로 채우기
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, console_size, top_left, &chars_written); // 콘솔 화면의 모든 속성을 기본값으로 채우기
    SetConsoleCursorPosition(hConsole, top_left); // 커서를 화면의 좌상단으로 이동
}

void setcolor(unsigned short text, unsigned short back) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));

//cursor
void set_cursor_visible(windows_console_t* console, bool hide) {
    console->cursor_info.is_hide = hide;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 핸들 가져오기
    CONSOLE_CURSOR_INFO cursorInfo;

    if (GetConsoleCursorInfo(hConsole, &cursorInfo)) {
        cursorInfo.bVisible = console->cursor_info.is_hide; // TRUE: 표시, FALSE: 숨김
        SetConsoleCursorInfo(hConsole, &cursorInfo);
    }
    else {
        printf("Error: Unable to set console cursor visibility.\n");
    }
}