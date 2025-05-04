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


#endif   