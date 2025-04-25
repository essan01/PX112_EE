#include <Wire.h>
#include <I2C_LCD.h>
#include <ctrl_joystick.h> 
#include <Arduino.h>
#include <Display.h>

#define NB_APPS 6 // Number of apps available
char app_list[NB_APPS][20] = {"MENU","BAD USB","IR","PONG","SETUP","COP MODE"};

int app_selected = 0; // Variable to keep track of the selected app
int page_selected = 0; // Variable to keep track of the current page

void setup() {
  set_joystick_entries(A0, A1, 7); // Set the joystick pins
  setup_display_infos(0x51, 0); // Set the I2C address and page number
  set_app_list(app_list, NB_APPS); // Set the app list
  
  Wire.begin();
  Serial.begin(9600);

  display_list(0); // Display the initial list of apps
}

void loop() {
  int x = joytick_position_x(); // Get the joystick X position
  int y = joytick_position_y(); // Get the joystick Y position

  if (x < 0.1) {
    page_selected = 0; // If joystick is moved to the left, go to menu
    app_selected = 0; // Reset app selection
    display_list(app_selected); // Display the initial list of apps
  }
  
  switch (page_selected) {
  case 0: // menu
    if (y > 4.9) { // If joystick is moved to the right
      app_selected++;
      if (app_selected > NB_APPS - 1) {
        app_selected = 0; // Loop back to the first app
      }
      display_list(app_selected); // Display the initial list of apps

    } else if (y < 0.1) { // If joystick is moved to the left
      app_selected--;
      if (app_selected < 0) {
        app_selected = NB_APPS - 1; // Loop back to the last app
      }
      display_list(app_selected); // Display the initial list of apps
    }

    if (button_pressed()) { // If the button is pressed
      page_selected = app_selected; // Set the current page to the selected app
    }
    break;
  
  case 1:
    display_page(1); //replace with the function to display the app
    break;

  case 2:
    display_page(2); //replace with the function to display the app
    break;
    
  case 3:
    display_page(3); //replace with the function to display the app
    break;
    
  case 4:
    display_page(4); //replace with the function to display the app
    break;
    
  default:
    break;
  }
  

  
}
