#include "parameters.h"

#include <Arduino.h>
#include <Display.h>
#include <ctrl_joystick.h>

#define NB_PARAMETERS 2 // Number of parameters available

int backlight_value = 100; // Default backlight value
int contrast_value = 21; // Default contrast value
long timer; // Variable to keep track of time
int selected_parameter = 0; // Variable to keep track of the selected parameter

char parameters[NB_PARAMETERS][20] = {
    "Back light",
    "Contrast",
};

int parameters_states[NB_PARAMETERS] = {100, 21}; // Array to hold parameter values

void parameters_setup() {
    selected_parameter = 0; // Initialize the current parameter
}

void parameters_loop(int x, int y) {
    if (y > 4.9 && millis() - timer > 200) { // If joystick is moved up
      timer = millis(); // Record the time of the joystick movement
      selected_parameter++;
      if (selected_parameter > NB_PARAMETERS - 1) {
        selected_parameter = 0; // Loop back to the first parameter
      }
      display_parameters(selected_parameter); // Display the parameters
    }

    if (y < 0.1 && millis() - timer > 200) { // If joystick is moved down
      timer = millis(); // Record the time of the joystick movement
      selected_parameter--;
      if (selected_parameter < 0) {
        selected_parameter = NB_PARAMETERS - 1; // Loop back to the last parameter
      }
      display_parameters(selected_parameter); // Display the parameters
    }

    if (x > 4.9 && millis() - timer > 100) { // If the button is pressed and held for more than 0.1 second
      timer = millis(); // Record the time of the button press
      LCD.CleanAll(WHITE); // Clean the screen with white
      change_state(selected_parameter); // Change the state of the selected parameter
    }
}

void display_parameters(int parameter_selected) {
    LCD.CharGotoXY(0, 0); // Set the start coordinate
    
    for (int i = 0; i < NB_PARAMETERS; i++) {
        if (i == parameter_selected) {
            LCD.print("-> "); // Indicate the selected parameter
        } else {
            LCD.print("   "); // No indication for unselected parameters
        }
        LCD.print(parameters[i]); // Display each parameter
        LCD.print(": " + String(parameters_states[i]) + " "); // Display the state of each parameter
        LCD.CharGotoXY(0, i*8+8); // Move to the next line
    }
}

void change_state(int parameter_selected) {
    //Slider for backlight
    if (parameter_selected == 0) {
        
        while (!button_pressed()) {
            int x = joystick_position_x(); // Get the joystick X position

            if (x > 4.9) {
                backlight_value++;
                if (backlight_value > 127) {
                    backlight_value = 127;
                }
                parameters_states[0] = backlight_value;
                LCD.BacklightConf(LOAD_TO_RAM, backlight_value);
                display_parameters(0); // Update the display
            }
            
            if (x < 0.1) {
                backlight_value--;
                if (backlight_value < 0) {
                    backlight_value = 0;
                }
                parameters_states[0] = backlight_value;
                LCD.BacklightConf(LOAD_TO_RAM, backlight_value);
                display_parameters(0); // Update the display
            }
        }
    }

    //Slider for contrast
    if (parameter_selected == 1) {
        
        while (!button_pressed()) {
            int x = joystick_position_x(); // Get the joystick X position

            if (x > 4.9) {
                contrast_value++;
                if (contrast_value > 63) {
                    contrast_value = 63;
                }
                parameters_states[1] = contrast_value;
                LCD.ContrastConf(LOAD_TO_RAM, contrast_value);
                display_parameters(1); // Update the display
            }
            
            if (x < 0.1) {
                contrast_value--;
                if (contrast_value < 0) {
                    contrast_value = 0;
                }
                parameters_states[1] = contrast_value;
                LCD.ContrastConf(LOAD_TO_RAM, contrast_value);
                display_parameters(1); // Update the display
            }
        }
    }
}