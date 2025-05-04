#ifndef STOPWATCH_H
#define STOPWATCH_H
#include <graphics.h>
#include "mechanism.h"

extern time_t start_time;
extern time_t paused_time;
extern int elapsed_time;
extern int total_paused_duration;
extern bool stopwatch_running;

void Stopwatch();

void startStopwatch();


#endif   
