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
  void setTitleFont(const char* font);

  void setLine(int offset, char *text);
  void setLine(int offset, char *text, bool transient, bool blink);
  void setBlinkingLine(int offset, char *text);
  void setTransientLine(int offset, char *text);
  void blinkLine(int offset, bool flag);
  void setBlinkPeriod(int offset, unsigned int period);
  void setTransientDuration(int offset, unsigned int duration); 
  void setLineFont(const char* font);
  
  void setIcon1(char icon, bool blink);
  void setIcon1(char icon);
  void setIcon2(char icon, bool blink);
  void setIcon2(char icon);
  void setIcon3(char icon, bool blink);
  void setIcon3(char icon);
  void setIcon4(char icon, bool blink);
  void setIcon4(char icon);
   
  void blinkIcon1(bool blink);
  void blinkIcon2(bool blink);
  void blinkIcon3(bool blink);
  void blinkIcon4(bool blink);
  void setIconFont(const char* font);
  
  void heartBeatOn();
  void heartBeatOff();
  void setHeartBeatposition(int x, int y);
  
  void refresh(); 
  
  static const byte NB_LINES = 4; 
  static const byte NB_ICONS = 4; 

protected:
  XOLEDLineClass _title;
  XOLEDLineClass _lines[NB_LINES];
  XOLEDLineClass _icons[NB_LINES];
 
  int _heartBeatX = 0;
  int _heartBeatY = 0;
  bool _heartBeatOn = true;
  bool _heartBeatHide = false;
  unsigned int _lastHeartBeat = 0;
  int _titlePositions[2] = {64, 0};
  int _linePositions[NB_LINES][2] = {{0, 16}, {0, 26}, {0, 36}, {0, 46}};
  int _iconPositions[NB_ICONS][2] = {{0, 0}, {12, 0}, {128-24, 0}, {128-12, 0}};
  SSD1306* _display;

  void syncBlinking(void);
};
