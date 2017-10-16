/**
 *  Class to handle displaying lines on an OLED screen, with transient and blinking capabilities
 *  Xavier Grosjean 2017
 *  Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International Public License
 */
 
#pragma once
#include <Arduino.h>
#include <SSD1306.h>
#include "XOLEDLine.h"

class XOLEDDisplayClass {
public:
  XOLEDDisplayClass(SSD1306* display);
  void setTitle(char *title);

  void setLine(int offset, char *text);
  void setLine(int offset, char *text, bool transient, bool blink);
  void setBlinkingLine(int offset, char *text);
  void unBlinkLine(int offset);

  void setLeftIcon1(char* icon, bool blink);
  void setLeftIcon2(char* icon, bool blink);
  void setRightIcon1(char* icon, bool blink);
  void setRightIcon2(char* icon, bool blink);
  void refresh(); 
  
  static const byte NB_LINES = 4; 
  static const byte MAX_TITLE_LENGTH = 10; 

protected:
  char _title[MAX_TITLE_LENGTH + 1];
  XOLEDLineClass _lines[NB_LINES];
  char* _leftIcon1 = NULL;  
  char* _leftIcon2 = NULL;  
  char* _rightIcon1= NULL;  
  char* _rightIcon2 = NULL;

  int _linePositions[NB_LINES][2] = {{0, 16}, {0, 26}, {0, 36}, {0, 46}};
  SSD1306* _display;
};
