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
#include "../header/mechanism.h"

// Fungsi membuat posisi acak
// pembuat modul : Samudra
void GenerateRandomPosition(int *x, int *y) {
    *x = 20 + (rand() % ((SCREEN_WIDTH - 40) / 20)) * 20;
    *y = 60 + (rand() % ((SCREEN_HEIGHT - 80) / 20)) * 20;
}

// Fungsi untuk menentukan jenis makanan secara acak
// pembuat modul : Samudra
makananType GeneratemakananType() {
    int random = rand() % 10; // 0-9

    if (random < 4) return NORMAL;   
    if (random < 8) return SPECIAL;  
    return POISON;                   
}

// Fungsi membuat makanan
// pembuat modul : Samudra
void Makanan(MakananStruct makanan) {
    switch (makanan.type) {
        case NORMAL:
            Kotak(makanan.x, makanan.y, makanan.x + 20, makanan.y + 20, "RED");  // Makanan biasa (merah)
            break;
        case SPECIAL:
            Kotak(makanan.x, makanan.y, makanan.x + 20, makanan.y + 20, "BLUE"); // Makanan spesial (biru)
            break;
        case POISON:
            Kotak(makanan.x, makanan.y, makanan.x + 20, makanan.y + 20, "GREEN"); // Makanan beracun (hijau)
            break;
    }
}

// Prosedur untuk menampilkan score
// pembuat modul : Samudra
void Tampilkanscore() 
{
    // Konversi score ke string
    char scoreText[20];
    sprintf(scoreText, "Score: %d", score);

    // Set warna teks dan latar belakang agar terlihat jelas
    setcolor(WHITE);
    setbkcolor(CYAN);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);

    // Tampilkan teks score di layar
    outtextxy(30, 20, scoreText);
}


