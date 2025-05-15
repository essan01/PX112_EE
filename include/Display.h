#ifndef DISPLAY_H
#define DISPLAY_H
#include <I2C_LCD.h>

void setup_display_infos(uint8_t screen_address , int default_pages);
void display_page(int page);
void display_next_page();
void display_previous_page();
int get_current_page();
void display_list(int app_selected);
void set_app_list(char app_list[][20], int nb_pages);

#endif