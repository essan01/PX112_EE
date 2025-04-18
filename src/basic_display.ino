#include <Wire.h>
#include <I2C_LCD.h>
#define PAGE_NUMBER 5
#define TT_LEN 10
I2C_LCD LCD;
uint8_t I2C_LCD_ADDRESS = 0x51; //Device address configuration, the default value is 0x51.

//For detials of the function useage, please refer to "I2C_LCD User Manual". 
//You can download the "I2C_LCD User Manual" from I2C_LCD WIKI page: http://www.seeedstudio.com/wiki/I2C_LCD

int current_page = 0;
int pg_count = 0;
char title[PAGE_NUMBER][TT_LEN] = {{"BAD USB"},{"IR"},{"PONG"},{"setup"},{"cop mode"}};

void dsp_page(int page){
  LCD.CleanAll(WHITE);    //Clean the screen with black or white.
  LCD.FontModeConf(Font_6x8, FM_ANL_AAA, BLACK_BAC);
  LCD.CharGotoXY(0,0);       //Set the start coordinate.
    LCD.print(title[page]);  
  }
void dsp_next_page(){
  current_page ++;
  if (current_page>4){
    current_page = 0;
    }
  dsp_page(current_page);
  }
  
void dsp_list(){
  LCD.CleanAll(WHITE);    //Clean the screen with black or white.
  for(int i=0; i<5; i++){
    if(i==current_page){
        LCD.FontModeConf(Font_8x16_2, FM_ANL_AAA, WHITE_BAC);
      }
    else {
        LCD.FontModeConf(Font_6x8, FM_ANL_AAA, BLACK_BAC);
    }
    
    if(i<=current_page){
      LCD.CharGotoXY(0,i*8+4);
      } 
    else{
      LCD.CharGotoXY(0,(i-1)*8+20);
      }
    LCD.print(title[i]);
    }
  }
void setup(void)
{
    Wire.begin();         //I2C controller initialization.
}

void loop(void)
{
  dsp_list();
  current_page ++;
  if (current_page>4){
    current_page = 0;
    }

  delay(1000);
}
