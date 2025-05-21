#include <IRremote.hpp>
#include <display.h>
#include "IR.h"

//uses IRremote to send basic off signal for denon nec and samsung
extern GUI_Bitmap_t bmcontroller; //Declare bitmap data packet.

const int DELAY_AFTER_SEND = 10;

void send_brand(uint16_t sAddress,uint8_t sCommand, uint8_t sRepeats, int brand){
    switch (brand){
    case 0 : 
        Serial.println(F("Send RC5"));
        Serial.flush();
        IrSender.sendRC5(sAddress & 0x1F, sCommand & 0x3F, sRepeats, true); // 5 address, 6 command bits
        delay(DELAY_AFTER_SEND);
    break;

    case 1 : 
        Serial.println(F("Send Sony/SIRCS with 7 command and 8 address bits"));
        Serial.flush();
        IrSender.sendSony(sAddress & 0xFF, sCommand, sRepeats, SIRCS_15_PROTOCOL);
        delay(DELAY_AFTER_SEND);
    break;

    case 2:
        Serial.println(F("Send Denon"));
        Serial.flush();
        IrSender.sendDenon(sAddress & 0x1F, sCommand, sRepeats);
        delay(DELAY_AFTER_SEND);
    break;

    case 3:
        Serial.println(F("Send Denon/Sharp variant"));
        Serial.flush();
        IrSender.sendSharp(sAddress & 0x1F, sCommand, sRepeats);
        delay(DELAY_AFTER_SEND);
    break;

    default : 
        Serial.println("inconnu");
    }}



void app_IR() {
    LCD.CleanAll(WHITE);    //Clean the screen with black or white.

    //8*16 font size��auto new line��black character on white back ground.
    LCD.FontModeConf(Font_6x8, FM_ANL_AAA, BLACK_BAC); 
    LCD.WorkingModeConf(ON, ON, WM_CharMode);
    LCD.CharGotoXY(0,0);       //Set the start coordinate.
    LCD.print("Hello World!");  //Display "Hello World!" on coordinate of (0, 10).
    LCD.WorkingModeConf(ON, ON, WM_BitmapMode);
    LCD.DrawScreenAreaAt(&bmcontroller, 30, 0);
    LCD.WorkingModeConf(OFF, ON, WM_CharMode);

}