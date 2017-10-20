/**
 *  Class to handle displaying lines on an OLED screen, with transient and blinking capabilities
 *  Xavier Grosjean 2017
 *  Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International Public License
 */
 
#pragma once
#include <Arduino.h>
#include <SSD1306.h>
#include "XOLEDLine.h"
#include "XOLEDIconFont.h"

class XOLEDDisplayClass {
public:
  XOLEDDisplayClass(SSD1306* display);
  void setTitle(char *title);

  void setLine(int offset, char *text);
  void setLine(int offset, char *text, bool transient, bool blink);
  void setBlinkingLine(int offset, char *text);
  void setTransientLine(int offset, char *text);
  void blinkLine(int offset, bool flag);
  void setBlinkPeriod(int offset, unsigned int period);
  void setTransientDuration(int offset, unsigned int duration); 
  
  void setLeftIcon1(char icon, bool blink);
  void setLeftIcon1(char icon);
  void setLeftIcon2(char icon, bool blink);
  void setLeftIcon2(char icon);
  void setRightIcon1(char icon, bool blink);
  void setRightIcon1(char icon);
  void setRightIcon2(char icon, bool blink);
  void setRightIcon2(char icon);
  
  void refresh(); 
  
  static const byte NB_LINES = 4; 
  static const byte NB_ICONS = 4; 
  static const byte MAX_TITLE_LENGTH = 10; 

protected:
  char _title[MAX_TITLE_LENGTH + 1];
  XOLEDLineClass _lines[NB_LINES];
  XOLEDLineClass _icons[NB_LINES];
    
  int _linePositions[NB_LINES][2] = {{0, 16}, {0, 26}, {0, 36}, {0, 46}};
  int _iconPositions[NB_ICONS][2] = {{0, 0}, {12, 0}, {128-24, 0}, {128-12, 0}};
  SSD1306* _display;

  void _syncBlinkingLines(void);
};
