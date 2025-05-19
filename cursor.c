#include "cursor.h"

//cursor
// Ŀ���� ����,ǥ�� ������ �������� �Լ�
bool get_cursor_visibility(void) {
    bool result = true; // tre�� default
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // �ܼ� �ڵ� ��������
    CONSOLE_CURSOR_INFO cursorInfo;

    // ���� Ŀ�� ���� ��������
    if (GetConsoleCursorInfo(hConsole, &cursorInfo)) {
        //cursorInfo.bVisible = visible; // TRUE: ǥ��, FALSE: ����
        //SetConsoleCursorInfo(hConsole, &cursorInfo);
        result = cursorInfo.bVisible;
    }
    else {
        printf("Error: Unable to set console cursor visibility.\n");
    }
    return result;
}



//cursor
void SetCurrentCursorPos(int x, int y) {
    COORD pos; // = (x, y);
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//cursor
point_t GetCurrentCursorPos(void) {
    point_t curr_point; // curPoint Ÿ���� �ü�� �������̶�  point_t Ÿ���� ����� �̽ļ��� ���� �Ϸ��� �ߴٳ׿�.
    CONSOLE_SCREEN_BUFFER_INFO curr_info;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curr_info);
    curr_point.x = curr_info.dwCursorPosition.X;
    curr_point.y = curr_info.dwCursorPosition.Y;

    return curr_point;
}
