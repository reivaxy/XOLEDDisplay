


#include "XOLEDDisplay.h"

XOLEDDisplayClass *oledDisplay;
SSD1306 display(0x3C, D5, D6);

unsigned int start;
void setup() {
  Serial.begin(9600);
  // Initialise the OLED display
  oledDisplay = new XOLEDDisplayClass(&display);
  oledDisplay->setTitle("BIG TITLE");
 
  oledDisplay->setLine(0, "Line 0 steady.");
  oledDisplay->setBlinkingLine(1, "Line 1 blinking");
  oledDisplay->setLine(2, "Line 2 permanent");
  oledDisplay->setBlinkingLine(3, "Line 3 blinking fast");
  oledDisplay->setBlinkPeriod(3, 200);
  start = millis();
}

void loop() {
  if (millis() > start + 8000) {
    Serial.println("Transient line 2");
    oledDisplay->setTransientLine(2, "Line 2 transient");
    oledDisplay->setTransientLine(3, "Truncated blinking transient line");
    start = millis();
  }
  oledDisplay->refresh();
  delay(50);  
}