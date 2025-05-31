#include <graphics.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include "header/ridho.h"
#include "header/samudra.h"
#include "header/salma.h"
#include "header/dimas.h"
#include "header/akmal.h"

int main() {
    srand(time(NULL));
    // Ambil resolusi layar penuh
    fullscreen_width = GetSystemMetrics(SM_CXSCREEN);
    fullscreen_height = GetSystemMetrics(SM_CYSCREEN);

    // int width = GetSystemMetrics(SM_CXSCREEN);
    // int height = GetSystemMetrics(SM_CYSCREEN);
    
    // Buka window dengan ukuran layar penuh
    initwindow(fullscreen_width, fullscreen_height, "Snake Game", 0, 0);

    int posisiLayar = 0;
    tampilanInput();

    for (;;) {
        cleardevice();
        if(posisiLayar == 0) {
            tampilanAwal();
        } else if(posisiLayar == 1) {
            tampilanArena();
        }

        char key = getch();
        if(key == 101) {
            posisiLayar = 1;
        } else if(key == 27) {
            break;
        }
    }

    closegraph();
    return 0;

}
