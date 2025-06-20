# Compiler yang digunakan
CC = g++

# Flags untuk kompilasi
CFLAGS = -I"C:\MinGW-w64\mingw64\include"

# Libraries yang diperlukan
LDFLAGS = -L"C:\MinGW-w64\mingw64\lib" -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32 -lwinmm

# Daftar file source code
SRCS = main.c function/ridho.c function/salma.c function/samudra.c function/akmal.c function/dimas.c

# Nama file output
TARGET = main.exe

# Rule untuk kompilasi
$(TARGET): $(SRCS)
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS) $(LDFLAGS)

# Rule untuk membersihkan file hasil kompilasi
clean:
	del $(TARGET)