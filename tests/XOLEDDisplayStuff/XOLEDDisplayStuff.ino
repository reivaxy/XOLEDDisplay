


#include "XOLEDDisplay.h"

XOLEDDisplayClass *oledDisplay;
SSD1306 display(0x3C, D5, D6);

unsigned int chrono;
unsigned int start;
bool done = false;

void setup() {
  Serial.begin(9600);
  // Initialise the OLED display
  oledDisplay = new XOLEDDisplayClass(&display);
  oledDisplay->setTitle("BIG TITLE");

  oledDisplay->setLeftIcon1(1);
  oledDisplay->setLeftIcon2(2);
  oledDisplay->setRightIcon1(3);
  oledDisplay->setRightIcon2(4, true);
  
  
  oledDisplay->setLine(0, "Line 0 steady ! éLp#M\"\"");
  oledDisplay->setBlinkingLine(1, "Line 1 blinking");
  oledDisplay->setLine(2, "Line 2 permanent");
  oledDisplay->setBlinkingLine(3, "Line 3 blinking fast");
  oledDisplay->setBlinkPeriod(3, 200);
  start = millis();
  chrono = start;

}

void loop() {
  unsigned int now = millis();
  // Every 8 seconds, display transient messages on lines 2 and 3
  if (now > chrono + 8000) {
    oledDisplay->setTransientLine(2, "Line 2 transient");
    oledDisplay->setTransientLine(3, "Truncated blinking transient line");
    chrono = now;
  }
  // 5.5 seconds after begining, set line 2 as blinking. Blinking Lines should be in sync (except fast blinking one)
  if (!done && now > start + 5500) {
    oledDisplay->blinkLine(2, true);
    done = true;
  }

  oledDisplay->refresh();
  delay(200);
}