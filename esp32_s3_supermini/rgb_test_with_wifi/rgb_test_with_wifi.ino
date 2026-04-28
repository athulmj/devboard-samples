#include <WiFi.h>
#include "time.h"
#include <FastLED.h>

// --- Wi-Fi Credentials ---
const char* ssid     = "YOUR_WIFI";
const char* password = "YOUR_PASS";

// --- NTP Time Settings ---
const char* ntpServer = "pool.ntp.org";
// IST is GMT+5:30. 5.5 hours * 3600 seconds = 19800 seconds
const long  gmtOffset_sec = 19800; 
const int   daylightOffset_sec = 0; // India does not use Daylight Saving Time

// --- Onboard LED Settings (ESP32-S3 Super Mini) ---
#define LED_PIN     21 // Pin 21 is standard for the S3 Super Mini's RGB LED
#define NUM_LEDS    1
#define BRIGHTNESS  50 // Keep this low (0-255) to avoid blinding yourself!
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

void setup() {
  // Remember: Set "USB CDC On Boot" to "Enabled" in the Tools menu!
  Serial.begin(115200);
  
  // Initialize the built-in RGB LED
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  
  // Connect to Wi-Fi
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(ssid, password);
  
  // Animate the LED pulsing YELLOW while connecting
  while (WiFi.status() != WL_CONNECTED) {
    leds[0] = CRGB::Yellow;
    FastLED.show();
    delay(250);
    leds[0] = CRGB::Black;
    FastLED.show();
    delay(250);
    Serial.print(".");
  }
  
  Serial.println("\nWiFi connected!");
  
  // Flash GREEN once connected
  leds[0] = CRGB::Green;
  FastLED.show();
  delay(1000);

  // Initialize and fetch the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

void printLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  // Prints time in a clean format: "Monday, April 27 2026 23:58:19"
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

void loop() {
  // 1. Print the time to the Serial Monitor every 1 second
  static unsigned long lastTime = 0;
  if (millis() - lastTime > 1000) {
    printLocalTime();
    lastTime = millis();
  }

  // 2. Play a continuous rainbow color-cycling animation on the built-in LED
  static uint8_t hue = 0;
  leds[0] = CHSV(hue++, 255, 255);
  FastLED.show();
  delay(15); // Adjust this delay to make the animation faster or slower
}