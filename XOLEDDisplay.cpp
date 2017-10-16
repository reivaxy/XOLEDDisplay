

#include "XOLEDDisplay.h"

XOLEDDisplayClass::XOLEDDisplayClass(SSD1306 display) {
  _display = &display;
  _display->init();
  _display->flipScreenVertically();
  _display = &display;
  _title[0] = 0;
  _line1[0] = 0;
  _line2[0] = 0;
  _line3[0] = 0;
  _line4[0] = 0;

};

void XOLEDDisplayClass::setTitle(char* title) {
  strncpy(_title, title, MAX_TITLE_LENGTH);
  _title[MAX_TITLE_LENGTH] = 0;
}  

void XOLEDDisplayClass::setLine1(char* line) {
  strncpy(_line1, line, MAX_LINE_LENGTH);
  _line1[MAX_LINE_LENGTH] = 0;
}

void XOLEDDisplayClass::setLine2(char* line) {
  strncpy(_line2, line, MAX_LINE_LENGTH);
  _line2[MAX_LINE_LENGTH] = 0;
}

void XOLEDDisplayClass::setLine3(char* line) {
  strncpy(_line3, line, MAX_LINE_LENGTH);
  _line3[MAX_LINE_LENGTH] = 0;
}

void XOLEDDisplayClass::display(void) {

  _display->clear();

  
  _display->setFont(ArialMT_Plain_16);
  _display->setTextAlignment(TEXT_ALIGN_CENTER);
  _display->drawString(64, 0, _title);  

  _display->setFont(ArialMT_Plain_10);
  _display->setTextAlignment(TEXT_ALIGN_LEFT);
  _display->drawString(0, 15, _line1);

  _display->setTextAlignment(TEXT_ALIGN_LEFT);
  _display->drawString(0, 25, _line2);

  _display->setTextAlignment(TEXT_ALIGN_LEFT);
  _display->drawString(0, 35, _line3);

  _display->display();
}