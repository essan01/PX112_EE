#include <Wire.h>
#include <I2C_LCD.h>
#include <ctrl_joystick.h> 
#include <Arduino.h>
#include <Display.h>



void setup() {
  set_joystick_entries(A0, A1, 7); // Set the joystick pins
  setup_display_infos(0x51, 0); // Set the I2C address and page number
  
  Wire.begin();
  Serial.begin(9600);

  display_page(0);
}

void loop() {

  if (joytick_position_x() >= 4.9){
    display_next_page();
  }
  if (joytick_position_x() <= 0.1){
    display_previous_page();
  }
}








