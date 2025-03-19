#ifndef OLED_H
#define OLED_H

void display_ini();
void show_intro(void);
void show_play();
void show_stop();
void show_number(uint8_t num, bool rec_on);
void show_bpm(uint8_t bpm);
void show_max_notes();
void show_sustain(int gate);
void show_figure(uint8_t fig);

#endif // OLED_H