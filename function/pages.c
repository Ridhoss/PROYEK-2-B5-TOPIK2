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
                tampilanPlay();
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
                    } 
                }

               
            }
        }

        delay(50);
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


// prosedur untuk tampilan play sebelum ingame
// pembuat modul : Salma
void tampilanPlay() {
    setbkcolor(BLACK);
    cleardevice();

    Titik();

    int iconWidth = 90, 
    iconHeight = 25;  
    int centerX = fullscreen_width / 2;
    int iconY = fullscreen_height / 2 - iconHeight / 2 - 50;  
    int spacing = 85; 
    

    readimagefile(
        "assets/pkiri.bmp",
        centerX - iconWidth - spacing,
        iconY,
        centerX - spacing,
        iconY + iconHeight
    );
    
    
    readimagefile(
        "assets/snake1.bmp",
        centerX - iconWidth / 2,
        iconY,
        centerX + iconWidth / 2,
        iconY + iconHeight
    );


    readimagefile(
        "assets/pkanan.bmp",
        centerX + spacing,
        iconY,
        centerX + iconWidth + spacing,
        iconY + iconHeight
    );

    char judul[] = "GET READY!";
    tulisan(0, 70, fullscreen_width, 0, "WHITE", judul, 6, Center);


    int tombolLebar = 150, tombolTinggi = 50;
    int posisiX = (fullscreen_width - tombolLebar) / 2;
    int posisiY = iconY + iconHeight + 50;  
    tombol(posisiX, posisiY, tombolLebar, tombolTinggi, "GREEN", "Play", 3);

   
    while (1) {
        int x, y;
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);

            gameOver = false;
            tampilanArena();
            break;
        }
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

    tombol(posisiX, posisiY, tombolLebar, tombolTinggi, "GREEN", "MASUK", 3);

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
void tampilkanLeaderboard() {
    int kotak_width = 340;
    int kotak_height = 450;
    
    int spacing = 370; 

    int x1 = SCREEN_WIDTH - kotak_width - 20 + spacing;
    int y1 = 60;
    int x2 = SCREEN_WIDTH - 20 + spacing;
    int y2 = y1 + kotak_height;

    Kotak(x1, y1, x2, y2, "BLACK");
    setbkcolor(CYAN);

    int imageHeight = 60;  
    readimagefile("assets/group_leaderboard.bmp", x1 + 10, y1 + 10, x2 - 10, y1 + imageHeight);
}