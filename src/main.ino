#include <Wire.h>
#include <I2C_LCD.h>
#include <ctrl_joystick.h> 
#include <Arduino.h>
#include <Display.h>
#include <IRremote.hpp>


void setup() {
  set_joystick_entries(A0, A1, 7); // Set the joystick pins
  setup_display_infos(0x51, 0); // Set the I2C address and page number
  
  Wire.begin();
  Serial.begin(115200);
  
  
#if defined(IR_SEND_PIN)
    IrSender.begin(); // Start with IR_SEND_PIN -which is defined in PinDefinitionsAndMore.h- as send pin and enable feedback LED at default feedback LED pin
//    disableLEDFeedback(); // Disable feedback LED at default feedback LED pin
#  if defined(IR_SEND_PIN_STRING)
    Serial.println(F("Send IR signals at pin " IR_SEND_PIN_STRING));
#  else
    Serial.println(F("Send IR signals at pin " STR(IR_SEND_PIN)));
#  endif
#else

    // Here the macro IR_SEND_PIN is not defined or undefined above with #undef IR_SEND_PIN
    uint8_t tSendPin = 3;
    IrSender.begin(tSendPin, ENABLE_LED_FEEDBACK, USE_DEFAULT_FEEDBACK_LED_PIN); // Specify send pin and enable feedback LED at default feedback LED pin
    // You can change send pin later with IrSender.setSendPin();

    Serial.print(F("Send IR signals at pin "));
    Serial.println(tSendPin);
#endif



 // disableLEDFeedback(); // Disable feedback LED at default feedback LED pin

  //display_page(0);
}

void loop() {
/*
  if (joytick_position_x() >= 4.9){
    display_next_page();
  }
  if (joytick_position_x() <= 0.1){
    display_previous_page();
  }
*/
    LCD.FontModeConf(Font_6x8, FM_ANL_AAA, BLACK_BAC); 
    LCD.WorkingModeConf(ON, ON, WM_CharMode);
    LCD.CharGotoXY(0,0);       //Set the start coordinate.
    LCD.print("Hello World!");  //Display "Hello World!" on coordinate of (0, 10).
delay(50000);
app_IR();
}








