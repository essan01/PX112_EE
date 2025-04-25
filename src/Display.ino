#include "Display.h"
#include <I2C_LCD.h>

I2C_LCD LCD;
uint8_t I2C_LCD_ADDRESS;

int current_page;
int _nb_pages;
char _app_list[10][20]; // Array to hold the app list

void setup_display_infos(uint8_t screen_address, int default_page) {
    I2C_LCD_ADDRESS = screen_address; // Set the I2C address for the LCD
    current_page = default_page; // Set the default page to display
    
    LCD.Init(); // Initialize the LCD
    LCD.CleanAll(WHITE); // Clean the screen with white
    display_page(current_page); // Display the first page
}

void set_app_list(char app_list[][20], int nb_pages) {
    _nb_pages = nb_pages; // Set the number of pages
    
    for (int i = 0; i < _nb_pages; i++) {
        strcpy(_app_list[i], app_list[i]);
    }
}

void display_page(int page){
    LCD.CleanAll(WHITE); // Clean the screen with white
    LCD.FontModeConf(Font_6x8, FM_ANL_AAA, BLACK_BAC);
    LCD.CharGotoXY(0,0);       //Set the start coordinate.
    LCD.print(_app_list[page]);  
}
  
void display_next_page(){
    current_page ++;
    if (current_page > _nb_pages - 1){
        current_page = 0;
        }
    LCD.CleanAll(WHITE);    //Clean the screen with black or white.
    display_page(current_page);
}
  
void display_previous_page(){
    current_page --;
    if (current_page < 0){
        current_page = _nb_pages - 1;
        }
    LCD.CleanAll(WHITE);    //Clean the screen with black or white.
    display_page(current_page);
}

int get_current_page(){
    return current_page;
}

void display_list(int app_selected) {
    LCD.CleanAll(WHITE); // Clean the screen with white
    for(int i = 0; i < _nb_pages; i++){
        if(i == app_selected){
            LCD.FontModeConf(Font_6x8, FM_ANL_AAA, WHITE_BAC);
        }
        else {
            LCD.FontModeConf(Font_6x8, FM_ANL_AAA, BLACK_BAC);
        }
        LCD.CharGotoXY(0,i*8+4);
        LCD.print(_app_list[i]);
    }
}