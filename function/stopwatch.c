#include <graphics.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "../header/basicfunction.h"
#include "../header/makanan.h"
#include "../header/pages.h"
#include "../header/ular.h"
#include "../header/stopwatch.h"

time_t start_time;
time_t paused_time = 0;
int elapsed_time = 0;
int total_paused_duration = 0;
bool stopwatch_running = false;

// Prosedur mekanisme stopwatch
// pembuat modul : Akmal
void Stopwatch() {
    if (stopwatch_running && !paused) {
        elapsed_time = time(NULL) - start_time - total_paused_duration;
    }

    int minutes = elapsed_time / 60;
    int seconds = elapsed_time % 60;

    char time_str[10];
    sprintf(time_str, "%02d:%02d", minutes, seconds);

    setcolor(WHITE);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);

    int text_width = textwidth(time_str);
    int x_center = (SCREEN_WIDTH / 2) - (text_width / 2);

    outtextxy(x_center, 20, time_str);
}

//Fungsi untuk memulai stopwatch
// pembuat modul : Akmal
void startStopwatch() {
    start_time = time(NULL);
    elapsed_time = 0;
    total_paused_duration = 0;
    stopwatch_running = true; 
}