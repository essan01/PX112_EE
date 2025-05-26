#include <Wire.h>
#include <I2C_LCD.h>
#include <ctrl_joystick.h> 
#include <Arduino.h>
#include <Display.h>
#include <pong.h>
#include <parameters.h>
#include <IR.h>

#include <IRremote.hpp> 

#define NB_APPS 6 // Number of apps available
#define NB_PARAMETERS 2 // Number of parameters available

char app_list[NB_APPS][20] = {"MENU","RFID","IR","PONG","SETUP","COP MODE"};

int app_selected = 0; // Variable to keep track of the selected app
int page_selected = 0; // Variable to keep track of the current page
long time; // Variables to keep track of time

extern GUI_Bitmap_t bmowo; // Bitmap for the image

void setup() {
  set_joystick_entries(A0, A1, 7); // Set the joystick pins
  setup_display_infos(0x51, 0); // Set the I2C address and page number
  set_app_list(app_list, NB_APPS); // Set the app list
  
  Wire.begin();
  Serial.begin(9600);

  display_list(0); // Display the initial list of apps
}

void loop() {
  int x = joystick_position_x(); // Get the joystick X position
  int y = joystick_position_y(); // Get the joystick Y position

  if (x < 0.1) {
    LCD.CleanAll(WHITE); // Clean the screen with white
    page_selected = 0; // If joystick is moved to the left, go to menu
    // app_selected = 0; // Reset app selection when going back to menu
    display_list(app_selected); // Display the initial list of apps
  }
  
  switch (page_selected) {
  case 0: // menu
    if (y > 4.9 && millis() - time > 200) { // If joystick is moved up
      time = millis(); // Record the time of the joystick movement
      app_selected++;
      if (app_selected > NB_APPS - 1) {
        app_selected = 0; // Loop back to the first app
      }
      display_list(app_selected); // Display the list of apps
    }

    if (y < 0.1 && millis() - time > 200) { // If joystick is moved down
      time = millis(); // Record the time of the joystick movement
      app_selected--;
      if (app_selected < 0) {
        app_selected = NB_APPS - 1; // Loop back to the last app
      }
      display_list(app_selected); // Display the list of apps
    }

    if (button_pressed()) { // If the button is pressed
      page_selected = app_selected; // Set the current page to the selected app

      if (page_selected == 3) { // If the selected app is PONG
        init_game(); // Initialize the game
      }
      if (page_selected == 4) {
        LCD.CleanAll(WHITE); // Clean the screen with white
        parameters_setup(); // Set up the parameters
        display_parameters(0);
      }
    }

    break;
    
  case 1:

    break;

  case 2:
    
    app_IR();
    break;
    
  case 3:
    game_loop(); // Call the game loop function
    break;

  case 4:
    parameters_loop(x, y);
    break;
    
  case 5:
    LCD.CleanAll(WHITE); // Clean the screen with white
    LCD.WorkingModeConf(OFF, ON, WM_BitmapMode);
    LCD.DrawScreenAreaAt(&bmowo, 30, 0);

    while (!(x < 0.1)) {x = joystick_position_x();} // Wait for joystick to be moved to the left

    LCD.WorkingModeConf(OFF, ON, WM_CharMode); // Set the working mode of the LCD
    break;

  default:
    break;
  }  
}
