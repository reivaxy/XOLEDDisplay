/**
 *  Class to handle displaying lines on an OLED screen, with transient and blinking capabilities
 *  Xavier Grosjean 2017
 *  Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International Public License
 */

#include "XOLEDDisplay.h"

XOLEDDisplayClass::XOLEDDisplayClass(SSD1306* display) {
  _display = display;
  _display->init();
  _display->flipScreenVertically();
  _title[0] = 0;
  for(byte  i = 0; i < NB_LINES; i++) {
    _lines[i].setPosition(_linePositions[i]);
  }  
};

void XOLEDDisplayClass::setTitle(char* title) {
  strncpy(_title, title, MAX_TITLE_LENGTH);
  _title[MAX_TITLE_LENGTH] = 0;
}  

void XOLEDDisplayClass::setLine(int offset, char* text) {
  _lines[offset].setText(text);   
}
void XOLEDDisplayClass::setLine(int offset, char* text, bool transient, bool blink) {
  _lines[offset].setText(text, transient, blink);   
}

void XOLEDDisplayClass::display(void) {
  Serial.println("DISPLAY");
  _display->clear();
  _display->setFont(ArialMT_Plain_16);
  _display->setTextAlignment(TEXT_ALIGN_CENTER);
  _display->drawString(64, 0, _title);  

  for(byte  i = 0; i < NB_LINES; i++) {
    _lines[i].refresh(_display);
  }

  _display->display();
}
