#ifndef BASICFUNCTION_H
#define BASICFUNCTION_H
#include <graphics.h>
#include "mechanism.h"

extern bool paused;
extern bool gameOver;

extern int score;
extern int lastScore;
extern char nama[100];
extern int lastTime;

extern int fullscreen_width;
extern int fullscreen_height;

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 700

#define MAX_ENTRIES 100
#define MAX_NAME_LENGTH 50

typedef const char* CSTR;
typedef enum { Center, Random } typePenempatanTulisan;

typedef struct {
    const char* name;
    int r, g, b;
} WarnaCustom;

typedef struct {
    char name[MAX_NAME_LENGTH];
    int score;
    int time;
} LeaderboardEntry;

extern LeaderboardEntry leaderboard[MAX_ENTRIES];
extern int leaderboardSize;

// header mengambil warna
int AmbilWarna(CSTR color);
// header membuat tulisan
void tulisan(int x, int y, int widthP, int heightP, CSTR warna, CSTR teks, int ukuran, typePenempatanTulisan penempatan);
// header kotak
void Kotak(int x1, int y1, int x2, int y2, CSTR warna);

// header membuat tombol
void tombol(int x, int y, int panjang, int lebar, CSTR warna, CSTR teks, int ukuranTeks);

void inputNama(char* nama, int x, int y, int width, int height, int tombolX, int tombolY, int tombolW, int tombolH);

void ResetGame();

void SaveToLeaderboard(char *name, int score, int time);

void AmbilLeaderboard();

#endif   