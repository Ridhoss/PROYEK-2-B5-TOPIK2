# PROYEK-2 KELOMPOK-B5 SNAKESNACK

Repository untuk penugasan proyek 2 dari kelompok 5 kelas 1B Aplikasi Game Ular Mukbang

Anggota Kelompok 5 :

- Ridho Sulistyo Saputro (059)
- Salma Arifah Zahra (062)
- Samudra Putra Gunawan (063)
- Dimas Rizal Ramadhani (040)
- Akmal Rezaqi Al-Farhan (036)

## Cara melakukan compile aplikasi

1. Ketik di terminal :
```bash
mingw32-make
```

2. Jika tidak berhasil (skip jika nomor 1 berhasil) :
```bash
g++ main.c function/basicfunction.c function/pages.c function/makanan.c function/stopwatch.c function/ular.c function/mechanism.c main.exe -I"C:\MinGW-w64\mingw64\include" -L"C:\MinGW-w64\mingw64\lib" -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
```

3. Lalu jalankan melalui terminal :
```bash
./main.exe
```

## Modul Modul dan Pemiliknya

Ridho : 
- Modul AmbilWarna
- Modul tulisan
- Modul Kotak
- Modul tombol
- Modul ResetGame
- Modul tampilanAwal
- Modul PopUpPause

Salma : 
- Modul Titik
- Modul gambarAwan
- Modul Tombolpause
- Modul HandlePause
- Modul tampilanPlay
- Modul tampilanArena

Samudra : 
- Modul GenerateRandomPosition
- Modul GeneratemakananType
- Modul Makanan
- Modul TampilkanScore

Dimas : 
- Modul LoopGame
- Modul InitUlar
- Modul GerakUlar
- Modul CekTabrakan
- Modul CekMakanMakanan
- Modul GambarUlar

Farhan : 
- Modul Stopwatch
- Modul startStopwatch