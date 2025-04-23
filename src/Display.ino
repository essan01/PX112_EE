#include "Display.h"
#include <I2C_LCD.h>

I2C_LCD LCD;
uint8_t I2C_LCD_ADDRESS = 0x51; // Set the I2C base address for the LCD

int current_page = 0;

char title[5][20] = {{"BAD USB"},{"IR"},{"PONG"},{"SETUP"},{"COP MODE"}};

void setup_display_infos(uint8_t screen_address, int default_page) {
    I2C_LCD_ADDRESS = screen_address; // Set the I2C address for the LCD
    current_page = default_page; // Set the default page to display

    LCD.Init(); // Initialize the LCD
    LCD.CleanAll(WHITE); // Clean the screen with white
    display_page(current_page); // Display the first page
}

void display_page(int page){
    LCD.FontModeConf(Font_6x8, FM_ANL_AAA, BLACK_BAC);
    LCD.CharGotoXY(0,0);       //Set the start coordinate.
    LCD.print(title[page]);  
}
  
void display_next_page(){
    current_page ++;
    if (current_page > 4){
        current_page = 0;
        }
    LCD.CleanAll(WHITE);    //Clean the screen with black or white.
    display_page(current_page);
}
  
void display_previous_page(){
    current_page --;
    if (current_page < 0){
        current_page = 4;
        }
    LCD.CleanAll(WHITE);    //Clean the screen with black or white.
    display_page(current_page);
}

int get_current_page(){
    return current_page;
}