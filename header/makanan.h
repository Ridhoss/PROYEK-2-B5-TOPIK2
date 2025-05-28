#pragma once
#ifndef MAKANAN_H
#define MAKANAN_H
#include <graphics.h>
#include "mechanism.h"

typedef enum {
    NORMAL,
    SPECIAL,
    POISON
} makananType;

 
extern int selectedSnakeIndex;
extern const char* warnaKepalaUlar[3];
extern const char* warnaBadanUlar[3];





// Struktur untuk makanan
typedef struct {
    int x, y;
    makananType type;
    double spawnTime; // Waktu saat makanan muncul
} MakananStruct;

void GenerateRandomPosition(int *x, int *y);

makananType GeneratemakananType();

void Makanan(MakananStruct makanan);

void Tampilkanscore();

void gambarApel(int x, int y, int ukuran);

void gambarScApel(int x, int y, int ukuran);

void gambarRacun(int x, int y, int ukuran);

const char* GetWarnaKepala(int index);
const char* GetWarnaBadan(int index);

#endif   