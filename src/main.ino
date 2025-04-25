#include <Wire.h>
#include <I2C_LCD.h>
#include <ctrl_joystick.h> 
#include <Arduino.h>
#include <Display.h>

#define NB_PAGES 6 // Number of pages available
#define TEXT_LENGTH 20 // Length of the text to be displayed
char app_list[NB_PAGES][TEXT_LENGTH] = {"MENU","BAD USB","IR","PONG","SETUP","COP MODE"};

int app_selected = 0; // Variable to keep track of the selected app
int page_selected = 0; // Variable to keep track of the current page

void setup() {
  set_joystick_entries(A0, A1, 7); // Set the joystick pins
  setup_display_infos(0x51, 0); // Set the I2C address and page number
  set_app_list(app_list, NB_PAGES); // Set the app list
  
  Wire.begin();
  Serial.begin(9600);

  display_list(0); // Display the initial list of apps
}

void loop() {
  int x = joytick_position_x(); // Get the joystick X position
  int y = joytick_position_y(); // Get the joystick Y position

  switch (page_selected) {
  case 0: // menu
    if (y > 4.9) { // If joystick is moved to the right
      app_selected++;
      if (app_selected > NB_PAGES - 1) {
        app_selected = 0; // Loop back to the first app
      }
      display_list(app_selected); // Display the initial list of apps

    } else if (y < 0.1) { // If joystick is moved to the left
      app_selected--;
      if (app_selected < 0) {
        app_selected = NB_PAGES - 1; // Loop back to the last app
      }
      display_list(app_selected); // Display the initial list of apps
    }

    

    if (button_pressed()) { // If the button is pressed
      page_selected = app_selected; // Set the current page to the selected app
    }
    break;
  
  case 1:
    display_page(1);
    break;

  case 2:
    display_page(2);
    break;
    
  case 3:
    display_page(3);
    break;
    
  case 4:
    display_page(4);
    break;
    
  default:
    break;
  }
  

  
}
