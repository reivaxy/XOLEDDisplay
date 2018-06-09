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
  void setText(const char* text);
  void setText(const char* text, bool transient, bool blink);
  void setTransientText(const char* text);
  void setBlinkingText(const char* text);
  char* getText();
  
  void setIcon(char glyph);
  void setIcon(char glyph, bool blink);

  void setBlink(bool flag);
  void setFont(const unsigned char* font);
  void setAlignment(OLEDDISPLAY_TEXT_ALIGNMENT alignment);
  void setBlinkPeriod(unsigned int period);
  void setTransientDuration(unsigned int duration);
  void setPosition(int* pos);
  void setPosition(int x, int y);
  void syncBlink(void);

  bool isEmpty(void);
  void cancelTransient(void);
  void refresh(SSD1306* display);
  
  static const unsigned int MAX_LINE_LENGTH = 25;
  
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
  const uint8_t* _font = ArialMT_Plain_10;
  OLEDDISPLAY_TEXT_ALIGNMENT _alignment = TEXT_ALIGN_LEFT;
      
};