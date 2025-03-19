#ifndef CONFIG_H
#define CONFIG_H
//LIBRARIES
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
//PINS:
#define PLAY_SWT 39
#define REC_SWT 36
#define GATE_PIN 34
#define VELOCITY_PIN 35
#define DT 33
#define CLK 32
#define ENCODER_SWT 25
//PARAMETERS
#define BPM_MIN 40
#define BPM_MAX 200

//SEQUENCER:
#define MAX_NOTES (2 * 64)
#define NOTE_DURATION(BPM, FIGURE) (240000000 /(BPM * FIGURE)) 
#define WHOLE_NOTE 1
#define HALF_NOTE 2
#define QUARTER_NOTE 4
#define EIGHTH_NOTE 8
#define SIXTEENTH_NOTE 16

#define GATE_MIN 0.05 //max=0.15

#endif // CONFIG_H