#include <Wire.h>
#include <I2C_LCD.h>
#include <ctrl_joystick.h> 
#include <Arduino.h>
#include <Display.h>
#include <parameters.h>

#define NB_APPS 6 // Number of apps available
#define NB_PARAMETERS 2 // Number of parameters available

char app_list[NB_APPS][20] = {"MENU","BAD USB","IR","PONG","SETUP","COP MODE"};

int parameter_selected = 0; // Variable to keep track of the selected parameter
int app_selected = 0; // Variable to keep track of the selected app
int page_selected = 0; // Variable to keep track of the current page

long press_time;

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
    app_selected = 0; // Reset app selection
    display_list(app_selected); // Display the initial list of apps
  }
  
  switch (page_selected) {
  case 0: // menu
    if (y > 4.9) { // If joystick is moved up
      app_selected++;
      if (app_selected > NB_APPS - 1) {
        app_selected = 0; // Loop back to the first app
      }
      display_list(app_selected); // Display the list of apps
    }

    if (y < 0.1) { // If joystick is moved down
      app_selected--;
      if (app_selected < 0) {
        app_selected = NB_APPS - 1; // Loop back to the last app
      }
      display_list(app_selected); // Display the list of apps
    }

    if (button_pressed()) { // If the button is pressed
      page_selected = app_selected; // Set the current page to the selected app
      if (page_selected == 4) {
        display_parameters(0);
      }
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
  
    if (y > 4.9) { // If joystick is moved up
      parameter_selected++;
      if (parameter_selected > NB_PARAMETERS - 1) {
        parameter_selected = 0; // Loop back to the first parameter
      }
      display_parameters(parameter_selected); // Display the parameters
    }
    
    if (y < 0.1) { // If joystick is moved down
      parameter_selected--;
      if (parameter_selected < 0) {
        parameter_selected = NB_PARAMETERS - 1; // Loop back to the last parameter
      }
      display_parameters(parameter_selected); // Display the parameters
    }

    if (x > 4.9 && millis() - press_time > 100) { // If the button is pressed and held for more than 0.1 second
      press_time = millis(); // Record the time of the button press
      LCD.CleanAll(WHITE); // Clean the screen with white
      change_state(parameter_selected); // Change the state of the selected parameter
    }

    break;
    
  default:
    break;
  }  
}
