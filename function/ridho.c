#include <graphics.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "../header/ridho.h"
#include "../header/samudra.h"
#include "../header/salma.h"
#include "../header/dimas.h"
#include "../header/akmal.h"

bool paused = false;
bool gameOver = false;

int score = 0;
int lastScore = 0;
char nama[100] = "";
int lastTime = 0;
int warnaCustomIndex = 16;

double speedBoostEndTime = 0;
double slowDownEndTime = 0;


int fullscreen_width = 640;
int fullscreen_height = 480;

int selectedArenaIndex = 0;

LeaderboardEntry leaderboard[MAX_LEADERBOARD];
int jumlahDataLeaderboard = 0;

// Fungsi untuk mengonversi warna dari string ke nilai integer
WarnaCustom daftarWarna[] = {
    {"ORANGE", 255, 109, 12},
    {"LIGHTORANGE", 251, 192, 153},
    {"BLUESNAKE", 7, 105, 170},
    {"LIGHTBLUESNAKE", 102, 189, 247},
    {"PINK", 255, 192, 203},
    {"PURPLE", 128, 0, 128},
    {"NAVY", 0, 0, 128},
    {"TEAL", 0, 128, 128},
    {"LIME", 0, 255, 0},
    {"MAROON", 128, 0, 0},
    {"OLIVE", 128, 128, 0},
    {"SILVER", 192, 192, 192},
    {"DARKGRAY", 64, 64, 64},       
    {"DARKGREEN", 0, 100, 0},       
    {"LIGHTYELLOW", 255, 255, 153},
    {"BADRED", 169, 55, 61},
    {"DARKBROWN", 139, 69, 19}, 
    {"LIGHTBROWN", 210, 180, 140},
    {"GRASSGREEN", 123, 179, 105},
};

int AmbilWarna(const char* color) {
    // Warna standar bawaan
    if (strcmp(color, "BLACK") == 0) return BLACK;
    if (strcmp(color, "BLUE") == 0) return BLUE;
    if (strcmp(color, "GREEN") == 0) return GREEN;
    if (strcmp(color, "CYAN") == 0) return CYAN;
    if (strcmp(color, "RED") == 0) return RED;
    if (strcmp(color, "MAGENTA") == 0) return MAGENTA;
    if (strcmp(color, "BROWN") == 0) return BROWN;
    if (strcmp(color, "LIGHTGRAY") == 0) return LIGHTGRAY;
    if (strcmp(color, "DARKGRAY") == 0) return DARKGRAY;
    if (strcmp(color, "LIGHTBLUE") == 0) return LIGHTBLUE;
    if (strcmp(color, "LIGHTGREEN") == 0) return LIGHTGREEN;
    if (strcmp(color, "LIGHTCYAN") == 0) return LIGHTCYAN;
    if (strcmp(color, "LIGHTRED") == 0) return LIGHTRED;
    if (strcmp(color, "LIGHTMAGENTA") == 0) return LIGHTMAGENTA;
    if (strcmp(color, "YELLOW") == 0) return YELLOW;
    if (strcmp(color, "WHITE") == 0) return WHITE;

    // Warna custom RGB (khusus untuk winbgim)
    for (int i = 0; i < sizeof(daftarWarna)/sizeof(WarnaCustom); i++) {
        if (strcmp(color, daftarWarna[i].name) == 0) {
            return COLOR(daftarWarna[i].r, daftarWarna[i].g, daftarWarna[i].b);
        }
    }

    return WHITE;
}


// Fungsi membuat teks
// pembuat modul : Ridho
void tulisan(int x, int y, int widthP, int heightP, CSTR warna, CSTR teks, int ukuran, typePenempatanTulisan penempatan) 
{
    setcolor(AmbilWarna(warna));
    settextstyle(BOLD_FONT, HORIZ_DIR, ukuran);

    char teksCopy[100];
    strcpy(teksCopy, teks);

    int textX, textY, textWidth, textHeight;

    if (penempatan == Center) {
        textWidth = textwidth(teksCopy);
        textHeight = textheight(teksCopy);
        textX = x + (widthP - textWidth) / 2;
        textY = y + (heightP - textHeight) / 2;

    } else if (penempatan == Random) {
        textX = x;
        textY = y;
    }

    outtextxy(textX, textY, teksCopy);
}

