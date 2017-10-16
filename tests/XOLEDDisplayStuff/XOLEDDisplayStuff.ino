


#include "XOLEDDisplay.h"

XOLEDDisplayClass *oledDisplay;
SSD1306 display(0x3C, D5, D6);

unsigned int start;
void setup() {
  // Initialise the OLED display
  oledDisplay = new XOLEDDisplayClass(&display);
  oledDisplay->setTitle("Big Title");
 
  oledDisplay->setLine(0, "Line 0 steady");
  oledDisplay->setLine(1, "Line 1 blinking", false, true);
  oledDisplay->setLine(2, "Line 2 permanent");
  oledDisplay->setLine(3, "Line 3");
  start = millis();
}

void loop() {
  Serial.println("tic"); 
  if (millis() > start + 8000) {
    Serial.println("Transient line 2");
    oledDisplay->setLine(2, "Line 2 transient", true, false);
    start = millis();
  }
  oledDisplay->refresh();
  delay(50);  
}