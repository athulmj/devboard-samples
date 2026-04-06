#include "DigiKeyboard.h"

void setup() {}

void loop() {

  DigiKeyboard.delay(5000); // wait for PC to recognize device

  // Open Run
  DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
  DigiKeyboard.delay(500);

  // Open CMD
  DigiKeyboard.print("cmd");
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(1000);

  // Green hacker style
  DigiKeyboard.print("color 02 && cls");
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(500);

  // Fake hacking text
  DigiKeyboard.print("echo Initializing system access...");
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(800);

  DigiKeyboard.print("echo Connecting to remote server...");
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(800);

  DigiKeyboard.print("echo Scanning network...");
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(800);

  // Show real system info
  DigiKeyboard.print("ipconfig");
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(2000);

  DigiKeyboard.print("systeminfo");
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(2000);

  // Directory tree animation
  DigiKeyboard.print("tree C:\\");
  DigiKeyboard.sendKeyStroke(KEY_ENTER);

  while(true){
    DigiKeyboard.update();
  }
}