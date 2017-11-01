/**
 *  Class to handle one line of text on OLED screen, with transient and blinking capabilities
 *  Xavier Grosjean 2017
 *  MIT License 
 */
 
#pragma once
#include <Arduino.h>
#include <SSD1306.h>

/**
 * Class to handle one line of text
 * One line can be transient: text is displayed for a given time and then
 * the line displays the old text
 * One line can blink
 *
 */
class XOLEDLineClass {
public:
  XOLEDLineClass();
  void setText(char* text);
  void setTransientText(char* text);
  void setBlinkingText(char* text);
  void setText(char* text, bool transient, bool blink);
  char* getText();
  
  void setIcon(char glyph);
  void setIcon(char glyph, bool blink);

  void setBlink(bool flag);
  void setFont(const char* font);
  void setAlignment(OLEDDISPLAY_TEXT_ALIGNMENT alignment);
  void setBlinkPeriod(unsigned int period);
  void setTransientDuration(unsigned int duration);
  void setPosition(int* pos);
  void setPosition(int x, int y);
  void syncBlink(void);

  bool isEmpty(void);
  void cancelTransient(void);
  void refresh(SSD1306* display);
  
  static const byte MAX_LINE_LENGTH = 25;  
  
protected:
  char* _text = NULL;
  char* _transientText = NULL;
  unsigned long _lastBlinkDate = 0;  
  unsigned long _blinkPeriod = 900;  
  bool _blinkHide = false;
  unsigned long _transientStartDate = 0;
  unsigned long _transientDuration = 5000; // 5 seconds
  int _posX = 0;
  int _posY = 0;
  const char* _font = ArialMT_Plain_10;
  OLEDDISPLAY_TEXT_ALIGNMENT _alignment = TEXT_ALIGN_LEFT;
      
};