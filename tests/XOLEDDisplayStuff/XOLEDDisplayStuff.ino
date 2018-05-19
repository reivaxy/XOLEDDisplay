


#include "XOLEDDisplay.h"

XOLEDDisplayClass *oledDisplay;
//SSD1306 display(0x3C, D5, D6);

unsigned int chrono8 = 0;
unsigned int chrono2 = 0;
unsigned int start;
bool done = false;
char message[] = "A!BC'D'E.F,GHIJ_K\"L\"MNOP QRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
char* firstChar = message;
char title[8];

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
  chrono8 = start;
  chrono2 = start;
}

void loop() {
  unsigned int now = millis();
  // Every 8 seconds, display transient messages on lines 2 and 3
  if (now > chrono8 + 8000) {
    oledDisplay->setTransientLine(2, "Line 2 transient");
    oledDisplay->setTransientLine(3, "Truncated blinking transient line");
    chrono8 = now;
  }
    
  if (now > chrono2 + 2000) {
    strncpy(title, firstChar, 7);
    title[7] = 0;
    firstChar += 7;
    if(firstChar > message + strlen(message)) firstChar = message;
    oledDisplay->setTitle((const char *)title);
    chrono2 = now;
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