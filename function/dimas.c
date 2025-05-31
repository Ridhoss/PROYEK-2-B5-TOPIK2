#include <graphics.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include "../header/ridho.h"
#include "../header/samudra.h"
#include "../header/salma.h"
#include "../header/dimas.h"
#include "../header/akmal.h"

extern int score;

// Inisialisasi variabel global
SnakeList snake = {NULL, NULL};
Direction arah = RIGHT;

Segment* createSegment(int x, int y) {
    Segment *newSegment = (Segment*)malloc(sizeof(Segment));
    if (newSegment == NULL) {
        return NULL;
    }
    
    newSegment->x = x;
    newSegment->y = y;
    newSegment->next = NULL;
    
    return newSegment;
}

void insertHead(SnakeList *list, int x, int y) {
    if (list == NULL) return;
    
    Segment *newSegment = createSegment(x, y);
    if (newSegment == NULL) return;
    
    // Jika list kosong
    if (list->head == NULL) {
        list->head = newSegment;
        list->tail = newSegment;
    } else {
        // Insert di kepala
        newSegment->next = list->head;
        list->head = newSegment;
    }
    
}

void insertTail(SnakeList *list, int x, int y) {
    if (list == NULL) return;
    
    Segment *newSegment = createSegment(x, y);
    if (newSegment == NULL) return;
    
    // Jika list kosong
    if (list->head == NULL) {
        list->head = newSegment;
        list->tail = newSegment;
    } else {
        // Insert di ekor
        list->tail->next = newSegment;
        list->tail = newSegment;
    }
    
}

void deleteTail(SnakeList *list) {
    if (list == NULL || list->head == NULL) return;
    
    // Jika hanya ada satu segmen
    if (list->head == list->tail) {
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
        return;
    }
    
    // Cari segmen sebelum ekor
    Segment *current = list->head;
    while (current->next != list->tail) {
        current = current->next;
    }
    
    // Hapus ekor lama dan update pointer
    free(list->tail);
    list->tail = current;
    list->tail->next = NULL;
}

void deleteAll(SnakeList *list) {
    if (list == NULL) return;
    
    Segment *current = list->head;
    while (current != NULL) {
        Segment *next = current->next;
        free(current);
        current = next;
    }
    
    list->head = NULL;
    list->tail = NULL;
}

bool isEmpty(SnakeList *list) {
    return (list == NULL || list->head == NULL);
}

void InitUlar() {
    // Reset ular terlebih dahulu
    deleteAll(&snake);
    
    int startX = SCREEN_WIDTH / 5;
    int startY = SCREEN_HEIGHT / 5;
    
    // Pastikan posisi awal berada dalam batas arena
    if (startX < 40) startX = 40;
    if (startY < 100) startY = 100;
    
    // Buat kepala ular
    insertHead(&snake, startX, startY);
    
    // Tambahkan 2 segmen tubuh di belakang kepala
    insertTail(&snake, startX - CELL_SIZE, startY);
    insertTail(&snake, startX - (2 * CELL_SIZE), startY);
    
    // Set arah awal
    arah = RIGHT;
    
}

void GerakUlar() {
    if (isEmpty(&snake)) {
        return;
    }
    
    // Hitung posisi kepala baru
    int newX = snake.head->x;
    int newY = snake.head->y;
    
    switch (arah) {
        case UP:    newY -= CELL_SIZE; break;
        case DOWN:  newY += CELL_SIZE; break;
        case LEFT:  newX -= CELL_SIZE; break;
        case RIGHT: newX += CELL_SIZE; break;
    }
    
    // Tambah segmen baru di kepala
    insertHead(&snake, newX, newY);
    
    // Hapus segmen terakhir (ekor) untuk pergerakan normal
    // Kecuali jika ular baru saja makan (akan ditangani di fungsi lain)
    deleteTail(&snake);
}

