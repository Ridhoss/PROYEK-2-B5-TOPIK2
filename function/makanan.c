#include <graphics.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#include "../header/basicfunction.h"
#include "../header/makanan.h"
#include "../header/pages.h"
#include "../header/ular.h"
#include "../header/stopwatch.h"

int selectedSnakeIndex = 0;
extern int selectedArenaIndex;

// Fungsi membuat posisi acak
// pembuat modul : Samudra
void GenerateRandomPosition(int *x, int *y) {
    int min_x = 20;
    int max_x = SCREEN_WIDTH - 20;
    int min_y = 80;
    int max_y = SCREEN_HEIGHT - 20;

    int cols = (max_x - min_x) / 20;
    int rows = (max_y - min_y) / 20;

    *x = min_x + (rand() % cols) * 20;
    *y = min_y + (rand() % rows) * 20;
}


// Fungsi untuk menentukan jenis makanan secara acak
// pembuat modul : Samudra
makananType GeneratemakananType() {
    int random = rand() % 100;

    if (random < 50) return NORMAL;
    else if (random < 70) return SPECIAL;
    else if (random < 80) return POISON;
    else return SpeedBoost;             
}

// Fungsi membuat makanan
// pembuat modul : Samudra
void Makanan(MakananStruct makanan) {
    switch (makanan.type) {
        case NORMAL:
            gambarApel(makanan.x, makanan.y, 20); // Makanan biasa (merah)
            break;
        case SPECIAL:
            gambarScApel(makanan.x, makanan.y, 20); // Makanan spesial (emas)
            break;
        case POISON:
            gambarRacun(makanan.x, makanan.y, 20); // Makanan beracun (hijau)
            break;
        case SpeedBoost:
            gambarSpeedBoost(makanan.x, makanan.y, 20); // Makanan speed boost (kuning)
            break;
    }
}

// Prosedur untuk menampilkan score
// pembuat modul : Samudra
void Tampilkanscore() 
{
    // Konversi score ke string
    char scoreText[20];
    sprintf(scoreText, "Score: %d", score);

    // Set warna teks dan latar belakang agar terlihat jelas
    setcolor(BLACK);
    setbkcolor(LIGHTGRAY);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);

    // Tampilkan teks score di layar
    outtextxy(30, 20, scoreText);
}

bool CekMakanMakanan(MakananStruct *makanan) {
    if (isEmpty(&snake) || makanan == NULL) return false;
    
    int headX = snake.head->x;
    int headY = snake.head->y;
    
    if (headX == makanan->x && headY == makanan->y) {
        // Ular makan makanan - tambah panjang
        GrowSnake();
        
        // Update score berdasarkan jenis makanan
        if (makanan->type == SPECIAL) {
            score += 5;
            PlaySpecialsound();
        } else if (makanan->type == POISON) {
            score -= 3;
            if (score < 0) score = 0;
            PlayPoisonsound();
            slowDownEndTime = clock() + 3 * CLOCKS_PER_SEC;
        } else if (makanan->type == SpeedBoost) {
            score += 1;
            speedBoostEndTime = clock() + 3 * CLOCKS_PER_SEC;
            PlaySpecialsound();
        }else {
            score += 1;
            PlayNormalsound();
        }
        
        return true;
    }
    
    return false;
}

void gambarApel(int x, int y, int ukuran) {
    // ukuran: panjang sisi kotak apel
    int warnaUtama = AmbilWarna("RED");
    int warnaHighlight = AmbilWarna("LIGHTRED");
    int warnaTangkai = AmbilWarna("BROWN");
    int warnaDaun = AmbilWarna("GREEN");

    // Gambar apel (kotak utama)
    setfillstyle(SOLID_FILL, warnaUtama);
    bar(x, y, x + ukuran, y + ukuran);

    // Gambar highlight di sisi kanan atas
    setfillstyle(SOLID_FILL, warnaHighlight);
    int highlightSize = ukuran / 3;
    bar(x + ukuran - highlightSize - 2, y + 2, x + ukuran - 2, y + highlightSize + 2);

    // Gambar tangkai di atas apel
    setcolor(warnaTangkai);
    setlinestyle(SOLID_LINE, 0, 3); // garis tebal
    line(x + ukuran/2, y, x + ukuran/2, y - ukuran/3);

    // Gambar daun di samping tangkai
    setcolor(warnaDaun);
    line(x + ukuran/2, y - ukuran/3, x + ukuran/2 + ukuran/4, y - ukuran/2);
}

