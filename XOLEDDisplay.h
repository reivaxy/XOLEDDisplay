/**
 *  Class to handle displaying lines on an OLED screen, with transient and blinking capabilities
 *  Xavier Grosjean 2017
 *  MIT License 
 */
 
#pragma once
#include <Arduino.h>
#include <SSD1306.h>
#include "XOLEDLine.h"
#include "XOLEDIconFont.h"
#include "XOLEDFont.h"

class XOLEDDisplayClass {
public:
  XOLEDDisplayClass(SSD1306* display, bool flipScreen = true, uint8_t brightness = 100);
  XOLEDDisplayClass(int addr, int sda, int scl, bool flipScreen = true, uint8_t brightness = 100);
  
  SSD1306* getDisplay();
  void setTitle(const char *title);
  void setTitleFont(const char* font);

  void setLine(int offset, const char *text);
  void setLine(int offset, const char *text, bool transient, bool blink);
  void setBlinkingLine(int offset, const char *text);
  void setTransientLine(int offset, const char *text);
  void blinkLine(int offset, bool flag);
  void setBlinkPeriod(int offset, unsigned int period);
  void setTransientDuration(int offset, unsigned int duration); 
  void setLineFont(const uint8_t* font);
  void setLineFont(int offset, const uint8_t* font);
  void resetLineFont(int offset);
  void resetLineFont();
  void resetLinesAndIcons();
  void setLineAlignment(int offset, OLEDDISPLAY_TEXT_ALIGNMENT alignment);
  void setLinePosition(int offset, int x, int y);
  
  void setIcon(int offset, char icon, bool blink);
  void setIcon(int offset, char icon);  
  void blinkIcon(int offset, bool blink);
  char getIconChar(int offset);
  void setIconFont(const char* font);
  
  void heartBeatOn();
  void heartBeatOff();
  void setHeartBeatposition(int x, int y);
  
  void refresh(); 
  
  static const unsigned char NB_LINES = 5; 
  static const unsigned char NB_ICONS = 4; 

protected:
  void _init(SSD1306* display, bool flipScreen = true, uint8_t brightness = 100);
  XOLEDLineClass _title;
  XOLEDLineClass _lines[NB_LINES];
  XOLEDLineClass _icons[NB_LINES];
 
  int _heartBeatX = 0;
  int _heartBeatY = 0;
  bool _heartBeatOn = true;
  bool _heartBeatHide = false;
  unsigned int _lastHeartBeat = 0;
  int _titlePositions[2] = {64, 0};
  int _linePositions[NB_LINES][2] = {{0, 15}, {0, 25}, {0, 35}, {0, 45}, {0, 54}};
  int _iconPositions[NB_ICONS][2] = {{0, 0}, {12, 0}, {127-24, 0}, {127-10, 0}};
  SSD1306* _display;

  void syncBlinking(void);
};
