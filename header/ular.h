#ifndef ULAR_H
#define ULAR_H
#include <graphics.h>
#include <stdbool.h>
#include "mechanism.h"

#define CELL_SIZE 20

// Struktur untuk setiap segmen ular menggunakan linked list
typedef struct Segment {
    int x, y;                    // Koordinat posisi segmen
    struct Segment *next;        // Pointer ke segmen berikutnya
} Segment;

// Struktur untuk kepala linked list ular
typedef struct {
    Segment *head;               // Pointer ke kepala ular (segmen pertama)
    Segment *tail;               // Pointer ke ekor ular (segmen terakhir)
} SnakeList;

// Enum untuk arah pergerakan ular
typedef enum { 
    UP, 
    DOWN, 
    LEFT, 
    RIGHT 
} Direction;

// Variabel global untuk ular
extern SnakeList snake;          // Struktur utama ular
extern Direction arah;           // Arah pergerakan ular saat ini

// Insert operations
Segment* createSegment(int x, int y);           // Membuat segmen baru
void insertHead(SnakeList *list, int x, int y); // Insert segmen di kepala (untuk pergerakan)
void insertTail(SnakeList *list, int x, int y); // Insert segmen di ekor (untuk pertumbuhan)

// Delete operations  
void deleteTail(SnakeList *list);               // Hapus segmen ekor (untuk pergerakan normal)
void deleteAll(SnakeList *list);                // Hapus semua segmen (reset game)

// Display operations
bool isEmpty(SnakeList *list);                         // Cek apakah ular kosong

// Inisialisasi Ular
void InitUlar();                                       // Inisialisasi ular dengan panjang awal

// Pergerakan dan logika game
void GerakUlar();                                      // Gerakkan ular satu langkah
void GrowSnake();                                      // Tambah panjang ular (setelah makan)

// Collision detection
void CekTabrakan();                                    // Cek tabrakan dengan dinding/diri sendiri
bool CekMakanMakanan(MakananStruct *makanan);         // Cek apakah ular makan makanan

// Rendering
void GambarUlar();                                     // Gambar ular di layar

#endif