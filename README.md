# PROYEK-2 KELOMPOK-B5 SNAKESNACK TOPIK 2 (LINKED LIST)

Repository untuk penugasan proyek 2 dari kelompok 5 kelas 1B Aplikasi Game Ular Mukbang Apel

Anggota Kelompok 5 :

- Ridho Sulistyo Saputro (059)
- Salma Arifah Zahra (062)
- Samudra Putra Gunawan (063)
- Dimas Rizal Ramadhani (040)
- Akmal Rezaqi Al-Farhan (036)

## Cara melakukan compile aplikasi

1. Instalasi MINGW-32 di komputer anda

2. Install Extension
    - C/C++ Extension Pack : Microsoft
    - C/C+++ Compile Run : danielpinto8zz6

3. Ketik di terminal :
```bash
mingw32-make
```

4. Jika tidak berhasil (skip jika nomor 1 berhasil) :
```bash
g++ main.c function/basicfunction.c function/pages.c function/makanan.c function/stopwatch.c function/ular.c function/mechanism.c main.exe -I"C:\MinGW-w64\mingw64\include" -L"C:\MinGW-w64\mingw64\lib" -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
```

5. Lalu jalankan melalui terminal :
```bash
./main.exe
```

6. Selamat Bermain!

## Modul Modul dan Pemiliknya

Ridho : ridho.c || ridho.h

Salma : salma.c || salma.h

Samudra : samudra.c || samudra.h

Dimas : dimas.c || dimas.h

Akmal : akmal.c || akmal.h