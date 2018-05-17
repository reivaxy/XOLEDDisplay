


#include "XOLEDDisplay.h"

XOLEDDisplayClass *oledDisplay;
//SSD1306 display(0x3C, D5, D6);

unsigned int chrono;
unsigned int start;
bool done = false;

int  batteryIcon = 70;
void setup() {
  Serial.begin(9600);
  // Initialise the OLED display
  oledDisplay = new XOLEDDisplayClass(0x3C, D5, D6);
  oledDisplay->setTitle("BIG TITLE");

  oledDisplay->setIcon(1, 70);
  oledDisplay->setIcon(2, 71);
  oledDisplay->setIcon(3, 72, true);
  
  oledDisplay->setLine(0, "Line 0 steady.");
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
  oledDisplay->setIcon(0, batteryIcon);
  batteryIcon--;
  if(batteryIcon < 66) batteryIcon = 70;
  oledDisplay->refresh();
  delay(100);
}