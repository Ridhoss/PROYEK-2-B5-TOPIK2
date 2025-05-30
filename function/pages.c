#include <graphics.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include "../header/basicfunction.h"
#include "../header/makanan.h"
#include "../header/pages.h"
#include "../header/ular.h"
#include "../header/stopwatch.h"
#include "../header/mechanism.h"


// prosedur untuk tampilan awal
// pembuat modul : Salma
void tampilanAwal() {
    setbkcolor(BLACK);
    cleardevice();

    Titik(); 

    printf("nama : %s\n", nama);
    printf("score: %d\n", lastScore);
    printf("time: %d\n", lastTime);

    tampilanNama(); 

    readimagefile(
        "assets/judul.bmp",
        (fullscreen_width - 300) / 2,
        10,
        (fullscreen_width - 300) / 2 + 300,
        10 + 207
    );


    int musicIconWidth = 40, musicIconHeight = 40;
    int dropdownIconWidth = 75, dropdownIconHeight = 75;

    int marginLeft = 15;
    int spacing = 15;
    int bottomY = fullscreen_height - dropdownIconHeight - 30;


    readimagefile("assets/music_logo.bmp",
        15, 20,
        15 + musicIconWidth, 20 + musicIconHeight);

    // posisi untuk masing-masing ikon 
    int iconY[3] = {
    bottomY - 2 * (dropdownIconHeight + spacing), // snake
    bottomY - dropdownIconHeight - spacing,       // guide
    bottomY                                       // arena
    };
    

    readimagefile("assets/snake_logo.bmp", marginLeft, iconY[0], marginLeft + dropdownIconWidth, iconY[0] + dropdownIconHeight);
    readimagefile("assets/guide_logo.bmp", marginLeft, iconY[1], marginLeft + dropdownIconWidth, iconY[1] + dropdownIconHeight);
    readimagefile("assets/arena_logo.bmp", marginLeft, iconY[2], marginLeft + dropdownIconWidth, iconY[2] + dropdownIconHeight);

   
    const char* textImages[3] = {
        "assets/text1.bmp",
        "assets/text2.bmp",
        "assets/text3.bmp"
    };

    int tombolLebar = 200, tombolTinggi = 50;
    int posisiX = (fullscreen_width - tombolLebar) / 2;
    int posisiY = 300;

    tombol(posisiX, posisiY, tombolLebar, tombolTinggi, "GREEN", "START", 3);
    tombol(posisiX, posisiY + 80, tombolLebar, tombolTinggi, "BLUE", "LEADERBOARD", 3);
    tombol(posisiX, posisiY + 150, tombolLebar, tombolTinggi, "RED", "EXIT", 3);

    bool isHovering[3] = { false, false, false };

   
   while (1) {
        int x = mousex();
        int y = mousey();

        for (int i = 0; i < 3; i++) {
            int iconX1 = marginLeft;
            int iconY1 = iconY[i];
            int iconX2 = iconX1 + dropdownIconWidth;
            int iconY2 = iconY1 + dropdownIconHeight;

            int dropX1 = iconX2 + 10;
            int dropY1 = iconY1 + (dropdownIconHeight - 40) / 2;
            int dropX2 = dropX1 + 100;
            int dropY2 = dropY1 + 40;

            if (x >= iconX1 && x <= iconX2 && y >= iconY1 && y <= iconY2) {
                if (!isHovering[i]) {
                    setfillstyle(SOLID_FILL, BLACK);
                    bar(dropX1 - 2, dropY1 - 2, dropX2 + 2, dropY2 + 2);
                    readimagefile(textImages[i], dropX1, dropY1, dropX2, dropY2);
                    isHovering[i] = true;
                }
            } else {
                if (isHovering[i]) {
                    setfillstyle(SOLID_FILL, BLACK);
                    bar(dropX1 - 2, dropY1 - 2, dropX2 + 2, dropY2 + 2);
                    isHovering[i] = false;
                }
            }
        }

        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            if (x >= posisiX && x <= posisiX + tombolLebar && y >= posisiY && y <= posisiY + tombolTinggi) {
                tampilanArena();
                break;
            }
            if (x >= posisiX && x <= posisiX + tombolLebar && y >= posisiY + 80 && y <= posisiY + 80 + tombolTinggi) {
                tampilanLeaderboardMenu();
                break;
            }
            if (x >= posisiX && x <= posisiX + tombolLebar && y >= posisiY + 150 && y <= posisiY + 150 + tombolTinggi) {
                exit(0);
            }

            // Cek klik pada dropdown
            for (int i = 0; i < 3; i++) {
                int iconX1 = marginLeft;
                int iconY1 = iconY[i];
                int iconX2 = iconX1 + dropdownIconWidth;
                int iconY2 = iconY1 + dropdownIconHeight;

                // int iconX2 = marginLeft + dropdownIconWidth;
                int dropX1 = iconX2 + 10;
                int dropY1 = iconY[i] + (dropdownIconHeight - 40) / 2;
                int dropX2 = dropX1 + 100;
                int dropY2 = dropY1 + 40;

                if (x >= iconX1 && x <= iconX2 && y >= iconY1 && y <= iconY2) {
                    if (i == 0) {
                        tampilanPlay();
                        return;
                    }else if (i == 1) {
                        tampilanGuide();
                        return;
                    } 
                }

               
            }
                   delay(50);
        }
    }

}

