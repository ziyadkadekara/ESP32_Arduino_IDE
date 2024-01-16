#include <Wire.h>
#include <Adafruit_SSD1306.h>

// OLED display configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Game variables
int bird_x = 32;
int bird_y = SCREEN_HEIGHT / 2;
int bird_dy = 0;  // Bird's vertical speed

int pipe_x = SCREEN_WIDTH;
int pipe_gap = 40;
int pipe_width = 15;

int score = 0;

//birds bitmap 
const uint8_t bird_bitmap[] = {
  0b11110000, // First row of pixels (MSB to LSB)
  0b10011000,
  0b00111100,
  0b00010010,
  0b00000010,
  0b00000110,
  0b00011110,
  0b00110000,
};


// Buttons for control
const int buttonPin = 15;  // Replace with your button pin

void setup() {
  // Initialize display and button
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // Check for button press
  if (!digitalRead(buttonPin)) {
    bird_dy = -5;  // Jump when button pressed
  }

  // Bird movement
  bird_y += bird_dy;
  bird_dy += 1;  // Gravity

  // Keep bird within screen bounds
  bird_y = constrain(bird_y, 0, SCREEN_HEIGHT - 8);

  // Pipe movement
  pipe_x -= 2;
  if (pipe_x < -pipe_width) {
    pipe_x = SCREEN_WIDTH;
    score++;
  }

  // Collision detection
  if (bird_x + 8 >= pipe_x && bird_x + 8 <= pipe_x + pipe_width &&
      (bird_y <= 0 || bird_y + 8 >= SCREEN_HEIGHT - pipe_gap)) {
    // Game over
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(30, 20);
    display.println("Game Over");
    display.display();
    while (true) {}  // Stop the game
  }

  // Clear display and draw game elements
  display.clearDisplay();
  display.drawRect(pipe_x, 0, pipe_width, SCREEN_HEIGHT - pipe_gap-10, WHITE);
  display.drawRect(pipe_x, SCREEN_HEIGHT - pipe_gap + pipe_width, pipe_width, SCREEN_HEIGHT, WHITE);
  display.drawBitmap(bird_x, bird_y, bird_bitmap, 8, 8, WHITE);  // Replace with your bird bitmap
  display.display();

  delay(10);  // Adjust delay for desired speed
}
