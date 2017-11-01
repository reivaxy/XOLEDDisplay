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
  _title.setFont(ArialMT_Plain_16);
  _title.setPosition(_titlePositions);
  _title.setAlignment(TEXT_ALIGN_CENTER);
    
  for(byte  i = 0; i < NB_LINES; i++) {
    _lines[i].setPosition(_linePositions[i]);
  }
  for(byte  i = 0; i < NB_ICONS; i++) {
    _icons[i].setPosition(_iconPositions[i]);
    _icons[i].setFont(My_Font);
  }
};

void XOLEDDisplayClass::setIcon1(char icon, bool blink) {
  _icons[0].setIcon(icon, blink);
}
void XOLEDDisplayClass::setIcon1(char icon) {
  _icons[0].setIcon(icon, false);
}
void XOLEDDisplayClass::setIcon2(char icon, bool blink) {
  _icons[1].setIcon(icon, blink);
}
void XOLEDDisplayClass::setIcon2(char icon) {
  _icons[1].setIcon(icon, false);
}
void XOLEDDisplayClass::setIcon3(char icon, bool blink) {
  _icons[2].setIcon(icon, blink);
}
void XOLEDDisplayClass::setIcon3(char icon) {
  _icons[2].setIcon(icon, false);
}
void XOLEDDisplayClass::setIcon4(char icon, bool blink) {
  _icons[3].setIcon(icon, blink);
}
void XOLEDDisplayClass::setIcon4(char icon) {
  _icons[3].setIcon(icon, false);
}
void XOLEDDisplayClass::blinkIcon1(bool blink) {
  _icons[0].setBlink(blink);
}
void XOLEDDisplayClass::blinkIcon2(bool blink) {
  _icons[1].setBlink(blink);
}
void XOLEDDisplayClass::blinkIcon3(bool blink) {
  _icons[2].setBlink(blink);
}
void XOLEDDisplayClass::blinkIcon4(bool blink) {
  _icons[3].setBlink(blink);
}
void XOLEDDisplayClass::setIconFont(const char* font) {
  for(byte  i = 0; i < NB_ICONS; i++) {
    _icons[i].setFont(My_Font);
  }
}

void XOLEDDisplayClass::setTitle(char* title) {
  _title.setText(title);
}
void XOLEDDisplayClass::setTitleFont(const char* font) {

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
  syncBlinking();
}
void XOLEDDisplayClass::setLineFont(const char* font) {
  for(byte  i = 0; i < NB_LINES; i++) {
    _lines[i].setFont(My_Font);
  }
}

/**
 *  We want all blinking element to blink in sync
 */
void XOLEDDisplayClass::syncBlinking() {
  for(byte l = 0; l < NB_LINES; l++) {
    _lines[l].syncBlink();
  }
  for(byte i = 0; i < NB_ICONS; i++) {
    _icons[i].syncBlink();
  }
}
void XOLEDDisplayClass::blinkLine(int offset, bool flag) {
  if (offset >= NB_LINES) return;
  _lines[offset].setBlink(flag);
  if (flag) {
    syncBlinking();
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
  _title.refresh(_display);    
  for(byte  i = 0; i < NB_LINES; i++) {
    _lines[i].refresh(_display);
  }
  for(byte  i = 0; i < NB_ICONS; i++) {
    _icons[i].refresh(_display);
  }
  _display->display();
}