void gambarRacun(int x, int y, int ukuran) {
   int warnaUtama = AmbilWarna("BADRED");            // Masih merah agar familiar
    int warnaHighlight = AmbilWarna("GREEN");      // Highlight kusam
    int warnaTangkai = AmbilWarna("BROWN");        // Tangkai kering
    int warnaDaun = AmbilWarna("DARKGREEN");       // Daun layu
    int warnaBintik = AmbilWarna("GREEN");         // Bintik busuk

    // Gambar apel merah
    setfillstyle(SOLID_FILL, warnaUtama);
    bar(x, y, x + ukuran, y + ukuran);

    // Gambar highlight kusam di kanan atas
    int highlightSize = ukuran / 3;
    setfillstyle(SOLID_FILL, warnaHighlight);
    bar(x + ukuran - highlightSize - 2, y + 2, x + ukuran - 2, y + highlightSize + 2);

    // Gambar tangkai
    setcolor(warnaTangkai);
    setlinestyle(SOLID_LINE, 0, 3);
    line(x + ukuran/2, y, x + ukuran/2, y - ukuran/3);

    // Gambar daun layu
    setcolor(warnaDaun);
    line(x + ukuran/2, y - ukuran/3, x + ukuran/2 + ukuran/4, y - ukuran/2);

    // Gambar bintik-bintik busuk (acak dan kecil)
    setfillstyle(SOLID_FILL, warnaBintik);
    fillellipse(x + ukuran/4, y + ukuran/3, ukuran/10, ukuran/10);
    fillellipse(x + 3*ukuran/4, y + 2*ukuran/3, ukuran/12, ukuran/12);
    fillellipse(x + ukuran/2, y + ukuran/2, ukuran/14, ukuran/14);
}


void gambarScApel(int x, int y, int ukuran) {
    // ukuran: panjang sisi kotak apel
    int warnaUtama = AmbilWarna("YELLOW");
    int warnaHighlight = AmbilWarna("LIGHTYELLOW");
    int warnaTangkai = AmbilWarna("BROWN");
    int warnaDaun = AmbilWarna("GREEN");

    // Gambar apel (kotak utama)
    setfillstyle(SOLID_FILL, warnaUtama);
    bar(x, y, x + ukuran, y + ukuran);

    // Gambar highlight di sisi kanan atas
    setfillstyle(SOLID_FILL, warnaHighlight);
    int highlightSize = ukuran / 3;
    bar(x + ukuran - highlightSize - 2, y + 2, x + ukuran - 2, y + highlightSize + 2);

    // Gambar tangkai di atas apel
    setcolor(warnaTangkai);
    setlinestyle(SOLID_LINE, 0, 3); // garis tebal
    line(x + ukuran/2, y, x + ukuran/2, y - ukuran/3);

    // Gambar daun di samping tangkai
    setcolor(warnaDaun);
    line(x + ukuran/2, y - ukuran/3, x + ukuran/2 + ukuran/4, y - ukuran/2);
}

const char* GetWarnaKepala(int index) {
    const char* warnaKepalaUlar[3] = {"GREEN", "BLUESNAKE", "ORANGE"};
    return warnaKepalaUlar[index];
}

const char* GetWarnaBadan(int index) {
    const char* warnaBadanUlar[3] = {"LIGHTGREEN", "LIGHTBLUESNAKE", "LIGHTORANGE"};
    return warnaBadanUlar[index];
}