void GrowSnake() {
    if (isEmpty(&snake)) return;
    
    // Ambil posisi ekor saat ini
    int tailX = snake.tail->x;
    int tailY = snake.tail->y;
    
    // Tambah segmen baru di ekor dengan posisi yang sama
    // (akan terpisah saat ular bergerak berikutnya)
    insertTail(&snake, tailX, tailY);
    
}

void CekTabrakan() {
    if (isEmpty(&snake)) return;
    
    int headX = snake.head->x;
    int headY = snake.head->y;
    
    // Cek tabrakan dengan dinding
    if (headX < 20 || headX >= SCREEN_WIDTH - 20 ||
        headY < 80 || headY >= SCREEN_HEIGHT - 20) {
        gameOver = true;
        PopUpGameOver(); // Panggil popup game over
        return;
    }
    
    // Cek tabrakan dengan tubuh sendiri (skip kepala)
    Segment *current = snake.head->next;
    while (current != NULL) {
        if (headX == current->x && headY == current->y) {
            gameOver = true;
            PopUpGameOver(); // Panggil popup game over
            return;
        }
        current = current->next;
    }
}

void GambarUlar() {
    if (isEmpty(&snake)) {
        return;
    }
    
    // Dapatkan warna berdasarkan skin yang dipilih
    const char* warnaKepala = GetWarnaKepala(selectedSnakeIndex);
    const char* warnaBadan = GetWarnaBadan(selectedSnakeIndex);
    
    // Gambar kepala ular
    Kotak(snake.head->x, snake.head->y, 
          snake.head->x + CELL_SIZE, snake.head->y + CELL_SIZE, 
          warnaKepala);
    
    // Gambar tubuh ular
    Segment *current = snake.head->next;
    while (current != NULL) {
        Kotak(current->x, current->y, 
              current->x + CELL_SIZE, current->y + CELL_SIZE, 
              warnaBadan);
        current = current->next;
    }
}

void PopUpGameOver() {
    int popupX = SCREEN_WIDTH / 4;
    int popupY = SCREEN_HEIGHT / 4;
    int popupWidth = SCREEN_WIDTH / 2;
    int popupHeight = SCREEN_HEIGHT / 2;

    // Gambar kotak popup dengan style yang sama seperti popup pause
    Kotak(popupX, popupY, popupX + popupWidth, popupY + popupHeight, "CYAN");
    setbkcolor(CYAN); 
    
    // Judul GAME OVER
    tulisan(popupX + popupWidth / 2, popupY + 50, 0, 0, "RED", "GAME OVER!", 5, Center);
    
    // Tampilkan skor final
    char scoreText[50];
    sprintf(scoreText, "SKOR AKHIR: %d", score);
    tulisan(popupX + popupWidth / 2, popupY + 100, 0, 0, "GREY", scoreText, 3, Center);
    
    // Tombol RETRY
    tombol(popupX + (popupWidth / 2) - 50, popupY + popupHeight / 2 - 20, 100, 40, "GREEN", "RETRY", 2);
    
    // Tombol MENU
    tombol(popupX + (popupWidth / 2) - 50, popupY + popupHeight / 2 + 30, 100, 40, "BLUE", "MENU", 2);
    
    setbkcolor(CYAN);
    
    // Handle input untuk tombol
    while (1) {
        int x, y;
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            
            // Tombol RETRY
            if (x >= popupX + (popupWidth / 2) - 50 && 
                x <= popupX + (popupWidth / 2) + 50 && 
                y >= popupY + popupHeight / 2 - 20 && 
                y <= popupY + popupHeight / 2 + 20) {
                
                // Reset game dan mulai ulang
                ResetGame();
                tampilanArena();
                return;
            }
            
            // Tombol MENU
            if (x >= popupX + (popupWidth / 2) - 50 && 
                x <= popupX + (popupWidth / 2) + 50 && 
                y >= popupY + popupHeight / 2 + 30 && 
                y <= popupY + popupHeight / 2 + 70) {
                
                // Kembali ke menu utama
                ResetGame();
                tampilanAwal();
                return;
            }
        }
        
        delay(50);
    }
}