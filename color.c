#include "color.h"

char* color_strings[16] = {
    "black", // °ËÁ¤
    "blue", // ÆÄ¶û
    "green", // ÃÊ·Ï
    "cyan", // Ã»·Ï
    "red", // »¡°­
    "purple", // ÀÚÁÖ
    "yellow", // ³ë¶û
    "white", // Èò»ö
    "gray", // È¸»ö
    "light blue", // ¹àÀº ÆÄ¶û
    "light green", // ¹àÀº È¸»ö
    "light cyan", // ¹àÀº Ã»·Ï
    "light red", // ¹àÀº »¡°­
    "light purple", // ¹àÀº ÀÚÁÖ
    "light yellow", // ¹àÀº ³ë¶û
    "light white" // ¹àÀº Èò»ö
};

char* get_color_string(color_t color) {
    if (color >= BLACK && color <= LIGHT_WHITE) {
        return color_strings[color]; // À¯È¿ÇÑ »ö»ó °ªÀÌ¸é ÇØ´ç ¹®ÀÚ¿­ ¹ÝÈ¯
    }
    else {
        return "unknown"; // À¯È¿ÇÏÁö ¾ÊÀº °ªÀÌ¸é ±âº»°ª ¹ÝÈ¯
    }
}
