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

// Prosedur untuk mengaktifkan atau menonaktifkan pause
// pembuat modul : Salma
// dimodifikasi oleh : -
void Tombolpause() {
    if (!paused) {
        paused = true;
        paused_time = time(NULL);
    } else {
        paused = false;
        total_paused_duration += time(NULL) - paused_time;
    }
}

// Prosedur untuk menangani klik mouse saat game dipause
// pembuat modul : Salma
// dimodifikasi oleh : -
void HandlePause(int x, int y) {
    if (!paused && x >= 520 && x <= 620 && y >= 15 && y <= 45) {
        Tombolpause();
    } else if (paused) {
        int popupX = SCREEN_WIDTH / 4;
        int popupY = SCREEN_HEIGHT / 4;
        int popupWidth = SCREEN_WIDTH / 2;
        int popupHeight = SCREEN_HEIGHT / 2;

        int resumeX = popupX + (popupWidth / 2) - 50;
        int resumeY = popupY + popupHeight / 2 - 20;
        int exitX = popupX + (popupWidth / 2) - 50;
        int exitY = popupY + popupHeight / 2 + 30;

        if (x >= resumeX && x <= resumeX + 100 && y >= resumeY && y <= resumeY + 40) {
            Tombolpause();
        } else if (x >= exitX && x <= exitX + 100 && y >= exitY && y <= exitY + 40) {
            ResetGame();
            tampilanAwal();
        }
    }
}

// Prosedur cek input user
// pembuat modul : Ridho
// dimodifikasi oleh : Dimas, Salma
void CekInputUser()
{
    // **Input pemain**
    if (kbhit()) {
        char key = getch();
    
        if (key == 0 || key == 224) {
            key = getch();
            if (key == 72 && arah != DOWN) arah = UP;    // Panah atas
            else if (key == 80 && arah != UP) arah = DOWN;    // Panah bawah
            else if (key == 75 && arah != RIGHT) arah = LEFT; // Panah kiri
            else if (key == 77 && arah != LEFT) arah = RIGHT; // Panah kanan
        } 
        else if (key == 'p' || key == 'P') {
            Tombolpause();
        }
    }
    
    //Mouse Klik Paused
    if (ismouseclick(WM_LBUTTONDOWN)) {
        int x, y;
        
        getmouseclick(WM_LBUTTONDOWN, x, y);
        HandlePause(x, y);
    }
}

// Prosedur Loop utama game
// pembuat modul : Dimas
// dimodifikasi oleh : Samudra, Ridho, Salma
void LoopGame() {
    int activePage = 0; // Buffer untuk double buffering
    double lastUpdate = clock(); // Waktu terakhir frame diperbarui
    double lastMoveTime = clock(); // Waktu terakhir ular bergerak
    double frameDelay = 1000.0 / 60.0; // 60 FPS
    double snakeSpeed = 150.0; // Kecepatan ular dalam ms (lebih besar = lebih lambat)

    MakananStruct makanan;
    GenerateRandomPosition(&makanan.x, &makanan.y);
    makanan.type = GeneratemakananType();
    makanan.spawnTime = clock(); // Simpan waktu makanan muncul

    startStopwatch();

    // **Loop utama game**
    while (!gameOver) {
        double currentTime = clock();

        CekInputUser();
        
         // Jika game tidak dipause, jalankan game seperti biasa
        if (!paused) {
            // *Batasi FPS (Frame Per Second)*
            if (currentTime - lastUpdate < frameDelay) continue;
            lastUpdate = currentTime;
            
            // *Menambah kecepatan ular berdasarkan kecepatan setiap 60 detik sekali snakespeednya berkurang 10
            if (elapsed_time % 60 == 0 && elapsed_time != lastTime) {
                if (snakeSpeed > 50) { // Batasi kecepatan minimum
                    snakeSpeed -= 10;
                }
                lastTime = elapsed_time;
            }

            // *Gerakkan ular berdasarkan kecepatan*
            if (currentTime - lastMoveTime >= snakeSpeed) {
                GerakUlar();
                lastMoveTime = currentTime;
            }

            // *Hapus makanan poison setelah 5 detik*
            if (makanan.type == POISON && (currentTime - makanan.spawnTime) / CLOCKS_PER_SEC > 5) {
                printf("Makanan poison menghilang!\n");
                GenerateRandomPosition(&makanan.x, &makanan.y);
                makanan.type = GeneratemakananType();
                makanan.spawnTime = clock(); // Reset waktu spawn
            }

            // *Double Buffering*
            activePage = 1 - activePage;
            setactivepage(activePage);
            cleardevice(); // Bersihkan layar sebelum menggambar ulang elemen game

            // *Gambar elemen game*
            Kotak(20, 60, SCREEN_WIDTH - 20, SCREEN_HEIGHT - 20, "BLACK");
            tombol(520, 15, 100, 30, "DARKGRAY", "PAUSE", 2);
            setbkcolor(BLACK);

            // *Gambar elemen game lainnya*
            Tampilkanscore();
            Stopwatch();
            Makanan(makanan);
            GambarUlar();
            tampilkanLeaderboard();

            // *Cek jika ular makan makanan*
            if (CekMakanMakanan(&makanan)) {
                GenerateRandomPosition(&makanan.x, &makanan.y);  
                makanan.type = GeneratemakananType();
                makanan.spawnTime = clock(); // Reset waktu spawn makanan
                
                printf("Score sekarang: %d\n", score);
            }

            // *Tampilkan buffer aktif*
            setvisualpage(activePage);
        } else {
            PopUpPause();
        }

        CekTabrakan();
        delay(100);
    }
}