// prosedur untuk tampilan nama kanan atas
// pembuat modul : Salma
void tampilanNama() {
    int kotakLebar = 150;
    int kotakTinggi = 40;

    int margin = 20; 
    int kotakX1 = fullscreen_width - kotakLebar - margin;
    int kotakY1 = margin;
    int kotakX2 = fullscreen_width - margin;
    int kotakY2 = kotakY1 + kotakTinggi;

    
    setfillstyle(SOLID_FILL, BLACK); 
    bar(kotakX1, kotakY1, kotakX2, kotakY2);

    setcolor(WHITE); 
    rectangle(kotakX1, kotakY1, kotakX2, kotakY2);

    settextstyle(10, HORIZ_DIR, 2); 
    setcolor(WHITE); 

    int textWidth = textwidth(nama);
    int textHeight = textheight(nama);

    outtextxy(
        kotakX1 + (kotakLebar - textWidth) / 2, 
        kotakY1 + (kotakTinggi - textHeight) / 2, 
        nama
    );
}


// prosedur untuk tampilan play pilih skin ular
// pembuat modul : Salma
void tampilanPlay() {
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

    const char* snakeImages[3] = {
        "assets/snake1.bmp",
        "assets/snake2.bmp",
        "assets/snake3.bmp"
    };

    int currentSnake = 0;
    int totalSnake = 3;

    int panahWidth = 50, panahHeight = 20;
    int snakeWidth = 270, snakeHeight = 20;

    int centerX = fullscreen_width / 2;
    int spacing = 50;
    int iconY = fullscreen_height / 2 - snakeHeight / 2 - 50;

    int tombolLebar = 150, tombolTinggi = 50;
    int posisiX = (fullscreen_width - tombolLebar) / 2;
    int posisiY = iconY + snakeHeight + 80;


    int kiriX1 = centerX - snakeWidth / 2 - spacing - panahWidth;
    int kiriY1 = iconY + (snakeHeight - panahHeight) / 2;
    int kiriX2 = kiriX1 + panahWidth;
    int kiriY2 = kiriY1 + panahHeight;

    int kananX1 = centerX + snakeWidth / 2 + spacing;
    int kananY1 = kiriY1;
    int kananX2 = kananX1 + panahWidth;
    int kananY2 = kananY1 + panahHeight;

    
    readimagefile("assets/pkiri.bmp", kiriX1, kiriY1, kiriX2, kiriY2);
    readimagefile("assets/pkanan.bmp", kananX1, kananY1, kananX2, kananY2);
    tombol(posisiX, posisiY, tombolLebar, tombolTinggi, "GREEN", "Play", 3);


    readimagefile(
        snakeImages[currentSnake],
        centerX - snakeWidth / 2,
        iconY,
        centerX + snakeWidth / 2,
        iconY + snakeHeight
    );

    while (1) {
        int x, y;
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);


            if (x >= kiriX1 && x <= kiriX2 && y >= kiriY1 && y <= kiriY2) {
                currentSnake = (currentSnake - 1 + totalSnake) % totalSnake;

               
                setfillstyle(SOLID_FILL, BLACK);
                bar(centerX - snakeWidth / 2, iconY, centerX + snakeWidth / 2, iconY + snakeHeight);

          
                readimagefile(
                    snakeImages[currentSnake],
                    centerX - snakeWidth / 2,
                    iconY,
                    centerX + snakeWidth / 2,
                    iconY + snakeHeight
                );
            }

 
            else if (x >= kananX1 && x <= kananX2 && y >= kananY1 && y <= kananY2) {
                currentSnake = (currentSnake + 1) % totalSnake;

             
                setfillstyle(SOLID_FILL, BLACK);
                bar(centerX - snakeWidth / 2, iconY, centerX + snakeWidth / 2, iconY + snakeHeight);

              
                readimagefile(
                    snakeImages[currentSnake],
                    centerX - snakeWidth / 2,
                    iconY,
                    centerX + snakeWidth / 2,
                    iconY + snakeHeight
                );
            }

      
            else if (x >= posisiX && x <= posisiX + tombolLebar && y >= posisiY && y <= posisiY + tombolTinggi) {
                selectedSnakeIndex = currentSnake;
                gameOver = false;
                tampilanArena();
                break;
            }
        }

        delay(30);
    }
}

