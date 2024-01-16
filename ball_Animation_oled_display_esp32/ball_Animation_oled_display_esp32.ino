#include <Wire.h>
#include <Adafruit_SSD1306.h>

// OLED display configuration (adjust as needed)
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Variables for animation elements (e.g., ball position, shape properties)
int ball_x = 0;
int ball_y = 0;
int ball_radius = 4;
int ball_dx = 2;  // Change in x-position for each frame
int ball_dy = 2;  // Change in y-position for each frame

void setup() {
  // Initialize display
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.clearDisplay();
}

void loop() {
  // Clear the display
  display.clearDisplay();

  // Draw animation elements
  display.drawCircle(ball_x, ball_y, ball_radius, WHITE);

  // Update animation variables (e.g., change positions, shapes)
  ball_x += ball_dx;
  ball_y += ball_dy;

  // Bounce off walls
  if (ball_x < 0 || ball_x > SCREEN_WIDTH - ball_radius * 2) {
    ball_dx = -ball_dx;
  }
  if (ball_y < 0 || ball_y > SCREEN_HEIGHT - ball_radius * 2) {
    ball_dy = -ball_dy;
  }

  // Show the updated display
  display.display();

  // Delay for smoother animation
  delay(10); // Adjust delay as needed
}