void gambarSpeedBoost(int x, int y, int ukuran) {
    // ukuran: panjang sisi kotak apel
    int warnaUtama = AmbilWarna("BLUE");
    int warnaHighlight = AmbilWarna("LIGHTBLUESNAKE");
    int warnaTangkai = AmbilWarna("BROWN");
    int warnaDaun = AmbilWarna("GREEN");

    // Gambar apel (kotak utama)
    setfillstyle(SOLID_FILL, warnaUtama);
    bar(x, y, x + ukuran, y + ukuran);

    // Gambar highlight di sisi kanan atas
    setfillstyle(SOLID_FILL, warnaHighlight);
    int highlightSize = ukuran / 3;
    bar(x + ukuran - highlightSize - 2, y + 2, x + ukuran - 2, y + highlightSize + 2);

    // Gambar tangkai di atas apel
    setcolor(warnaTangkai);
    setlinestyle(SOLID_LINE, 0, 3); // garis tebal
    line(x + ukuran/2, y, x + ukuran/2, y - ukuran/3);

    // Gambar daun di samping tangkai
    setcolor(warnaDaun);
    line(x + ukuran/2, y - ukuran/3, x + ukuran/2 + ukuran/4, y - ukuran/2);

}

void PlayNormalsound() {
    PlaySound(TEXT("assets/sound/normal.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void PlaySpecialsound() {
    PlaySound(TEXT("assets/sound/spesial.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void PlayPoisonsound() {
    PlaySound(TEXT("assets/sound/poison.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void gambarArena(int index) {
    int cellSize = CELL_SIZE;

    switch (index) {
        case 0: // Arena Normal (Hitam Polos)
            Kotak(20, 80, SCREEN_WIDTH - 20, SCREEN_HEIGHT - 20, "BLACK"); 
            break;
        case 1: // Arena Kayu (Papan Catur Coklat)
            Kotak(20, 80, SCREEN_WIDTH - 20, SCREEN_HEIGHT - 20, "BROWN"); // Base warna coklat 

            // Gambar pola seperti papan catur
            for (int y = 80; y < SCREEN_HEIGHT - 20; y += cellSize) { 
                for (int x = 20; x < SCREEN_WIDTH - 20; x += cellSize) { 
                    // Warna bergantian seperti papan catur
                    if (((x / cellSize) + (y / cellSize)) % 2 == 0) { 
                        Kotak(x, y, x + cellSize, y + cellSize, "BROWN"); // Warna coklat tua //
                    } else {
                        Kotak(x, y, x + cellSize, y + cellSize, "LIGHTBROWN"); // Warna coklat muda //
                    }
                }
            }
            break;
        case 2: // Arena Rumput (Hijau dengan Aksen Rumput)
            Kotak(20, 80, SCREEN_WIDTH - 20, SCREEN_HEIGHT - 20, "GRASSGREEN"); // Base warna hijau //

            // Tambahkan aksen rumput
            for (int i = 0; i < 50; i++) { // Jumlah aksen rumput //
                int grassX = 20 + (rand() % ((SCREEN_WIDTH - 40) / 5)) * 5; // Posisi X acak //
                int grassY = 80 + (rand() % ((SCREEN_HEIGHT - 80) / 5)) * 5; // Posisi Y acak //

                setcolor(AmbilWarna("DARKGREEN")); // Warna rumput lebih gelap
                line(grassX, grassY, grassX + 2, grassY - 5); 
                line(grassX, grassY, grassX - 2, grassY - 5); 
            }
            break;
        default: // Default ke Normal jika indeks tidak valid
            Kotak(20, 80, SCREEN_WIDTH - 20, SCREEN_HEIGHT - 20, "BLACK"); 
            break;
    }
    // Tambahkan border kuning untuk semua arena
    setcolor(AmbilWarna("YELLOW"));
    setlinestyle(SOLID_LINE, 0, 2); 
    rectangle(20, 80, SCREEN_WIDTH - 20, SCREEN_HEIGHT - 20);
}




void gambarArenaPreview(int index, int x1, int y1, int x2, int y2) {
    int previewWidth = x2 - x1;
    int previewHeight = y2 - y1;
    // Skala CELL_SIZE agar sesuai dengan ukuran pratinjau yang lebih kecil
    int scaledCellSize = CELL_SIZE / 4; 

    if (scaledCellSize < 1) scaledCellSize = 1; // Pastikan ukuran sel minimal 1

    switch (index) {
        case 0: // Arena Normal (Hitam Polos)
            Kotak(x1, y1, x2, y2, "BLACK");
            break;
        case 1: // Arena Kayu (Papan Catur Coklat)
            Kotak(x1, y1, x2, y2, "BROWN"); // Isi latar belakang dengan satu warna coklat
            
            // Gambar pola seperti papan catur yang diskalakan
            for (int y = y1; y < y2; y += scaledCellSize) {
                for (int x = x1; x < x2; x += scaledCellSize) {
                    // Warna bergantian seperti papan catur
                    if (((x / scaledCellSize) + (y / scaledCellSize)) % 2 == 0) {
                        Kotak(x, y, x + scaledCellSize, y + scaledCellSize, "BROWN"); // Warna coklat tua
                    } else {
                        Kotak(x, y, x + scaledCellSize, y + scaledCellSize, "LIGHTBROWN"); // Warna coklat muda
                    }
                }
            }
            break;
            case 2: // Arena Rumput (Hijau dengan Aksen Rumput)
            Kotak(x1, y1, x2, y2, "GRASSGREEN"); // Base warna hijau

            // Tambahkan aksen rumput yang diskalakan
            // PERUBAHAN: Hapus srand(time(NULL)) di sini, karena seharusnya hanya dipanggil sekali di awal program (misalnya di main.c)
            for (int i = 0; i < 20; i++) { // Kurangi jumlah aksen untuk pratinjau agar tidak terlalu ramai
                int grassX = x1 + (rand() % (previewWidth - 4)); // Posisi X acak dalam pratinjau
                int grassY = y1 + (rand() % (previewHeight - 4)); // Posisi Y acak dalam pratinjau

                setcolor(AmbilWarna("DARKGREEN")); // Warna rumput lebih gelap
                line(grassX, grassY, grassX + 1, grassY - 2); // Lebih kecil
                line(grassX, grassY, grassX - 1, grassY - 2); // Lebih kecil
            }
            break;
        default: // Default ke Normal jika indeks tidak valid
            Kotak(x1, y1, x2, y2, "BLACK");
            break;
    }
}


void tampilanArenaSelection() {
    setbkcolor(BLACK);
    cleardevice();

    Titik(); 

    readimagefile(
        "assets/judul.bmp",
        (fullscreen_width - 300) / 2,
        10,
        (fullscreen_width - 300) / 2 + 300,
        10 + 207
    );

    const char* arenaNames[3] = { 
        "NORMAL",
        "KAYU",
        "RUMPUT"
    };

    int currentArena = 0;
    int totalArenas = 3; // Ubah menjadi 3

    int panahWidth = 50, panahHeight = 20;
    int arenaPreviewWidth = 300, arenaPreviewHeight = 200; // Ukuran preview arena

    int centerX = fullscreen_width / 2;
    int spacing = 50;
    int previewY = fullscreen_height / 2 - arenaPreviewHeight / 2 - 50;

    int tombolLebar = 150, tombolTinggi = 50;
    int posisiX = (fullscreen_width - tombolLebar) / 2;
    int posisiY = previewY + arenaPreviewHeight + 80;


    int kiriX1 = centerX - arenaPreviewWidth / 2 - spacing - panahWidth;
    int kiriY1 = previewY + (arenaPreviewHeight - panahHeight) / 2;
    int kiriX2 = kiriX1 + panahWidth;
    int kiriY2 = kiriY1 + panahHeight;

    int kananX1 = centerX + arenaPreviewWidth / 2 + spacing;
    int kananY1 = kiriY1;
    int kananX2 = kananX1 + panahWidth;
    int kananY2 = kananY1 + panahHeight;

    readimagefile("assets/pkiri.bmp", kiriX1, kiriY1, kiriX2, kiriY2);
    readimagefile("assets/pkanan.bmp", kananX1, kananY1, kananX2, kananY2);
    tombol(posisiX, posisiY, tombolLebar, tombolTinggi, "GREEN", "PILIH", 3);

    // Hitung koordinat pratinjau arena
    int tempArenaX1 = centerX - arenaPreviewWidth / 2;
    int tempArenaY1 = previewY;
    int tempArenaX2 = centerX + arenaPreviewWidth / 2;
    int tempArenaY2 = previewY + arenaPreviewHeight;

    // Gambar border untuk pratinjau
    Kotak(tempArenaX1, tempArenaY1, tempArenaX2, tempArenaY2, "WHITE");
    setfillstyle(SOLID_FILL, BLACK);
    bar(tempArenaX1 + 5, tempArenaY1 + 5, tempArenaX2 - 5, tempArenaY2 - 5); // Bersihkan area di dalam border
    
    // Tampilkan nama arena
    setbkcolor(BLACK);
    tulisan(centerX, previewY + arenaPreviewHeight + 20, 0, 0, "WHITE", arenaNames[currentArena], 3, Center);

    gambarArenaPreview(currentArena, tempArenaX1 + 5, tempArenaY1 + 5, tempArenaX2 - 5, tempArenaY2 - 5);

    while (1) {
        int x, y;
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);

            if (x >= kiriX1 && x <= kiriX2 && y >= kiriY1 && y <= kiriY2) {
                currentArena = (currentArena - 1 + totalArenas) % totalArenas;
                // Bersihkan area pratinjau dan nama arena
                setfillstyle(SOLID_FILL, BLACK);
                bar(tempArenaX1 + 1, tempArenaY1 + 1, tempArenaX2 - 1, tempArenaY2 - 1); // Bersihkan area pratinjau
                bar(centerX - textwidth((char*)arenaNames[totalArenas-1])/2, previewY + arenaPreviewHeight + 10, centerX + textwidth((char*)arenaNames[totalArenas-1])/2, previewY + arenaPreviewHeight + 50); // Bersihkan nama arena

                // Gambar border lagi
                Kotak(tempArenaX1, tempArenaY1, tempArenaX2, tempArenaY2, "WHITE");
                setfillstyle(SOLID_FILL, BLACK);
                bar(tempArenaX1 + 5, tempArenaY1 + 5, tempArenaX2 - 5, tempArenaY2 - 5);

                // Tampilkan nama arena baru
                setbkcolor(BLACK);
                tulisan(centerX, previewY + arenaPreviewHeight + 20, 0, 0, "WHITE", arenaNames[currentArena], 3, Center);

                // PERUBAHAN: Gambar pratinjau arena baru
                gambarArenaPreview(currentArena, tempArenaX1 + 5, tempArenaY1 + 5, tempArenaX2 - 5, tempArenaY2 - 5);

            } else if (x >= kananX1 && x <= kananX2 && y >= kananY1 && y <= kananY2) {
                currentArena = (currentArena + 1) % totalArenas;
                // Bersihkan area pratinjau dan nama arena
                setfillstyle(SOLID_FILL, BLACK);
                bar(tempArenaX1 + 1, tempArenaY1 + 1, tempArenaX2 - 1, tempArenaY2 - 1); // Bersihkan area pratinjau
                bar(centerX - textwidth((char*)arenaNames[totalArenas-1])/2, previewY + arenaPreviewHeight + 10, centerX + textwidth((char*)arenaNames[totalArenas-1])/2, previewY + arenaPreviewHeight + 50); // Bersihkan nama arena

                // Gambar border lagi
                Kotak(tempArenaX1, tempArenaY1, tempArenaX2, tempArenaY2, "WHITE");
                setfillstyle(SOLID_FILL, BLACK);
                bar(tempArenaX1 + 5, tempArenaY1 + 5, tempArenaX2 - 5, tempArenaY2 - 5);

                // Tampilkan nama arena baru
                setbkcolor(BLACK);
                tulisan(centerX, previewY + arenaPreviewHeight + 20, 0, 0, "WHITE", arenaNames[currentArena], 3, Center);
                gambarArenaPreview(currentArena, tempArenaX1 + 5, tempArenaY1 + 5, tempArenaX2 - 5, tempArenaY2 - 5);
            } else if (x >= posisiX && x <= posisiX + tombolLebar && y >= posisiY && y <= posisiY + tombolTinggi) {
                selectedArenaIndex = currentArena; // Simpan pilihan arena
                tampilanAwal(); // Kembali ke tampilan awal setelah memilih
                break;
            }
        }
        delay(30);
    }
}

void PlayDeathsound() {
    PlaySound(TEXT("assets/sound/death.wav"), NULL, SND_FILENAME | SND_ASYNC);
}