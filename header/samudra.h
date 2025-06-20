#pragma once
#ifndef SAMUDRA_H
#define SAMUDRA_H
#include <graphics.h>
#include <time.h>

typedef enum {
    NORMAL,
    SPECIAL,
    POISON,
    SpeedBoost
} makananType;

 
extern int selectedSnakeIndex;
extern const char* warnaKepalaUlar[3];
extern const char* warnaBadanUlar[3];





// Struktur untuk makanan
typedef struct {
    int x, y;
    makananType type;
    clock_t spawnTime; // Waktu saat makanan muncul
} MakananStruct;

void GenerateRandomPosition(int *x, int *y);

makananType GeneratemakananType();

void Makanan(MakananStruct makanan);

void Tampilkanscore();

bool CekMakanMakanan(MakananStruct *makanan);

void gambarApel(int x, int y, int ukuran);

void gambarScApel(int x, int y, int ukuran);

void gambarRacun(int x, int y, int ukuran);

void gambarSpeedBoost(int x, int y, int ukuran);

const char* GetWarnaKepala(int index);
const char* GetWarnaBadan(int index);

void PlayNormalsound();
void PlaySpecialsound();
void PlayPoisonsound();
void PlayDeathsound();

void gambarArenaPreview(int index, int x1, int y1, int x2, int y2);
void gambarArena(int index);
void tampilanArenaSelection();

#endif   