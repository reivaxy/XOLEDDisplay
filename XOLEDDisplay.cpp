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
  if (offset >= NB_LINES) return;
  _lines[offset].setText(text);   
}
void XOLEDDisplayClass::setTransientLine(int offset, char* text) {
  if (offset >= NB_LINES) return;
  _lines[offset].setTransientText(text);   
}
void XOLEDDisplayClass::setBlinkingLine(int offset, char* text) {
  if (offset >= NB_LINES) return;
  _lines[offset].setBlinkingText(text);
  // We probably want all blinking lines (with same period) to be in sync
  _syncBlinkingLines();
}

void XOLEDDisplayClass::_syncBlinkingLines() {
  for(byte i = 0; i < NB_LINES; i++) {
    _lines[i].syncBlink();
  }
}
void XOLEDDisplayClass::blinkLine(int offset, bool flag) {
  if (offset >= NB_LINES) return;
  _lines[offset].setBlink(flag);
  if (flag) {
    _syncBlinkingLines();
  }
}

void XOLEDDisplayClass::setLine(int offset, char* text, bool transient, bool blink) {
  if (offset >= NB_LINES) return;
  _lines[offset].setText(text, transient, blink);   
}
void XOLEDDisplayClass::setBlinkPeriod(int offset, unsigned int period) {
  if (offset >= NB_LINES) return;
  _lines[offset].setBlinkPeriod(period);   
}
void XOLEDDisplayClass::setTransientDuration(int offset, unsigned int duration) {
  if (offset >= NB_LINES) return;
  _lines[offset].setTransientDuration(duration);   
}

void XOLEDDisplayClass::refresh(void) {
  _display->clear();
  _display->setFont(ArialMT_Plain_16);
  _display->setTextAlignment(TEXT_ALIGN_CENTER);
  _display->drawString(64, 0, _title);  
  for(byte  i = 0; i < NB_LINES; i++) {
    _lines[i].refresh(_display);
  }
  _display->display();
}
