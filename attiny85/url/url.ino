#include "DigiKeyboard.h"

void setup() {}

void loop() {
  DigiKeyboard.delay(5000);

  // Open CMD
  DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
  DigiKeyboard.delay(500);
  DigiKeyboard.print("cmd");
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(1000);

  // Make it green and clear the screen
  DigiKeyboard.print("color 02 && cls");
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(500);

  // Run the 'tree' command (shows all files in a cool scrolling list)
  DigiKeyboard.print("tree C:\\");
  DigiKeyboard.sendKeyStroke(KEY_ENTER);

  while(1) { DigiKeyboard.update(); }
}