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

int selectedSnakeIndex = 0;

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
            gambarApel(makanan.x, makanan.y, 20); // Makanan biasa (merah)
            break;
        case SPECIAL:
            gambarScApel(makanan.x, makanan.y, 20); // Makanan spesial (emas)
            break;
        case POISON:
            gambarRacun(makanan.x, makanan.y, 5); // Makanan beracun (hijau)
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


void gambarApel(int x, int y, int ukuran) {
    // ukuran: panjang sisi kotak apel
    int warnaUtama = AmbilWarna("RED");
    int warnaHighlight = AmbilWarna("LIGHTRED");
    int warnaTangkai = AmbilWarna("BROWN");
    int warnaDaun = AmbilWarna("GREEN");

    // Gambar apel (kotak utama)
    setfillstyle(SOLID_FILL, warnaUtama);
    bar(x, y, x + ukuran, y + ukuran);

    // Gambar highlight di sisi kanan atas
    setfillstyle(SOLID_FILL, warnaHighlight);
    int highlightSize = ukuran / 3;
    bar(x + ukuran - highlightSize - 2, y + 2, x + ukuran - 2, y + highlightSize + 2);

    // Gambar tangkai di atas apel
    setcolor(warnaTangkai);
    setlinestyle(SOLID_LINE, 0, 3); // garis tebal
    line(x + ukuran/2, y, x + ukuran/2, y - ukuran/3);

    // Gambar daun di samping tangkai
    setcolor(warnaDaun);
    line(x + ukuran/2, y - ukuran/3, x + ukuran/2 + ukuran/4, y - ukuran/2);
}

void gambarRacun(int x, int y, int ukuran) {
    // ukuran = seberapa besar pixel (scale)
    int p = ukuran;

    // Definisi warna
    
    int hijau = AmbilWarna("GREEN");    // isi racun
    int putih = AmbilWarna("WHITE");    // highlight pantulan
    int coklat = AmbilWarna("BROWN");   // tutup botol
    int hitam = AmbilWarna("BLACK");    // latar belakang

    // Tutup botol
    setfillstyle(SOLID_FILL, coklat);
    bar(x + 3*p, y, x + 5*p, y + p); // bagian coklat tutup

    // Badan botol (ungu)
    setfillstyle(SOLID_FILL, hijau);
    bar(x + 2*p, y + p, x + 6*p, y + 6*p);

    // Cairan racun hijau di dalam
    setfillstyle(SOLID_FILL, hijau);
    bar(x + 2*p, y + 4*p, x + 6*p, y + 6*p);

    // Pantulan botol (highlight putih)
    setfillstyle(SOLID_FILL, putih);
    bar(x + 5*p, y + 2*p, x + 6*p, y + 3*p);

    // Outline botol (hitam)
    setcolor(hitam);
    rectangle(x + 2*p, y + p, x + 6*p, y + 6*p);
    rectangle(x + 3*p, y, x + 5*p, y + p); // outline tutup
}

void gambarScApel(int x, int y, int ukuran) {
    // ukuran: panjang sisi kotak apel
    int warnaUtama = AmbilWarna("YELLOW");
    int warnaTangkai = AmbilWarna("BROWN");
    int warnaDaun = AmbilWarna("GREEN");

    // Gambar apel (kotak utama)
    setfillstyle(SOLID_FILL, warnaUtama);
    bar(x, y, x + ukuran, y + ukuran);

    // Gambar tangkai di atas apel
    setcolor(warnaTangkai);
    setlinestyle(SOLID_LINE, 0, 3); // garis tebal
    line(x + ukuran/2, y, x + ukuran/2, y - ukuran/3);

    // Gambar daun di samping tangkai
    setcolor(warnaDaun);
    line(x + ukuran/2, y - ukuran/3, x + ukuran/2 + ukuran/4, y - ukuran/2);
}

const char* GetWarnaKepala(int index) {
    const char* warnaKepalaUlar[3] = {"GREEN", "BLUESNAKE", "ORANGE"};
    return warnaKepalaUlar[index];
}

const char* GetWarnaBadan(int index) {
    const char* warnaBadanUlar[3] = {"LIGHTGREEN", "LIGHTBLUESNAKE", "LIGHTORANGE"};
    return warnaBadanUlar[index];
}