// Fungsi menggambar kotak berisi warna
// pembuat modul : Ridho
void Kotak(int x1, int y1, int x2, int y2, CSTR warna) 
{
    int ambilwarna = AmbilWarna(warna);

    setfillstyle(SOLID_FILL, ambilwarna);
    bar(x1, y1, x2, y2);

    setcolor(ambilwarna);
    rectangle(x1, y1, x2, y2);
}


// Fungsi membuat tombol dengan teks (lebih praktis)
// pembuat modul : Ridho
void tombol(int x, int y, int panjang, int lebar, CSTR warna, CSTR teks, int ukuranTeks) 
{
    Kotak(x, y, x + panjang, y + lebar, warna);
    setbkcolor(AmbilWarna(warna));
    tulisan(x, y, panjang, lebar, "WHITE", teks, ukuranTeks, Center);
}


// Prosedur untuk membuat sistem input nama
// pembuat modul : Ridho
void inputNama(char *nama, int kotakX, int kotakY, int kotakW, int kotakH,
    int tombolX, int tombolY, int tombolW, int tombolH) {

    int pos = 0;
    char ch;
    int x = kotakX + 10; 
    int y = kotakY + 10;

    // Fokus pada teks input
    setcolor(BLACK); // teks warna hitam (supaya kontras di input box putih)
    setbkcolor(WHITE); // background transparan pas input
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);

    while (1) {
        if (kbhit()) {
            ch = getch();

            if (ch == 13) { // Enter ditekan
                tampilanAwal(); 
                break;
            }
            else if (ch == 8 && pos > 0) { // Backspace
                pos--;
                nama[pos] = '\0';

                // Hapus dan redraw semua teks di kotak input
                setfillstyle(SOLID_FILL, WHITE);
                bar(kotakX + 2, kotakY + 2, kotakX + kotakW - 2, kotakY + kotakH - 2);
                outtextxy(x, y, nama);
            }
            else if (pos < 49 && ch >= 32 && ch <= 126) { // Karakter normal
                // Hitung lebar nama saat ini
                int currentWidth = textwidth(nama);

                // Cek apakah masih muat dalam kotak
                if (currentWidth + textwidth((char*)"W") < kotakW - 20) { // sedikit margin kanan
                    nama[pos] = ch;
                    nama[pos + 1] = '\0';

                    // Hapus dan redraw
                    setfillstyle(SOLID_FILL, WHITE);
                    bar(kotakX + 2, kotakY + 2, kotakX + kotakW - 2, kotakY + kotakH - 2);
                    outtextxy(x, y, nama);
                    pos++;
                }
            }
        }

        // Cek klik mouse
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int mx, my;
            getmouseclick(WM_LBUTTONDOWN, mx, my);
            if (mx >= tombolX && mx <= tombolX + tombolW &&
                my >= tombolY && my <= tombolY + tombolH) {
                // Kalau tombol diklik
                tampilanAwal(); // kembali ke menu awal
                break;
            }
        }
    }
}

// Prosedur untuk melakukan reset variabel variabel game (reset game saat mulai ulang)
// pembuat modul : Ridho
void ResetGame() {
    paused = false;
    arah = RIGHT;
    lastScore = score;
    lastTime = elapsed_time;

    // Simpan ke leaderboard hanya jika ada score
    if (lastScore > 0 || lastTime > 0) {
        SaveToLeaderboard(nama, lastScore, lastTime);
    }
    
    score = 0;

    deleteAll(&snake);
    
    // Reset stopwatch
    stopwatch_running = false;
    total_paused_duration = 0;
    elapsed_time = 0;

    InitUlar();
    gameOver = false;
    
}

