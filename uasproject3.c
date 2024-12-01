#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALAT 100
#define MAX_AKUN 10
#define MAX_NAMA_ALAT 100
#define MAX_MODEL_ALAT 50
#define MAX_PEMINJAMAN 500

// Struktur data untuk alat lab
typedef struct {
    unsigned int id;
    char nama[MAX_NAMA_ALAT];
    char merek[MAX_NAMA_ALAT];
    char model[MAX_MODEL_ALAT];
    unsigned int tahunProduksi;
    unsigned int jumlahUnit;
    unsigned int jumlahTersedia;
} AlatLab;

// Struktur data untuk akun
typedef struct {
    char username[50];
    char password[50];
} Akun;

// Struktur data untuk peminjaman alat
typedef struct {
    unsigned int id_alat;
    char nama_alat[MAX_NAMA_ALAT];
    char username_peminjam[50]; // Username peminjam
    unsigned int jumlah_peminjaman; // Jumlah alat yang dipinjam
} Peminjaman;

// Deklarasi array dan variabel global
AlatLab alatLab[MAX_ALAT];
Akun akun[MAX_AKUN];
Peminjaman riwayatPeminjaman[MAX_PEMINJAMAN];
int jumlahAlat = 0;
int jumlahAkun = 0;
int jumlahRiwayatPeminjaman = 0;

// Fungsi untuk membaca data akun dari file
void bacaAkun() {
    FILE *file = fopen("akun.txt", "r");
    if (file == NULL) {
        printf("Error membuka file akun.txt\n");
        return;
    }
    while (fscanf(file, "%s %s", akun[jumlahAkun].username, akun[jumlahAkun].password) != EOF) {
        jumlahAkun++;
    }
    fclose(file);
}

// Fungsi untuk membaca data alat dari file
void bacaAlat() {
    FILE *file = fopen("alatlab.txt", "r");
    if (file == NULL) {
        printf("Error membuka file alatlab.txt\n");
        return;
    }
    while (fscanf(file, "%u|%[^|]|%[^|]|%[^|]|%u|%u|%u\n", 
                   &alatLab[jumlahAlat].id, alatLab[jumlahAlat].nama,
                   alatLab[jumlahAlat].merek, alatLab[jumlahAlat].model,
                   &alatLab[jumlahAlat].tahunProduksi, &alatLab[jumlahAlat].jumlahUnit, 
                   &alatLab[jumlahAlat].jumlahTersedia) != EOF) {
        jumlahAlat++;
