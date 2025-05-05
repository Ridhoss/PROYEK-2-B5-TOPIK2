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

Segment *head = NULL;
Segment *tail = NULL;
Direction arah = RIGHT;

// Prosedur Inisialisasi posisi awal ular
// pembuat modul : Dimas
void InitUlar() {
    int startX = SCREEN_WIDTH / 5;
    int startY = SCREEN_HEIGHT / 5;

    // Buat kepala ular
    head = (Segment *)malloc(sizeof(Segment));
    head->x = startX;
    head->y = startY;
    head->next = NULL;
    tail = head;

    // Tambahkan segmen awal ke tubuh ular
    for (int i = 1; i < 3; i++) {
        Segment *newSegment = (Segment *)malloc(sizeof(Segment));
        newSegment->x = startX - (i * CELL_SIZE);
        newSegment->y = startY;
        newSegment->next = NULL;
        tail->next = newSegment;
        tail = newSegment;
    }
}

// Prosedur Menggerakkan ular
// pembuat modul : Dimas
void GerakUlar() {
    // Buat segmen baru untuk kepala
    Segment *newHead = (Segment *)malloc(sizeof(Segment));
    newHead->x = head->x;
    newHead->y = head->y;

    // Gerakkan kepala ular berdasarkan arah
    if (arah == UP) newHead->y -= CELL_SIZE;
    if (arah == DOWN) newHead->y += CELL_SIZE;
    if (arah == LEFT) newHead->x -= CELL_SIZE;
    if (arah == RIGHT) newHead->x += CELL_SIZE;

    newHead->next = head;
    head = newHead;

    // Hapus segmen terakhir (ekor)
    Segment *temp = head;
    while (temp->next != tail) {
        temp = temp->next;
    }
    free(tail);
    tail = temp;
    tail->next = NULL;
}

// Prosedur Mengecek tabrakan dengan dinding atau tubuh sendiri
// pembuat modul : Dimas
void CekTabrakan() {
    // tabrakan dengan dinding
    if (head->x < 20 || head->x >= SCREEN_WIDTH - 20 ||
        head->y < 60 || head->y >= SCREEN_HEIGHT - 20) {
        gameOver = true;
        ResetGame();
        tampilanAwal();
    }

    // tabrakan dengan tubuh sendiri
    Segment *current = head->next;
    while (current != NULL) {
        if (head->x == current->x && head->y == current->y) {
            gameOver = true;
            ResetGame();
            tampilanAwal();
        }
        current = current->next;
    }
}

// Prosedur Mengecek apakah ular makan makanan
// pembuat modul : Dimas
bool CekMakanMakanan(MakananStruct *makanan) {
    if (head->x == makanan->x && head->y == makanan->y) {
        // Tambahkan segmen baru ke ekor
        Segment *newSegment = (Segment *)malloc(sizeof(Segment));
        newSegment->x = tail->x;
        newSegment->y = tail->y;
        newSegment->next = NULL;
        tail->next = newSegment;
        tail = newSegment;

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
    const char* warnaKepala = GetWarnaKepala(selectedSnakeIndex);
    const char* warnaBadan  = GetWarnaBadan(selectedSnakeIndex);

    // Gambar kepala dengan warna merah
    Kotak(head->x, head->y, head->x + CELL_SIZE, head->y + CELL_SIZE, warnaKepala);

    // Gambar tubuh dengan warna hijau
    Segment *current = head->next;
    while (current != NULL) {
        Kotak(current->x, current->y, current->x + CELL_SIZE, current->y + CELL_SIZE, warnaBadan);
        current = current->next;
    }
}
