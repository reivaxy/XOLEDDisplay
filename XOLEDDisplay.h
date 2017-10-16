
#pragma once
#include <Arduino.h>
#include <SSD1306.h>

#define MAX_TITLE_LENGTH 10
#define MAX_LINE_LENGTH 25

class XOLEDDisplayClass {
public:
  XOLEDDisplayClass(SSD1306 display);
  void setTitle(char *title);
  void setLine1(char *line);
  void setLine2(char *line);
  void setLine3(char *line);
  void setLine4(char *line);
  void setLeftIcon1(char* icon, bool blink);
  void setLeftIcon2(char* icon, bool blink);
  void setRightIcon1(char* icon, bool blink);
  void setRightIcon2(char* icon, bool blink);
  void display(void); 
  
protected:
  SSD1306* _display;
  char _title[MAX_TITLE_LENGTH + 1];
  char _line1[MAX_LINE_LENGTH +1];  
  char _line2[MAX_LINE_LENGTH +1];  
  char _line3[MAX_LINE_LENGTH +1];  
  char _line4[MAX_LINE_LENGTH +1];
  char* _leftIcon1 = NULL;  
  char* _leftIcon2 = NULL;  
  char* _rightIcon1= NULL;  
  char* _rightIcon2 = NULL;
  unsigned long _lastBlinkElapsed = 0;  
};
