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
}
    fclose(file);
}

// Fungsi untuk menulis data alat ke file
void simpanAlat() {
    FILE *file = fopen("alatlab.txt", "w");
    if (file == NULL) {
        printf("Error membuka file alatlab.txt untuk menulis\n");
        return;
    }
    for (int i = 0; i < jumlahAlat; i++) {
        fprintf(file, "%u|%s|%s|%s|%u|%u|%u\n", alatLab[i].id, alatLab[i].nama, alatLab[i].merek,
                alatLab[i].model, alatLab[i].tahunProduksi, alatLab[i].jumlahUnit, alatLab[i].jumlahTersedia);
    }
    fclose(file);
}

// Fungsi untuk membaca status peminjaman alat
void bacaPeminjaman() {
    FILE *file = fopen("peminjaman.txt", "r");
    if (file == NULL) {
        printf("Error membuka file peminjaman.txt\n");
        return;
    }

    jumlahRiwayatPeminjaman = 0;
    while (fscanf(file, "%u|%[^|]|%[^|]|%u\n", 
        &riwayatPeminjaman[jumlahRiwayatPeminjaman].id_alat,
        riwayatPeminjaman[jumlahRiwayatPeminjaman].nama_alat,
        riwayatPeminjaman[jumlahRiwayatPeminjaman].username_peminjam,
        &riwayatPeminjaman[jumlahRiwayatPeminjaman].jumlah_peminjaman) != EOF) {
        jumlahRiwayatPeminjaman++;
    }

    fclose(file);
}

// Fungsi untuk menulis status peminjaman ke file
void simpanPeminjaman() {
    FILE *file = fopen("peminjaman.txt", "w");
    if (file == NULL) {
        printf("Error membuka file peminjaman.txt untuk menulis\n");
        return;
    }
    for (int i = 0; i < jumlahRiwayatPeminjaman; i++) {
        fprintf(file, "%u|%s|%s|%u\n", 
            riwayatPeminjaman[i].id_alat,
            riwayatPeminjaman[i].nama_alat,
            riwayatPeminjaman[i].username_peminjam,
            riwayatPeminjaman[i].jumlah_peminjaman);
    }
    fclose(file);
}

// Fungsi untuk menghapus peminjaman dari riwayat
void hapusPeminjamanDariRiwayat(unsigned int id_alat, const char* username) {
    int index_hapus = -1;
    for (int i = 0; i < jumlahRiwayatPeminjaman; i++) {
        if (riwayatPeminjaman[i].id_alat == id_alat && 
            strcmp(riwayatPeminjaman[i].username_peminjam, username) == 0) {
            index_hapus = i;
            break;
        }
    }

    if (index_hapus != -1) {
        // Geser elemen untuk menghapus entri
        for (int i = index_hapus; i < jumlahRiwayatPeminjaman - 1; i++) {
            riwayatPeminjaman[i] = riwayatPeminjaman[i + 1];
