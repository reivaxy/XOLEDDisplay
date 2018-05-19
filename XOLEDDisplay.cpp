/**
 *  Class to handle displaying lines on an OLED screen, with transient and blinking capabilities
 *  Xavier Grosjean 2017
 *  MIT License 
 */

#include "XOLEDDisplay.h"

XOLEDDisplayClass::XOLEDDisplayClass(int addr, int sda, int scl) {
  SSD1306* display = new SSD1306(addr, sda, scl);
  _init(display);
}

XOLEDDisplayClass::XOLEDDisplayClass(SSD1306* display) {
  _init(display);
}

SSD1306* XOLEDDisplayClass::getDisplay() {
  return _display;
}

void XOLEDDisplayClass::_init(SSD1306* display) {
  _display = display;
  _display->init();
  _display->flipScreenVertically();
  _title.setFont(ArialMT_Plain_13);
  _title.setPosition(_titlePositions);
  _title.setAlignment(TEXT_ALIGN_CENTER);
    
  for(byte  i = 0; i < NB_LINES; i++) {
    _lines[i].setPosition(_linePositions[i]);
  }
  _lines[4].setAlignment(TEXT_ALIGN_RIGHT);
  for(byte  i = 0; i < NB_ICONS; i++) {
    _icons[i].setPosition(_iconPositions[i]);
    _icons[i].setFont(XOLEDIconFont);
  }
};

void XOLEDDisplayClass::setIcon(int offset, char icon, bool blink) {
  _icons[offset].setIcon(icon, blink);
}
void XOLEDDisplayClass::setIcon(int offset, char icon) {
  _icons[offset].setIcon(icon, false);
}
void XOLEDDisplayClass::blinkIcon(int offset, bool blink) {
  _icons[offset].setBlink(blink);
  syncBlinking();
}

char XOLEDDisplayClass::getIconChar(int offset) {
  return _icons[offset].getText()[0];
}

void XOLEDDisplayClass::setIconFont(const char* font) {
  for(byte  i = 0; i < NB_ICONS; i++) {
    _icons[i].setFont(XOLEDIconFont);
  }
}

void XOLEDDisplayClass::setTitle(const char* title) {
  _title.setText(title);
}
void XOLEDDisplayClass::setTitleFont(const char* font) {

}  

void XOLEDDisplayClass::setLine(int offset, const char* text) {
  if (offset >= NB_LINES) return;
  _lines[offset].setText(text);   
}
void XOLEDDisplayClass::setTransientLine(int offset, const char* text) {
  if (offset >= NB_LINES) return;
  _lines[offset].setTransientText(text);   
}
void XOLEDDisplayClass::setBlinkingLine(int offset, const char* text) {
  if (offset >= NB_LINES) return;
  _lines[offset].setBlinkingText(text);
  // We probably want all blinking lines (with same period) to be in sync
  syncBlinking();
}
void XOLEDDisplayClass::setLineFont(const unsigned char* font) {
  for(byte  i = 0; i < NB_LINES; i++) {
    _lines[i].setFont(font);
  }
}
void XOLEDDisplayClass::setLineAlignment(int offset, OLEDDISPLAY_TEXT_ALIGNMENT alignment) {
  _lines[offset].setAlignment(alignment);
}
void XOLEDDisplayClass::setLinePosition(int offset, int x, int y) {
  _lines[offset].setPosition(x, y);
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

void XOLEDDisplayClass::setLine(int offset, const char* text, bool transient, bool blink) {
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

void XOLEDDisplayClass::heartBeatOn() {
  _heartBeatOn = true;
}
void XOLEDDisplayClass::heartBeatOff() {
  _heartBeatOn = false;
}
void XOLEDDisplayClass::setHeartBeatposition(int x, int y) {
  _heartBeatX = x;
  _heartBeatY = y;
}
  
void XOLEDDisplayClass::refresh(void) {
  _display->clear();
  if (_heartBeatOn) {
    unsigned long now = millis();
    if (now > _lastHeartBeat + 500) {
      _lastHeartBeat = now;
      _heartBeatHide = !_heartBeatHide;
    }
  } else {
    _heartBeatHide = true;
  }
  if (!_heartBeatHide) {
    _display->setPixel(_heartBeatX, _heartBeatY);
  }
  _title.refresh(_display);    
  for(byte  i = 0; i < NB_LINES; i++) {
    _lines[i].refresh(_display);
  }
  for(byte  i = 0; i < NB_ICONS; i++) {
    _icons[i].refresh(_display);
  }
  _display->display();
}
