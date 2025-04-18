#ifndef DISPLAY_H
#define DISPLAY_H
#include <I2C_LCD.h>

void setup_display_infos(uint8_t screen_address, int page_number, int tt_len, int default_page);
void display_page(int page);
void display_next_page();
void display_previous_page();
void diplay_list();

#endif DISPLAY_H