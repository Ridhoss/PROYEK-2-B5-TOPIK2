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

extern int score;

Segment ular[MAX_LENGTH];
int panjangUlar = 3;
Direction arah = RIGHT;

// Prosedur Inisialisasi posisi awal ular
// pembuat modul : Dimas
void InitUlar() {
    int startX = SCREEN_WIDTH / 5;
    int startY = SCREEN_HEIGHT / 5;

    for (int i = 0; i < panjangUlar; i++) {
        ular[i].x = startX - (i * CELL_SIZE);
        ular[i].y = startY;
    }
}

// Prosedur Menggerakkan ular
// pembuat modul : Dimas
void GerakUlar() {
    // Pindahkan badan ular mengikuti kepala
    for (int i = panjangUlar - 1; i > 0; i--) {
        ular[i] = ular[i - 1];
    }

    // Gerakkan kepala ular berdasarkan arah
    if (arah == UP) ular[0].y -= CELL_SIZE;
    if (arah == DOWN) ular[0].y += CELL_SIZE;
    if (arah == LEFT) ular[0].x -= CELL_SIZE;
    if (arah == RIGHT) ular[0].x += CELL_SIZE;
}

// Prosedur Mengecek tabrakan dengan dinding atau tubuh sendiri
// pembuat modul : Dimas
void CekTabrakan() {
    // tabrakan dengan dinding
    if (ular[0].x < 20 || ular[0].x >= SCREEN_WIDTH - 20 ||
        ular[0].y < 60 || ular[0].y >= SCREEN_HEIGHT - 20) {
        gameOver = true;
        ResetGame();
        tampilanAwal();
    }
    for (int i = 1; i < panjangUlar; i++) {
        if (ular[0].x == ular[i].x && ular[0].y == ular[i].y) {
            gameOver = true;
            ResetGame();
            tampilanAwal();
        }
    }
}

// Prosedur Mengecek apakah ular makan makanan
// pembuat modul : Dimas
bool CekMakanMakanan(MakananStruct *makanan) {
    if (ular[0].x == makanan->x && ular[0].y == makanan->y) {
        panjangUlar++;
        if (makanan->type == SPECIAL) score += 5;
        else if (makanan->type == POISON) score -= 3;
        else score += 1;
        
        GenerateRandomPosition(&makanan->x, &makanan->y);
        makanan->type = GeneratemakananType();
        return true;
    }
    return false;
}

// Prosedur Menggambar ulang ular di layar
// pembuat modul : Dimas
void GambarUlar() {
    // Gambar kepala dengan warna merah
    Kotak(ular[0].x, ular[0].y, ular[0].x + CELL_SIZE, ular[0].y + CELL_SIZE, "GREEN");

    // Gambar badan dengan warna hijau
    for (int i = 1; i < panjangUlar; i++) {
        Kotak(ular[i].x, ular[i].y, ular[i].x + CELL_SIZE, ular[i].y + CELL_SIZE, "LIGHTGREEN");
    }
}
