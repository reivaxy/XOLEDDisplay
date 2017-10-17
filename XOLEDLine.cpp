/**
 *  Class to handle one line of text on OLED screen, with transient and blinking capabilities
 *  Xavier Grosjean 2017
 *  Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International Public License
 */

#include "XOLEDLine.h"

XOLEDLineClass::XOLEDLineClass() {
}

void XOLEDLineClass::setText(char* text) {
  setText(text, false, false);
}

void XOLEDLineClass::setPosition(int* pos) {
  _posX = pos[0];
  _posY = pos[1];
}

void XOLEDLineClass::setTransientText(char* text) {
  setText(text, true, false);
}
void XOLEDLineClass::setBlinkingText(char* text) {
  setText(text, false, true);
}
void XOLEDLineClass::setBlinkPeriod(unsigned int period) {
  _blinkPeriod = period;
}
void XOLEDLineClass::setTransientDuration(unsigned int duration) {
  _transientDuration = duration;
}

void XOLEDLineClass::setText(char* text, bool transient, bool blink) {
  char **targetText = &_text;
  unsigned long now = millis();

  if (transient) {
    targetText = &_transientText;
    _transientStartDate = now;
  }
  
  // Initialize blinking if required
  if (blink) {
    _lastBlinkDate = now;
  } else {
    _lastBlinkDate = 0;
  }
  if (*targetText != NULL) {
    free(*targetText);
    *targetText = NULL;
  }
  int len = min(strlen(text), MAX_LINE_LENGTH);
  Serial.println(len);
  *targetText = (char*)malloc(len + 1) ;
  strncpy(*targetText, text, len);
  (*targetText)[len] = 0;
}

void XOLEDLineClass::refresh(SSD1306* display) {
  unsigned long now = millis();
  
  if (_lastBlinkDate != 0) {
    if (now > _lastBlinkDate + _blinkPeriod) {
      _blinkHide = !_blinkHide;
      _lastBlinkDate = now;
    }
  }
  if (_blinkHide) {
    return;
  }
  display->setFont(_font);
  display->setTextAlignment(_alignment);
  if (_transientText != NULL) {
    if (now > _transientStartDate + _transientDuration) {
      free(_transientText);
      _transientText = NULL;
      _transientStartDate = 0;
    }
  }
  if (_transientText != NULL) {
      display->drawString(_posX, _posY, String(_transientText));
    } else {
    if (_text != NULL) {
      display->drawString(_posX, _posY, String(_text));
    }
  }
}