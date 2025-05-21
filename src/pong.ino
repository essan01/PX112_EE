#include <Arduino.h>
#include <Display.h>
#include <ctrl_joystick.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define GAME_SPEED 2

int ball_x, ball_y; // Ball position
float ball_dx, ball_dy; // Ball direction
int paddle1_x, paddle1_y; // Paddle 1 position
int paddle2_x, paddle2_y; // Paddle 2 position

void init_game() {
    LCD.CleanAll(BLACK); // Clear the screen
    ball_x = SCREEN_WIDTH / 2;
    ball_y = SCREEN_HEIGHT / 2;
    ball_dx = GAME_SPEED;
    ball_dy = GAME_SPEED;
    paddle1_x = 10;
    paddle1_y = SCREEN_HEIGHT / 2;
    paddle2_x = SCREEN_WIDTH - 10;
    paddle2_y = SCREEN_HEIGHT / 2;
    draw_ball();
    draw_paddle();
}

void move_ball() {
    // Update ball position
    ball_x += ball_dx;
    ball_y += ball_dy;
    
    if (ball_y <= 0 || ball_y >= SCREEN_HEIGHT) {
        ball_dy = -ball_dy; // Reverse direction
    }
}

void move_paddle() {
    int y = joystick_position_y();

    if (y > 4.9) {
        paddle1_y += GAME_SPEED; // Move paddle 1 up
        if (paddle1_y > SCREEN_HEIGHT - 20) {
            paddle1_y = SCREEN_HEIGHT - 20; // Prevent going out of bounds
        }
    } else if (y < 0.1) {
        paddle1_y -= GAME_SPEED; // Move paddle 1 down
        if (paddle1_y < 0) {
            paddle1_y = 0; // Prevent going out of bounds
        }
    }
}

void move_ai_paddle() {
    // Simple AI for paddle 2
    if (ball_y > paddle2_y + 10) {
        paddle2_y += GAME_SPEED; // Move paddle 2 down
        if (paddle2_y > SCREEN_HEIGHT - 20) {
            paddle2_y = SCREEN_HEIGHT - 20; // Prevent going out of bounds
        }
    } else if (ball_y < paddle2_y + 10) {
        paddle2_y -= GAME_SPEED; // Move paddle 2 up
        if (paddle2_y < 0) {
            paddle2_y = 0; // Prevent going out of bounds
        }
    }
}

void check_collision() {
    // Check for collision between ball and paddles
    if (ball_x <= paddle1_x + 2 && ball_x >= paddle1_x && ball_y <= paddle1_y + 20 && ball_y >= paddle1_y) {
        ball_dx = -ball_dx; // Reverse direction and increase speed
    }
    if (ball_x <= paddle2_x + 2 && ball_x >= paddle2_x && ball_y <= paddle2_y + 20 && ball_y >= paddle2_y) {
        ball_dx = -ball_dx; // Reverse direction and increase speed
    }
}

void draw_ball() {
    // Draw the ball
    LCD.DrawCircleAt(ball_x, ball_y, 2, WHITE_FILL);
}

void draw_paddle() {
    // Draw paddle 1
    LCD.DrawRectangleAt(paddle1_x, paddle1_y, 2, 20, WHITE_FILL);
    // Draw paddle 2
    LCD.DrawRectangleAt(paddle2_x, paddle2_y, 2, 20, WHITE_FILL);
}

void game_loop() {
    // Clear the screen
    LCD.CleanAll(BLACK);
    
    // Check for collision
    check_collision();

    // Move ball and paddle
    move_ball();
    move_paddle();
    move_ai_paddle();

    // Draw ball and paddles
    draw_ball();
    draw_paddle();
}