// prosedur untuk tampilan arena ingame
// pembuat modul : Salma
void tampilanArena() 
{
    setbkcolor(WHITE);
    cleardevice();

    Kotak(20, 60, SCREEN_WIDTH - 20, SCREEN_HEIGHT - 20, "BLACK");

    tombol(520, 15, 100, 30, "GREEN", "PAUSE", 2);
    
    tampilkanLeaderboard();

    // Inisialisasi ular
    InitUlar();

    // Mulai loop game
    LoopGame();
}


// prosedur untuk tampilan popup saat game di pause
// pembuat modul : Salma
void PopUpPause() 
{
    int popupX = SCREEN_WIDTH / 4;
    int popupY = SCREEN_HEIGHT / 4;
    int popupWidth = SCREEN_WIDTH / 2;
    int popupHeight = SCREEN_HEIGHT / 2;

    Kotak(popupX, popupY, popupX + popupWidth, popupY + popupHeight, "CYAN");
    setbkcolor(CYAN); 
    tulisan(popupX + popupWidth / 2, popupY + 50, 0, 0, "GREY", "GAME PAUSED", 5, Center);
    tombol(popupX + (popupWidth / 2) - 50, popupY + popupHeight / 2 - 20, 100, 40, "GREEN", "RESUME", 2);
    tombol(popupX + (popupWidth / 2) - 50, popupY + popupHeight / 2 + 30, 100, 40, "RED", "EXIT", 2);
    setbkcolor(CYAN);
}


// prosedur untuk tampilan input nama
// pembuat modul : Salma
void tampilanInput() {
    setbkcolor(BLACK);
    cleardevice();

    Titik(); 

   
    readimagefile(
        "assets/judul.bmp",
        (getmaxx() - 300) / 2,
        10 + 50, 
        (getmaxx() - 300) / 2 + 300,
        10 + 50 + 207 
    );

    int layarTengahX = getmaxx() / 2;

    setcolor(WHITE);
    setbkcolor(BLACK);
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    outtextxy(layarTengahX - textwidth((char*)"Masukkan Nama")/2, 370, (char*)"Masukkan Nama");

 
    int kotakW = 300;
    int kotakH = 40;
    int kotakX = layarTengahX - kotakW/2;
    int kotakY = 420;

    setfillstyle(SOLID_FILL, WHITE);
    bar(kotakX, kotakY, kotakX + kotakW, kotakY + kotakH);


    int tombolLebar = 200;
    int tombolTinggi = 50;
    int posisiX = (getmaxx() - tombolLebar) / 2;
    int posisiY = kotakY + 85;

    tombol(posisiX, posisiY, tombolLebar, tombolTinggi, "ORANGE", "MASUK", 3);

    inputNama(nama, kotakX, kotakY, kotakW, kotakH, posisiX, posisiY, tombolLebar, tombolTinggi);

    closegraph();
}

