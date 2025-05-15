#ifndef CTRL_JOYSTICK_H
#define CTRL_JOYSTICK_H

void set_joystick_entries(int x, int y, int button);
float joystick_position_x();
float joystick_position_y();
int button_pressed();

#endif