// Prosedur untuk melakukan save ke txt leaderboard
// pembuat modul : Ridho
void SaveToLeaderboard(char *name, int score, int time) {
    FILE *file = fopen("leaderboard.txt", "r");
    int found = 0;
    jumlahDataLeaderboard = 0;

    if (file != NULL) {
        while (fscanf(file, "%s %d %d", leaderboard[jumlahDataLeaderboard].nama,
                      &leaderboard[jumlahDataLeaderboard].skor,
                      &leaderboard[jumlahDataLeaderboard].waktu) == 3) {
            
            // Cek apakah nama sama
            if (strcmp(leaderboard[jumlahDataLeaderboard].nama, name) == 0) {
                found = 1;
                // Update hanya jika skor baru lebih tinggi
                if (score > leaderboard[jumlahDataLeaderboard].skor) {
                    leaderboard[jumlahDataLeaderboard].skor = score;
                    leaderboard[jumlahDataLeaderboard].waktu = time;
                }
            }

            jumlahDataLeaderboard++;
        }
        fclose(file);
    }

    // Kalau nama belum ditemukan, tambahkan data baru
    if (!found && jumlahDataLeaderboard < MAX_LEADERBOARD) {
        strcpy(leaderboard[jumlahDataLeaderboard].nama, name);
        leaderboard[jumlahDataLeaderboard].skor = score;
        leaderboard[jumlahDataLeaderboard].waktu = time;
        jumlahDataLeaderboard++;
    }

    // Urutkan sebelum disimpan (opsional tapi direkomendasikan)
    UrutkanLeaderboard();

    // Tulis ulang seluruh leaderboard ke file
    file = fopen("leaderboard.txt", "w");
    if (file != NULL) {
        for (int i = 0; i < jumlahDataLeaderboard; i++) {
            fprintf(file, "%s %d %d\n", leaderboard[i].nama,
                    leaderboard[i].skor, leaderboard[i].waktu);
        }
        fclose(file);
    } else {
        printf("Gagal membuka file leaderboard.txt untuk ditulis!\n");
    }
}


// Fungsi untuk mengambil data leaderboard dari file
void AmbilDataLeaderboard() {
    // Membuka file "leaderboard.txt" dalam mode baca
    FILE *file = fopen("leaderboard.txt", "r");
    if (file == NULL) {
        // Jika file gagal dibuka, tampilkan pesan kesalahan dan keluar dari fungsi
        printf("Gagal membuka file leaderboard.txt\n");
        return;
    }

    // Menginisialisasi jumlah data leaderboard yang dibaca
    jumlahDataLeaderboard = 0;

    // Membaca data dari file hingga akhir file atau mencapai batas maksimum
    while (fscanf(file, "%s %d %d", leaderboard[jumlahDataLeaderboard].nama,
                  &leaderboard[jumlahDataLeaderboard].skor,
                  &leaderboard[jumlahDataLeaderboard].waktu) == 3) {
        jumlahDataLeaderboard++;

        // Hentikan jika jumlah data sudah mencapai batas maksimum yang ditentukan
        if (jumlahDataLeaderboard >= MAX_LEADERBOARD) {
            break;
        }
    }

    // Menutup file setelah selesai membaca
    fclose(file);
    // Mengurutkan data leaderboard berdasarkan skor
    UrutkanLeaderboard();
}

// Fungsi untuk mengurutkan data leaderboard dari skor tertinggi ke terendah
void UrutkanLeaderboard() {
    // Menggunakan algoritma bubble sort untuk mengurutkan data
    for (int i = 0; i < jumlahDataLeaderboard - 1; i++) {
        for (int j = 0; j < jumlahDataLeaderboard - i - 1; j++) {
            // Jika skor pada elemen saat ini lebih kecil dari skor berikutnya, tukar posisinya
            if (leaderboard[j].skor < leaderboard[j + 1].skor) {
                LeaderboardEntry temp = leaderboard[j];
                leaderboard[j] = leaderboard[j + 1];
                leaderboard[j + 1] = temp;
            }
        }
    }
}


