#include <Wire.h>
#include <I2C_LCD.h>

#define PAGE_NUMBER 5
#define TT_LEN 10
I2C_LCD LCD;
uint8_t I2C_LCD_ADDRESS = 0x51; 

int current_page = 0;
int pg_count = 0;
char title[PAGE_NUMBER][TT_LEN] = {{"BAD USB"},{"IR"},{"PONG"},{"setup"},{"cop mode"}};

int axeX = A0;
int axeY = A1;
int BP7 = 7;

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
  
void diplay_list(){
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

void setup() {
  pinMode(axeX, INPUT);
  pinMode(axeY, INPUT);
  pinMode(BP7, INPUT);
  digitalWrite(BP7, HIGH); 

  Wire.begin();

  Serial.begin(9600);

  display_page(current_page);
}

void loop() {
  float X = analogRead(axeX) * (5.0 / 1023.0);
  float Y = analogRead(axeY) * (5.0 / 1023.0);


  if (X >= 4.9){
    display_next_page();
  }
  if (X <= 0.1){
    display_previous_page();
  }

}