// Fungsi untuk menggambar titik-titik putih secara acak di layar
// pembuat modul : Salma
void Titik() 
{
    int jml = 20;  
    int ukuran = 4;

    srand(time(NULL)); // Seed untuk posisi acak

    for (int i = 0; i < jml; i++) {
        int x = rand() % getmaxx(); // Acak posisi x
        int y = rand() % getmaxy(); // Acak posisi y

        setfillstyle(SOLID_FILL, AmbilWarna("WHITE"));
        fillellipse(x, y, ukuran / 2, ukuran / 2); 
    }
}

// Fungsi untuk menggambar awan
// pembuat modul : Salma
void gambarAwan(int x, int y) 
{
    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(x, y, 30, 20);
    fillellipse(x + 20, y + 10, 30, 20);
    fillellipse(x - 20, y + 10, 30, 20);
    fillellipse(x + 40, y, 30, 20);
    fillellipse(x - 40, y, 30, 20);
}

// Prosedur untuk menampilkan leaderboard di arena main
// pembuat modul : Salma
// Fungsi menampilkan tabel leaderboard dengan dummy data
// Pembuat modul : Salma
// Dimodifikasi oleh : -
void tampilkanLeaderboard() {
    int kotak_width = 530;
    int kotak_height = 620;
    int spacing = 600;

    int x1 = SCREEN_WIDTH - kotak_width - 20 + spacing;
    int y1 = 60;
    int x2 = SCREEN_WIDTH - 20 + spacing;
    int y2 = y1 + kotak_height;

    Kotak(x1, y1, x2, y2, "BLACK"); // Kotak utama
    setbkcolor(CYAN);

    int imageHeight = 60;
    readimagefile("assets/group_leaderboard.bmp", x1 + 10, y1 + 10, x2 - 10, y1 + imageHeight);

    // Kolom teks (judul)
    int kolomNoX = x1 + 20;
    int kolomNamaX = x1 + 80;
    int kolomSkorX = x1 + 270;
    int kolomWaktuX = x1 + 390;
    int awalY = y1 + imageHeight + 20;

    // Header tabel
    setbkcolor(BLACK);
    tulisan(kolomNoX, awalY, 0, 0, "WHITE", "No", 1, Random);
    tulisan(kolomNamaX, awalY, 0, 0, "WHITE", "Nama", 1, Random);
    tulisan(kolomSkorX, awalY, 0, 0, "WHITE", "Skor", 1, Random);
    tulisan(kolomWaktuX, awalY, 0, 0, "WHITE", "Waktu", 1, Random);
    setbkcolor(CYAN);

    int barisTinggi = 30;
    AmbilDataLeaderboard();

    for (int i = 0; i < 15; i++) {
        int barisY = awalY + 10 + (i + 1) * barisTinggi;

        setfillstyle(SOLID_FILL, BLACK);
        bar(x1 + 10, barisY - 5, x2 - 10, barisY + barisTinggi - 10);
    
        char noStr[10], skorStr[10], waktuStr[10];
        sprintf(noStr, "%d", i + 1);
        sprintf(skorStr, "%d", leaderboard[i].skor);
        sprintf(waktuStr, "%ds", leaderboard[i].waktu);
    
        setbkcolor(BLACK);
        tulisan(kolomNoX, barisY, 0, 0, "WHITE", noStr, 1, Random);
        tulisan(kolomNamaX, barisY, 0, 0, "WHITE", leaderboard[i].nama, 1, Random);
        tulisan(kolomSkorX, barisY, 0, 0, "WHITE", skorStr, 1, Random);
        tulisan(kolomWaktuX, barisY, 0, 0, "WHITE", waktuStr, 1, Random);
        setbkcolor(CYAN);
    }
    
}

