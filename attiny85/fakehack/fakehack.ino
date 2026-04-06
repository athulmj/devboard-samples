#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);
#define MIC_PIN 0
#define BARS    16
#define BAR_W   7

int  heights[BARS]  = {0};
int  peaks[BARS]    = {0};

void setup() {
  Wire.begin(8, 9);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop() {
  // Sample mic
  for (int b = 0; b < BARS; b++) {
    long sum = 0;
    for (int s = 0; s < 20; s++) sum += analogRead(MIC_PIN);
    int avg = sum / 20;
    int h   = map(avg, 1800, 2300, 0, 60);
    h = constrain(h, 0, 60);
    heights[b] = (heights[b] * 2 + h) / 3; // smooth
    if (heights[b] > peaks[b]) peaks[b] = heights[b];
    else if (peaks[b] > 0)     peaks[b]--;
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(30, 0);
  display.println("VISUALIZER");

  for (int b = 0; b < BARS; b++) {
    int x = b * (BAR_W + 1);
    int y = 63 - heights[b];
    display.fillRect(x, y, BAR_W, heights[b], SSD1306_WHITE);
    // Peak dot
    display.drawPixel(x + 3, 63 - peaks[b], SSD1306_WHITE);
  }
  display.display();
  delay(30);
}