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
    int random = rand() % 100;

    if (random < 50) return NORMAL;
    else if (random < 70) return SPECIAL;
    else if (random < 80) return POISON;
    else return SpeedBoost;             
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
            gambarRacun(makanan.x, makanan.y, 20); // Makanan beracun (hijau)
            break;
        case SpeedBoost:
            gambarSpeedBoost(makanan.x, makanan.y, 20); // Makanan speed boost (kuning)
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
   int warnaUtama = AmbilWarna("BADRED");            // Masih merah agar familiar
    int warnaHighlight = AmbilWarna("GREEN");      // Highlight kusam
    int warnaTangkai = AmbilWarna("BROWN");        // Tangkai kering
    int warnaDaun = AmbilWarna("DARKGREEN");       // Daun layu
    int warnaBintik = AmbilWarna("GREEN");         // Bintik busuk

    // Gambar apel merah
    setfillstyle(SOLID_FILL, warnaUtama);
    bar(x, y, x + ukuran, y + ukuran);

    // Gambar highlight kusam di kanan atas
    int highlightSize = ukuran / 3;
    setfillstyle(SOLID_FILL, warnaHighlight);
    bar(x + ukuran - highlightSize - 2, y + 2, x + ukuran - 2, y + highlightSize + 2);

    // Gambar tangkai
    setcolor(warnaTangkai);
    setlinestyle(SOLID_LINE, 0, 3);
    line(x + ukuran/2, y, x + ukuran/2, y - ukuran/3);

    // Gambar daun layu
    setcolor(warnaDaun);
    line(x + ukuran/2, y - ukuran/3, x + ukuran/2 + ukuran/4, y - ukuran/2);

    // Gambar bintik-bintik busuk (acak dan kecil)
    setfillstyle(SOLID_FILL, warnaBintik);
    fillellipse(x + ukuran/4, y + ukuran/3, ukuran/10, ukuran/10);
    fillellipse(x + 3*ukuran/4, y + 2*ukuran/3, ukuran/12, ukuran/12);
    fillellipse(x + ukuran/2, y + ukuran/2, ukuran/14, ukuran/14);
}


void gambarScApel(int x, int y, int ukuran) {
    // ukuran: panjang sisi kotak apel
    int warnaUtama = AmbilWarna("YELLOW");
    int warnaHighlight = AmbilWarna("LIGHTYELLOW");
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

const char* GetWarnaKepala(int index) {
    const char* warnaKepalaUlar[3] = {"GREEN", "BLUESNAKE", "ORANGE"};
    return warnaKepalaUlar[index];
}

const char* GetWarnaBadan(int index) {
    const char* warnaBadanUlar[3] = {"LIGHTGREEN", "LIGHTBLUESNAKE", "LIGHTORANGE"};
    return warnaBadanUlar[index];
}

void gambarSpeedBoost(int x, int y, int ukuran) {
    // ukuran: panjang sisi kotak apel
    int warnaUtama = AmbilWarna("BLUE");
    int warnaHighlight = AmbilWarna("LIGHTBLUESNAKE");
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