// Prosedur untuk menampilkan leaderboard di arena Menu
// pembuat modul : Salma
// Dimodifikasi oleh : -
void tampilanLeaderboardMenu() {
    int kotak_width = 360;
    int kotak_height = 650;

    int x1 = (fullscreen_width - kotak_width) / 2;
    int y1 = (fullscreen_height - kotak_height) / 2;
    int x2 = x1 + kotak_width;
    int y2 = y1 + kotak_height;

    cleardevice();
    
    Kotak(0, 0, fullscreen_width, fullscreen_height, "BLACK"); 

    Titik(); 
    
    // Background Multi Layer
    for(int i = 0; i < 20; i++) {
        Kotak(x1 - i*2, y1 - i*2, x2 + i*2, y2 + i*2, (i % 2 == 0) ? "DARKGRAY" : "WHITE");
    }

    // Border kotak utama
    Kotak(x1-3, y1-3, x2+3, y2+3, "BLUE");
    Kotak(x1-1, y1-1, x2+1, y2+1, "WHITE");

   
    Kotak(x1 + 10, y1 + 5, x2 - 10, y1 + 75, "DARKGRAY");
    
    // Gambar trophy
    int trophy_x = x1 + 40;
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, YELLOW);

    fillellipse(trophy_x, y1 + 40, 15, 12); //Kepala trophy
    setfillstyle(SOLID_FILL, BROWN);
    bar(trophy_x - 8, y1 + 50, trophy_x + 8, y1 + 60); //Batang trophy
    bar(trophy_x - 15, y1 + 60, trophy_x + 15, y1 + 65); //Dasar trophy

    // Tombol untuk kembali ke menu awal
    int tombolLebar = 38; 
    int tombolTinggi = 35;
    int buttonX = x2 + 2 - tombolLebar + 40 - 2;
    int buttonY = y1 - 37; 

    tombol(buttonX, buttonY, tombolLebar, tombolTinggi, "RED", "X", 2);
    
    // Border button menu awal
    setcolor(AmbilWarna("BLUE"));
    setlinestyle(SOLID_LINE, 0, 2);
    rectangle(buttonX, buttonY, buttonX + tombolLebar, buttonY + tombolTinggi);

    // Judul Leaderboard
    int lebarTulisan = 200;
    int posisiTulisanHeader  = x1 + (kotak_width - lebarTulisan) / 2;
    
    setbkcolor(DARKGRAY);
    tulisan(posisiTulisanHeader  + 2, y1 + 32, 0, 0, "BLACK", "LEADERBOARD", 2, Random);
    tulisan(posisiTulisanHeader , y1 + 30, 0, 0, "YELLOW", "LEADERBOARD", 2, Random);

    int posisiTulisanSubheader = x1 + 80; 
    tulisan(posisiTulisanSubheader, y1 + 50, 0, 0, "CYAN", "SNACK SNAKE", 1, Random);

    // Header tabel biru
    int headerY = y1 + 80;
    Kotak(x1 + 10, headerY, x2 - 10, headerY + 35, "BLUE");
    
    // Border header tabel
    setcolor(WHITE);
    setlinestyle(SOLID_LINE, 0, 2);
    rectangle(x1 + 10, headerY, x2 - 10, headerY + 35);

    // Posisi kolom
    int kolomNoX = x1 + 25;
    int kolomNamaX = x1 + 70;
    int kolomSkorX = x1 + 220;
    int kolomWaktuX = x1 + 280;

    // Header Kolom Teks
    setbkcolor(BLUE);
    tulisan(kolomNoX, headerY + 10, 0, 0, "WHITE", "No", 1, Random);
    tulisan(kolomNamaX, headerY + 10, 0, 0, "WHITE", "NAMA PLAYER", 1, Random);
    tulisan(kolomSkorX, headerY + 10, 0, 0, "WHITE", "SKOR", 1, Random);
    tulisan(kolomWaktuX, headerY + 10, 0, 0, "WHITE", "WAKTU", 1, Random);

    int barisTinggi = 35;
    int awalDataY = headerY + 45;
    
    AmbilDataLeaderboard();

    for (int i = 0; i < 15; i++) {
        int barisY = awalDataY + i * barisTinggi;
        
        // Gambar kotak untuk setiap baris
        const char* warna = (i % 2 == 0) ? "BLACK" : "DARKGRAY";
        
        Kotak(x1 + 10, barisY, x2 - 10, barisY + barisTinggi - 5, warna);

        char noStr[10], skorStr[20], waktuStr[15];
        sprintf(noStr, "%d", i + 1);
        sprintf(skorStr, "%d", leaderboard[i].skor);
        sprintf(waktuStr, "%ds", leaderboard[i].waktu);

       const char* textColor = "YELLOW";
       setcolor(AmbilWarna(textColor));
       setbkcolor(AmbilWarna(warna));  
       
       tulisan(kolomNoX, barisY + 8, 0, 0, textColor, noStr, 1, Random);
       tulisan(kolomNamaX, barisY + 8, 0, 0, textColor, leaderboard[i].nama, 1, Random);
       tulisan(kolomSkorX, barisY + 8, 0, 0, textColor, skorStr, 1, Random);
       tulisan(kolomWaktuX, barisY + 8, 0, 0, textColor, waktuStr, 1, Random);

    }

    int ch;
    while (1) {
  
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int mouseX, mouseY;
            getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);
            
            if (mouseX >= buttonX && mouseX <= buttonX + tombolLebar &&
                mouseY >= buttonY && mouseY <= buttonY + tombolTinggi) {
                tampilanAwal();
                return;
            }
        }
        
        if (kbhit()) {
            ch = getch();
            if (ch == 27) {  
                tampilanAwal();
                return;
            }
        }
        
        delay(50);
    }
}

