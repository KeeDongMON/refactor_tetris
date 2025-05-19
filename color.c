#include "color.h"

char* get_color_string(color_t color) {
    if (color >= BLACK && color <= LIGHT_WHITE) {
        return color_strings[color]; // ��ȿ�� ���� ���̸� �ش� ���ڿ� ��ȯ
    }
    else {
        return "unknown"; // ��ȿ���� ���� ���̸� �⺻�� ��ȯ
    }
}

//�߰������� ���� ������ �ش� ���� 8�� ���� ������ ǥ���˴ϴ�(��: ���� �Ķ��� 9).
static char* color_strings[16] = {
    "black", // ����
    "blue", // �Ķ�
    "green", // �ʷ�
    "cyan", // û��
    "red", // ����
    "purple", // ����
    "yellow", // ���
    "white", // ���
    "gray", // ȸ��
    "light blue", // ���� �Ķ�
    "light green", // ���� ȸ��
    "light cyan", // ���� û��
    "light red", // ���� ����
    "light purple", // ���� ����
    "light yellow", // ���� ���
    "light white" // ���� ���
};