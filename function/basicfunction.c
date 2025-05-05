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

bool paused = false;
bool gameOver = false;

int score = 0;
int lastScore = 0;
char nama[100] = "";
int lastTime = 0;
int warnaCustomIndex = 16;


int fullscreen_width = 640;
int fullscreen_height = 480;

// Fungsi untuk mengonversi warna dari string ke nilai integer
// pembuat modul : Ridho

typedef struct {
    const char* name;
    int r, g, b;
} WarnaCustom;

WarnaCustom daftarWarna[] = {
    {"ORANGE", 255, 109, 12},
    {"LIGHTORANGE", 251, 192, 153},
    {"BLUESNAKE", 7, 105, 170},
    {"LIGHTBLUESNAKE", 102, 189, 247},
    {"PINK", 255, 192, 203},
    {"PURPLE", 128, 0, 128},
    {"NAVY", 0, 0, 128},
    {"TEAL", 0, 128, 128},
    {"LIME", 0, 255, 0},
    {"MAROON", 128, 0, 0},
    {"OLIVE", 128, 128, 0},
    {"SILVER", 192, 192, 192},
};

int AmbilWarna(const char* color) {
    // Warna standar bawaan
    if (strcmp(color, "BLACK") == 0) return BLACK;
    if (strcmp(color, "BLUE") == 0) return BLUE;
    if (strcmp(color, "GREEN") == 0) return GREEN;
    if (strcmp(color, "CYAN") == 0) return CYAN;
    if (strcmp(color, "RED") == 0) return RED;
    if (strcmp(color, "MAGENTA") == 0) return MAGENTA;
    if (strcmp(color, "BROWN") == 0) return BROWN;
    if (strcmp(color, "LIGHTGRAY") == 0) return LIGHTGRAY;
    if (strcmp(color, "DARKGRAY") == 0) return DARKGRAY;
    if (strcmp(color, "LIGHTBLUE") == 0) return LIGHTBLUE;
    if (strcmp(color, "LIGHTGREEN") == 0) return LIGHTGREEN;
    if (strcmp(color, "LIGHTCYAN") == 0) return LIGHTCYAN;
    if (strcmp(color, "LIGHTRED") == 0) return LIGHTRED;
    if (strcmp(color, "LIGHTMAGENTA") == 0) return LIGHTMAGENTA;
    if (strcmp(color, "YELLOW") == 0) return YELLOW;
    if (strcmp(color, "WHITE") == 0) return WHITE;

    // Warna custom RGB (khusus untuk winbgim)
    for (int i = 0; i < sizeof(daftarWarna)/sizeof(WarnaCustom); i++) {
        if (strcmp(color, daftarWarna[i].name) == 0) {
            return COLOR(daftarWarna[i].r, daftarWarna[i].g, daftarWarna[i].b);
        }
    }

    return WHITE;
}


// Fungsi membuat teks
// pembuat modul : Ridho
void tulisan(int x, int y, int widthP, int heightP, CSTR warna, CSTR teks, int ukuran, typePenempatanTulisan penempatan) 
{
    setcolor(AmbilWarna(warna));
    settextstyle(BOLD_FONT, HORIZ_DIR, ukuran);

    char teksCopy[100];
    strcpy(teksCopy, teks);

    int textX, textY, textWidth, textHeight;

    if (penempatan == Center) {
        textWidth = textwidth(teksCopy);
        textHeight = textheight(teksCopy);
        textX = x + (widthP - textWidth) / 2;
        textY = y + (heightP - textHeight) / 2;

    } else if (penempatan == Random) {
        textX = x;
        textY = y;
    }

    outtextxy(textX, textY, teksCopy);
}

// Fungsi menggambar kotak berisi warna
// pembuat modul : Ridho
void Kotak(int x1, int y1, int x2, int y2, CSTR warna) 
{
    int ambilwarna = AmbilWarna(warna);

    setfillstyle(SOLID_FILL, ambilwarna);
    bar(x1, y1, x2, y2);

    setcolor(ambilwarna);
    rectangle(x1, y1, x2, y2);
}


// Fungsi membuat tombol dengan teks (lebih praktis)
// pembuat modul : Ridho
void tombol(int x, int y, int panjang, int lebar, CSTR warna, CSTR teks, int ukuranTeks) 
{
    Kotak(x, y, x + panjang, y + lebar, warna);
    setbkcolor(AmbilWarna(warna));
    tulisan(x, y, panjang, lebar, "WHITE", teks, ukuranTeks, Center);
}


// Prosedur untuk membuat sistem input nama
// pembuat modul : Ridho
void inputNama(char *nama, int kotakX, int kotakY, int kotakW, int kotakH,
    int tombolX, int tombolY, int tombolW, int tombolH) {

    int pos = 0;
    char ch;
    int x = kotakX + 10; 
    int y = kotakY + 10;

    // Fokus pada teks input
    setcolor(BLACK); // teks warna hitam (supaya kontras di input box putih)
    setbkcolor(WHITE); // background transparan pas input
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);

    while (1) {
        if (kbhit()) {
            ch = getch();

            if (ch == 13) { // Enter ditekan
                break;
            }
            else if (ch == 8 && pos > 0) { // Backspace
                pos--;
                nama[pos] = '\0';

                // Hapus dan redraw semua teks di kotak input
                setfillstyle(SOLID_FILL, WHITE);
                bar(kotakX + 2, kotakY + 2, kotakX + kotakW - 2, kotakY + kotakH - 2);
                outtextxy(x, y, nama);
            }
            else if (pos < 49 && ch >= 32 && ch <= 126) { // Karakter normal
                // Hitung lebar nama saat ini
                int currentWidth = textwidth(nama);

                // Cek apakah masih muat dalam kotak
                if (currentWidth + textwidth((char*)"W") < kotakW - 20) { // sedikit margin kanan
                    nama[pos] = ch;
                    nama[pos + 1] = '\0';

                    // Hapus dan redraw
                    setfillstyle(SOLID_FILL, WHITE);
                    bar(kotakX + 2, kotakY + 2, kotakX + kotakW - 2, kotakY + kotakH - 2);
                    outtextxy(x, y, nama);
                    pos++;
                }
            }
        }

        // Cek klik mouse
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int mx, my;
            getmouseclick(WM_LBUTTONDOWN, mx, my);
            if (mx >= tombolX && mx <= tombolX + tombolW &&
                my >= tombolY && my <= tombolY + tombolH) {
                // Kalau tombol diklik
                tampilanAwal(); // kembali ke menu awal
                break;
            }
        }
    }
}

// Prosedur untuk melakukan reset variabel variabel game (reset game saat mulai ulang)
// pembuat modul : Ridho
void ResetGame() {
    paused = false;
    arah = RIGHT;
    panjangUlar = 3;
    lastScore = score;
    lastTime = elapsed_time;
    SaveToLeaderboard(nama, lastScore, lastTime);
    score = 0;
}

// Prosedur untuk melakukan save ke txt leaderboard
// pembuat modul : Ridho
void SaveToLeaderboard(char *name, int score, int time)
{
    FILE *file = fopen("leaderboard.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s %d %d\n", name, lastScore, lastTime);
        fclose(file);
    } else {
        printf("Error opening file!\n");
    }
}