// Prosedur untuk menampilkan tampilan panduan bermain
// Pembuat modul : Salma 
// Dimodifikasi oleh : -
void tampilanGuide() {
    cleardevice();
    setbkcolor(BLACK);
    cleardevice();

    int screenW = getmaxx();
    int screenH = getmaxy();

    // Background pattern 
    setlinestyle(SOLID_LINE, 0, 1);

    for (int y = 0; y < screenH; y += 30) {
        for (int x = 0; x < screenW; x += 30) {
            line(x, y + 15, x + 15, y);
            line(x + 15, y, x + 30, y + 15);
            line(x + 30, y + 15, x + 15, y + 30);
            line(x + 15, y + 30, x, y + 15);
        }
    }

    // Header persegi (tanpa lengkungan)
    int headerW = 500;
    int headerH = 80;
    int headerX = (screenW - headerW) / 2;
    int headerY = 80;
    int textAreaX = headerX + (headerW / 2);
    int textAreaY = headerY + (headerH / 2);
   
    setfillstyle(SOLID_FILL, BLUE);
    bar(headerX, headerY, headerX + headerW, headerY + headerH);

    // Border cyan untuk header
    setcolor(CYAN);
    setlinestyle(SOLID_LINE, 0, 4);
    rectangle(headerX, headerY, headerX + headerW, headerY + headerH);

    setbkcolor(BLUE);
    tulisan(headerX, headerY, headerW, headerH, "YELLOW", "GUIDE", 7, Center);

    // Main content box
    int contentW = 700;
    int contentH = 400;
    int contentX = (screenW - contentW) / 2;
    int contentY = 200;

    setfillstyle(SOLID_FILL, BLUE);
    bar(contentX, contentY, contentX + contentW, contentY + contentH);

    setcolor(MAGENTA);
    setlinestyle(SOLID_LINE, 0, 4);
    rectangle(contentX - 3, contentY - 3, contentX + contentW + 3, contentY + contentH + 3);

    setbkcolor(AmbilWarna("NAVY"));
    tulisan(contentX + 50, contentY + 30, contentW - 100, 40, "YELLOW", "CARA BERMAIN:", 3, Center);

    int instrY = contentY + 100;
    int iconX = contentX + 80;

    // Panah
    readimagefile("assets/arrow.bmp", iconX, instrY, iconX + 60, instrY + 60);
    tulisan(iconX + 80, instrY + 10, contentW - 200, 25, "YELLOW", "Gunakan tombol", 2, Random);
    tulisan(iconX + 80, instrY + 35, contentW - 200, 25, "YELLOW", "panah untuk bergerak", 2, Random);

    // Apel
    instrY += 100;
    readimagefile("assets/apple.bmp", iconX, instrY, iconX + 60, instrY + 60);

    // Teks untuk apel
    int textY = instrY - 5;
    tulisan(iconX + 70, textY, contentW - 200, 25, "YELLOW", "Skor Makanan:", 2, Random);
    tulisan(iconX + 70, textY + 25, contentW - 200, 25, "RED",    "Merah   : +1 (Normal)", 2, Random);
    tulisan(iconX + 70, textY + 45, contentW - 200, 25, "YELLOW", "Kuning  : +5 (Spesial)", 2, Random);
    tulisan(iconX + 70, textY + 65, contentW - 200, 25, "GREEN",  "Hijau   : -1 (Racun)", 2, Random);


    // Dinding
    instrY += 100;
    setcolor(RED);
    setlinestyle(SOLID_LINE, 0, 5);
    circle(iconX + 30, instrY + 30, 30);
    readimagefile("assets/wall.bmp", iconX + 15, instrY + 15, iconX + 45, instrY + 45);
    setcolor(RED);
    setlinestyle(SOLID_LINE, 0, 4);
    line(iconX + 10, instrY + 10, iconX + 50, instrY + 50);
    line(iconX + 10, instrY + 50, iconX + 50, instrY + 10);
    tulisan(iconX + 80, instrY + 10, contentW - 200, 25, "YELLOW", "Hindari dinding arena dan", 2, Random);
    tulisan(iconX + 80, instrY + 35, contentW - 200, 25, "YELLOW", "tubuhmu sendiri", 2, Random);

    // Tombol kembali ke menu
    int bottomBtnW = 400;
    int bottomBtnH = 60;
    int bottomBtnX = (screenW - bottomBtnW) / 2;
    int bottomBtnY = contentY + contentH + 60;

    setfillstyle(SOLID_FILL, MAGENTA);
    bar(bottomBtnX, bottomBtnY, bottomBtnX + bottomBtnW, bottomBtnY + bottomBtnH);

    setcolor(CYAN);
    setlinestyle(SOLID_LINE, 0, 3);
    rectangle(bottomBtnX - 2, bottomBtnY - 2, bottomBtnX + bottomBtnW + 2, bottomBtnY + bottomBtnH + 2);

    setbkcolor(MAGENTA);
    tulisan(bottomBtnX, bottomBtnY + 15, bottomBtnW, 30, "YELLOW", "KEMBALI KE MENU", 2, Center);

    setbkcolor(BLACK);

    int ch;
    while (1) {
        if (kbhit()) {
            ch = getch();
            tampilanAwal();
            break;
        }

        if (ismouseclick(WM_LBUTTONDOWN)) {
            int mx, my;
            getmouseclick(WM_LBUTTONDOWN, mx, my);
            if (mx >= bottomBtnX && mx <= bottomBtnX + bottomBtnW &&
                my >= bottomBtnY && my <= bottomBtnY + bottomBtnH) {
                tampilanAwal();
                break;
            }
        }

        delay(50);
    }
}
