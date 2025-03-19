#include <U8g2lib.h>
#include <Wire.h>
#include <SPI.h>
#include "oled.h"
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);

void display_ini(){
  u8g2.begin();
}

void show_intro(void) {
  uint8_t i = 0;
  for (i=0; i<=31; i+=2){
    u8g2.clearBuffer();
    u8g2.setFontMode(1);
    u8g2.setBitmapMode(1);
    u8g2.drawFrame(62-2*i, 31-i, 4+4*i, 2+2*i);//origen
    u8g2.sendBuffer();
    delay(5);
  }
  u8g2.clearBuffer();
  u8g2.setFontMode(1);
  u8g2.setBitmapMode(1);
    u8g2.drawFrame(0, 0, 128, 64);//marco
    u8g2.setFont(u8g2_font_5x8_tr);
    u8g2.drawStr(55, 17, "MIDI");
    u8g2.setFont(u8g2_font_6x13_tr);
    u8g2.drawStr(38, 30, "SEQUENCER");  
    //keyboard:  
    u8g2.drawBox(34, 36, 61, 6);
    u8g2.drawBox(34, 43, 61, 14);
    u8g2.setDrawColor(2);
    u8g2.drawStr(34, 52, "||| || |||");
    u8g2.setFont(u8g2_font_4x6_tr);
    u8g2.drawStr(36, 57, "|  |  |  |  |");
    u8g2.setFont(u8g2_font_6x13_tr);
    u8g2.drawStr(35, 52, "||| || |||");
    u8g2.drawStr(36, 52, "||| || |||");
    u8g2.setFont(u8g2_font_4x6_tr);
    u8g2.drawStr(42, 57, "|  |  |");
    u8g2.drawStr(78, 57, "|  |");
    u8g2.setFont(u8g2_font_6x12_tr);
    u8g2.drawStr(53, 51, "|  |");
  u8g2.sendBuffer();
  delay(2000);
}

void show_play(){
  u8g2.clearBuffer();
  u8g2.setFontMode(1);
  u8g2.setBitmapMode(1);
  u8g2.setFont(u8g2_font_spleen32x64_mf);
  u8g2.drawStr(2, 54, "PLAY");
  u8g2.sendBuffer();
}

void show_stop(){
  u8g2.clearBuffer();
  u8g2.setFontMode(1);
  u8g2.setBitmapMode(1);
  u8g2.setFont(u8g2_font_spleen32x64_mf);
  u8g2.drawStr(2, 54, "STOP");
  u8g2.sendBuffer();
}

void show_number(uint8_t num, bool rec_on){
  char num_char[4];
  itoa(num, num_char, 10);
  u8g2.clearBuffer();
  u8g2.setFontMode(1);
  u8g2.setBitmapMode(1);
  u8g2.setFont(u8g2_font_logisoso50_tf);
  if (num < 10) u8g2.drawStr(46, 60, num_char);
  else if(num >=10) u8g2.drawStr(28, 60, num_char);
  //rec icon 
  if (rec_on){
    u8g2.setDrawColor(1);
    u8g2.drawRBox(101, 0, 27, 7, 2);//rectangulo
    u8g2.setDrawColor(2);
    u8g2.drawEllipse(123, 3, 2, 2);//circulo
    u8g2.setFont(u8g2_font_4x6_tr);
    u8g2.drawStr(106, 6, "REC"); 
  }
      
  u8g2.sendBuffer();
}

void show_bpm(uint8_t bpm){
  char bpm_char[4];
  itoa(bpm, bpm_char, 10);
  u8g2.clearBuffer();
  u8g2.setFontMode(1);
  u8g2.setBitmapMode(1);
  //metronomo icon
  u8g2.drawFrame(13, 43, 18, 8);
  u8g2.drawLine(30, 44, 33, 40);
  u8g2.drawLine(30, 50, 33, 45);
  u8g2.drawLine(33, 41, 33, 44);
  u8g2.drawLine(13, 42, 21, 18);
  u8g2.drawLine(24, 18, 30, 42);
  u8g2.drawLine(21, 18, 23, 18);
  u8g2.drawLine(33, 40, 26, 16);
  u8g2.drawLine(23, 16, 25, 16);
  u8g2.drawLine(22, 43, 12, 24);
  u8g2.drawPixel(25, 18);
  u8g2.drawPixel(22, 17);
  //mesa
  u8g2.drawLine(0, 55, 48, 55);
  u8g2.drawLine(59, 32, 34, 32);
  u8g2.drawLine(48, 55, 60, 33);
  u8g2.drawLine(13, 32, 0, 32);
  //bpm
  u8g2.setFont(u8g2_font_spleen16x32_mf);
  u8g2.drawStr(72, 35, bpm_char);
  u8g2.setFont(u8g2_font_spleen8x16_mf);
  u8g2.drawStr(84, 51, "bpm");
  //
  u8g2.sendBuffer();
}

void show_max_notes()
{
  u8g2.clearBuffer();
  u8g2.setFontMode(1);
  u8g2.setBitmapMode(1);
  u8g2.setFont(u8g2_font_profont29_tr);
  u8g2.drawStr(49, 28, "NO");
  u8g2.drawStr(33, 54, "MORE");
  u8g2.drawFrame(0, 0, 128, 64);
  u8g2.sendBuffer();
}