// Prosedur untuk mengaktifkan atau menonaktifkan pause
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
void HandlePause(int x, int y) {
    if (!paused && x >= 780 && x <= 880 && y >= 15 && y <= 45) {
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
void LoopGame() {
    // Variabel untuk pengaturan halaman aktif (double buffering)
    int activePage = 0;
    // Waktu terakhir frame di-update (untuk kontrol frame rate)
    double lastUpdate = clock();
    // Waktu terakhir ular bergerak (kontrol kecepatan ular)
    double lastMoveTime = clock();
    // Waktu mulai permainan (untuk stopwatch dan penurunan kecepatan bertahap)
    double startTime = clock();
    // Delay antar frame agar berjalan di 60 FPS (1000ms / 60)
    double frameDelay = 1000.0 / 60.0;
    // Kecepatan awal ular dalam milidetik per gerakan
    double snakeSpeed = 120.0;

    // Inisialisasi makanan
    MakananStruct makanan;
    GenerateRandomPosition(&makanan.x, &makanan.y); // Tentukan posisi acak makanan
    makanan.type = GeneratemakananType();           // Tentukan jenis makanan secara acak
    makanan.spawnTime = clock();                    // Catat waktu spawn makanan

    startStopwatch(); // Mulai stopwatch game

    // --- Buffer statis disiapkan untuk optimasi render ---
    int arenaWidth = getmaxx();     // Ambil lebar arena
    int arenaHeight = getmaxy();    // Ambil tinggi arena

    // Alokasi memori untuk menyimpan gambar statis (arena, UI)
    void* arenaBuffer = malloc(imagesize(0, 0, arenaWidth, arenaHeight));
    if (!arenaBuffer) {
        printf("Gagal alokasi buffer\n");
        return;
    }

    // Gambar komponen statis seperti UI, arena, leaderboard
    setactivepage(0);
    cleardevice();
    gambarArena(selectedArenaIndex);
    tombol(780, 15, 100, 30, "DARKGRAY", "PAUSE", 2);

    setcolor(BLACK);
    rectangle(780, 15, 880, 45);

    tampilanNamaArena();
    tampilanLeaderboard();

    getimage(0, 0, arenaWidth, arenaHeight, arenaBuffer);

    // === Loop utama game ===
    while (!gameOver) {
        double currentTime = clock();

        CekInputUser();

        if (!paused) {
            if (currentTime - lastUpdate < frameDelay) continue;
            lastUpdate = currentTime;

            if (currentTime - lastMoveTime >= snakeSpeed) {
                GerakUlar();
                lastMoveTime = currentTime;
            }

            // Spawn makanan, Jika makanan beracun sudah muncul > 5 detik, ganti makanan baru
            if (makanan.type == POISON && (currentTime - makanan.spawnTime) / CLOCKS_PER_SEC > 5) {
                GenerateRandomPosition(&makanan.x, &makanan.y);
                makanan.type = GeneratemakananType();
                makanan.spawnTime = clock();
            }

            // === Double Buffering ===
            activePage = 1 - activePage; // Tukar halaman (page flip)
            setactivepage(activePage);   // Aktifkan page baru
            cleardevice();               // Bersihkan page aktif

            // Tempel ulang gambar statis (arena, UI) dari buffer
            putimage(0, 0, arenaBuffer, COPY_PUT);

            // Gambar elemen dinamis seperti skor, stopwatch, makanan, dan ular
            Tampilkanscore();
            Stopwatch();
            Makanan(makanan);
            GambarUlar()

            // Cek apakah ular memakan makanan
            if (CekMakanMakanan(&makanan)) {
                GenerateRandomPosition(&makanan.x, &makanan.y);
                makanan.type = GeneratemakananType();
                makanan.spawnTime = clock();
            }

            // Jika dalam efek speed boost, percepat ular
            if (currentTime < speedBoostEndTime) {
                snakeSpeed = 70.0;
            } 
            // Jika dalam efek slow down, perlambat ular
            else if (currentTime < slowDownEndTime) {
                snakeSpeed = 180.0;
            } 
            // Jika tidak ada efek, kembalikan ke kecepatan default
            else {
                snakeSpeed = 120.0;
            }

            // Percepat ular seiring waktu (tiap 20 detik dikurangi 10ms)
            double elapsedSeconds = (clock() - startTime) / CLOCKS_PER_SEC;
            double speedReduction = (int)(elapsedSeconds / 20) * 10.0;
            snakeSpeed -= speedReduction;

            // Tetapkan batas kecepatan minimum
            if (snakeSpeed < 40.0) snakeSpeed = 40.0;

            setvisualpage(activePage);
        } else {
            // Jika sedang pause, tetap tampilkan halaman aktif
            setvisualpage(activePage);
            PopUpPause();

            // Tunggu sampai tidak pause lagi atau gameOver
            while (paused && !gameOver) {
                CekInputUser();
                delay(10);
            }
        }

        // Cek tabrakan ular dengan dirinya atau tembok
        CekTabrakan();

        delay(10);
    }

    free(arenaBuffer);
}
