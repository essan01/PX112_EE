#include <arduino.h>
#include <ctrl_joystick.h> 

int axeX;
int axeY;
int BP7;

void set_joystick_entries(int x, int y, int button) {
    axeX = x;
    axeY = y;
    BP7 = button;
    pinMode(axeX, INPUT);
    pinMode(axeY, INPUT);
    pinMode(BP7, INPUT);
    digitalWrite(BP7, HIGH); 
}

float joytick_position_x() {
    int x = analogRead(axeX);
    float position = x * (5.0 / 1023.0);
    return position;
}

float joytick_position_y() {
    int y = analogRead(axeY);
    float position = y * (5.0 / 1023.0);
    return position;
}

int button_pressed() {
    int button = digitalRead(BP7);
    if (button == LOW) {
        return 1; // Button is pressed
    } else {
        return 0; // Button is not pressed
    }
}