void show_sustain(int gate){//espera un valor de analogRead
  gate = map(gate, 0, 4096, 0, 6);
  u8g2.clearBuffer();
  u8g2.setFontMode(1);
  u8g2.setBitmapMode(1);
  switch (gate) {
    
    case 0:   
      u8g2.drawBox(20, 33, 12, 12);
      u8g2.drawFrame(34, 33, 12, 12);
      u8g2.drawFrame(48, 33, 12, 12);
      u8g2.drawFrame(62, 33, 12, 12);
      u8g2.drawFrame(76, 33, 12, 12);
      u8g2.drawFrame(90, 33, 12, 12);
      break;    

      case 1:   
      u8g2.drawBox(20, 33, 12, 12);
      u8g2.drawBox(34, 33, 12, 12);
      u8g2.drawFrame(48, 33, 12, 12);
      u8g2.drawFrame(62, 33, 12, 12);
      u8g2.drawFrame(76, 33, 12, 12);
      u8g2.drawFrame(90, 33, 12, 12);
      break;

      case 2:   
      u8g2.drawBox(20, 33, 12, 12);
      u8g2.drawBox(34, 33, 12, 12);
      u8g2.drawBox(48, 33, 12, 12);
      u8g2.drawFrame(62, 33, 12, 12);
      u8g2.drawFrame(76, 33, 12, 12);
      u8g2.drawFrame(90, 33, 12, 12);
      break;

      case 3:   
      u8g2.drawBox(20, 33, 12, 12);
      u8g2.drawBox(34, 33, 12, 12);
      u8g2.drawBox(48, 33, 12, 12);
      u8g2.drawBox(62, 33, 12, 12);
      u8g2.drawFrame(76, 33, 12, 12);
      u8g2.drawFrame(90, 33, 12, 12);
      break; 

      case 4:   
      u8g2.drawBox(20, 33, 12, 12);
      u8g2.drawBox(34, 33, 12, 12);
      u8g2.drawBox(48, 33, 12, 12);
      u8g2.drawBox(62, 33, 12, 12);
      u8g2.drawBox(76, 33, 12, 12);
      u8g2.drawFrame(90, 33, 12, 12);
      break;  

      case 5:   
      u8g2.drawBox(20, 33, 12, 12);
      u8g2.drawBox(34, 33, 12, 12);
      u8g2.drawBox(48, 33, 12, 12);
      u8g2.drawBox(62, 33, 12, 12);
      u8g2.drawBox(76, 33, 12, 12);
      u8g2.drawBox(90, 33, 12, 12);
      break;    
  }
  
  u8g2.setFont(u8g2_font_spleen6x12_mf);
  u8g2.drawStr(41, 21, "sustain");
  //u8g2.drawLine(1, 8, 123, 8);
  //u8g2.drawLine(0, 24, 122, 24);
  u8g2.sendBuffer();
}

void show_figure(uint8_t fig){
  switch(fig){
    case WHOLE_NOTE:
    u8g2.clearBuffer();
    u8g2.setFontMode(1);
    u8g2.setBitmapMode(1);
    u8g2.drawFilledEllipse(65, 29, 30, 21);
    u8g2.setDrawColor(0);
    u8g2.drawFilledEllipse(65, 29, 23, 20);
    u8g2.setDrawColor(1);
    u8g2.sendBuffer();
    break;

    case HALF_NOTE:
    u8g2.clearBuffer();
    u8g2.setFontMode(1);
    u8g2.setBitmapMode(1);
    u8g2.drawFilledEllipse(58, 43, 10, 7);
    u8g2.drawBox(65, 9, 4, 32);
    u8g2.setDrawColor(0);
    u8g2.drawFilledEllipse(58, 43, 7, 4);
    u8g2.setDrawColor(1);
    
    u8g2.sendBuffer();       
    break;

    case QUARTER_NOTE:
    u8g2.clearBuffer();
    u8g2.setFontMode(1);
    u8g2.setBitmapMode(1);
    u8g2.drawFilledEllipse(58, 43, 10, 7);
    u8g2.drawBox(65, 9, 4, 32);
    u8g2.sendBuffer();
    break;

    case EIGHTH_NOTE:
    u8g2.clearBuffer();
    u8g2.setFontMode(1);
    u8g2.setBitmapMode(1);
    u8g2.drawFilledEllipse(44, 43, 10, 7);
    u8g2.drawFilledEllipse(72, 43, 10, 7);
    u8g2.drawBox(51, 9, 4, 32);
    u8g2.drawBox(79, 9, 4, 32);
    u8g2.drawBox(55, 9, 24, 4);
    u8g2.sendBuffer();
    break;
    
    case SIXTEENTH_NOTE:
    u8g2.clearBuffer();
    u8g2.setFontMode(1);
    u8g2.setBitmapMode(1);
    u8g2.drawFilledEllipse(19, 43, 10, 7);
    u8g2.drawFilledEllipse(47, 43, 10, 7);
    u8g2.drawBox(26, 9, 4, 32);
    u8g2.drawBox(54, 9, 4, 32);
    u8g2.drawBox(30, 18, 24, 4);
    u8g2.drawBox(30, 9, 24, 4);
    u8g2.drawFilledEllipse(75, 43, 10, 7);
    u8g2.drawFilledEllipse(103, 43, 10, 7);
    u8g2.drawBox(82, 9, 4, 32);
    u8g2.drawBox(110, 9, 4, 32);
    u8g2.drawBox(86, 18, 24, 4);
    u8g2.drawBox(86, 9, 24, 4);
    u8g2.drawBox(58, 18, 24, 4);
    u8g2.drawBox(58, 9, 24, 4);
    u8g2.sendBuffer();
    break;
  }
  
}