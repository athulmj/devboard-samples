#include "DigiKeyboard.h"

void setup() {
  pinMode(1, OUTPUT);
}

void loop() {
  DigiKeyboard.delay(5000); // 5-second safety window

  // Open the Run dialog (Windows + R)
  DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
  DigiKeyboard.delay(800);

  // Type a URL and hit Enter
  // Example: A 10-hour loop of relaxing music (or change to any link)
  DigiKeyboard.print("https://www.youtube.com/watch?v=dQw4w9WgXcQ");
  DigiKeyboard.sendKeyStroke(KEY_ENTER);

  // Signal completion with LED
  digitalWrite(1, HIGH);
  while(1) { DigiKeyboard.update(); } 
}