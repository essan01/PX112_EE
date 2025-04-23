#include <Wire.h>
#include <I2C_LCD.h>
#include <ctrl_joystick.h> 
#include <Arduino.h>
#include <Display.h>

int app_selected = 0; // Variable to keep track of the selected app

void setup() {
  set_joystick_entries(A0, A1, 7); // Set the joystick pins
  setup_display_infos(0x51, 0); // Set the I2C address and page number
  
  Wire.begin();
  Serial.begin(9600);

  display_list(0); // Display the initial list of apps
}

void loop() {
  int x = joytick_position_x(); // Get the joystick X position
  int y = joytick_position_y(); // Get the joystick Y position

  if (y > 4.9) { // If joystick is moved to the right
    app_selected++;
    if (app_selected > 4) {
      app_selected = 0; // Loop back to the first app
    }
    display_list(app_selected); // Update the display with the new selection

  } else if (y < 0.1) { // If joystick is moved to the left
    app_selected--;
    if (app_selected < 0) {
      app_selected = 4; // Loop back to the last app
    }
    display_list(app_selected); // Update the display with the new selection
  }

  if (button_pressed()) { // If the button is pressed
    display_page(app_selected); // Display the selected app page
    delay(1000); // Delay for a second to allow the user to see the selection
  }
}








