#include "parameters.h"

#include <Arduino.h>
#include <I2C_LCD.h>
#include <Display.h>
#include <ctrl_joystick.h>

#define nb_parameters 2 // Number of parameters available


int backlight_value = 100;
int contrast_value = 21;

char parameters[nb_parameters][20] = {
    "Back light",
    "Contrast",
};

int parameters_states[nb_parameters] = {100, 21}; // Array to hold parameter values

int current_parameter = 0; // Variable to keep track of the selected parameter

void display_parameters(int parameter_selected) {
    LCD.CleanAll(WHITE); // Clean the screen with white

    display_parameters_list(parameter_selected);// Display the list of parameters
}

void display_parameters_list(int parameter_selected) {
    LCD.CharGotoXY(0, 0); // Set the start coordinate
    
    for (int i = 0; i < nb_parameters; i++) {
        if (i == parameter_selected) {
            LCD.print("-> "); // Indicate the selected parameter
        } else {
            LCD.print("   "); // No indication for unselected parameters
        }
        LCD.print(parameters[i]); // Display each parameter
        LCD.print(": " + String(parameters_states[i])); // Display the state of each parameter
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