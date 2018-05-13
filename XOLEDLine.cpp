/**
 *  Class to handle one line of text on OLED screen, with transient and blinking capabilities
 *  Xavier Grosjean 2017
 *  MIT License 
 */

#include "XOLEDLine.h"

XOLEDLineClass::XOLEDLineClass() {
}

void XOLEDLineClass::setText(const char* text) {
  setText(text, false, false);
}

/**
 * This call preserves the blinking property of the line
 *
 */
void XOLEDLineClass::setTransientText(const char* text) {
  setText(text, true, _lastBlinkDate != 0);
}
void XOLEDLineClass::setBlinkingText(const char* text) {
  setText(text, false, true);
}
void XOLEDLineClass::setBlinkPeriod(unsigned int period) {
  _blinkPeriod = period;
}
void XOLEDLineClass::setTransientDuration(unsigned int duration) {
  _transientDuration = duration;
}

void XOLEDLineClass::setPosition(int* pos) {
  setPosition(pos[0], pos[1]);
}
void XOLEDLineClass::setPosition(int x, int y) {
  _posX = x;
  _posY = y;
}

void XOLEDLineClass::setIcon(char icon, bool blink) {
  char text[2];
  text[0] = icon;
  text[1] = 0;
  setText(text, false, blink);
}

void XOLEDLineClass::setIcon(char icon) {
  setIcon(icon, false);
}
void XOLEDLineClass::setAlignment(OLEDDISPLAY_TEXT_ALIGNMENT alignment) {
  _alignment = alignment;
}

void XOLEDLineClass::setFont(const unsigned char* font) {
  _font = font;
}

void XOLEDLineClass::setBlink(bool flag) {
  if (flag) {
    _lastBlinkDate = millis();
  } else {
    _lastBlinkDate = 0;
  }
}

void XOLEDLineClass::syncBlink(void) {
  if(_lastBlinkDate != 0) {
    _lastBlinkDate = millis();;
    _blinkHide = false;
  }
}

char* XOLEDLineClass::getText() {
  return _text;
}

void XOLEDLineClass::setText(const char* text, bool transient, bool blink) {
  char **targetText = &_text;
  unsigned long now = millis();

  if (transient) {
    targetText = &_transientText;
    _transientStartDate = now;
  }
  
  // Initialize blinking if required
  if (blink) {
    // If already blinking, don't ruin the rythm
    if(_lastBlinkDate == 0) {
      _lastBlinkDate = now;
    }
  } else {
    _lastBlinkDate = 0;
  }
  if (*targetText != NULL) {
    free(*targetText);
    *targetText = NULL;
  }
  int len = min(strlen(text), MAX_LINE_LENGTH);
  *targetText = (char*)malloc(len + 1) ;
  strncpy(*targetText, text, len);
  (*targetText)[len] = 0;
}

void XOLEDLineClass::refresh(SSD1306* display) {
  unsigned long now = millis();

  if (_lastBlinkDate != 0) {
    if (now > (_lastBlinkDate + _blinkPeriod)) {
      _blinkHide = !_blinkHide;
      _lastBlinkDate = now;
    }
  } else {
    _blinkHide = false;
  }
  if (_blinkHide) {
    return;
  }
  display->setFont(_font);
  display->setTextAlignment(_alignment);
  // If there is a transient text, check if expired
  if (_transientText != NULL) {
    // If transient text has expired, unset it
    if (now > _transientStartDate + _transientDuration) {
      free(_transientText);
      _transientText = NULL;
      _transientStartDate = 0;
    }
  }
  // If there is a (non expired) transient text, display it
  if (_transientText != NULL) {
    display->drawString(_posX, _posY, String(_transientText));
  } else {
    if (_text != NULL) {
      display->drawString(_posX, _posY, String(_text));
    }
  }
}