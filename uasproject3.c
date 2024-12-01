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
}
        jumlahRiwayatPeminjaman--;
        simpanPeminjaman();
    }
}

// Fungsi untuk melihat riwayat peminjaman
void lihatRiwayatPeminjaman() {
    printf("Riwayat Peminjaman:\n");
    printf("ID Alat | Nama Alat | Username Peminjam | Jumlah Peminjaman\n");
    printf("-----------------------------------------------------------\n");
    for (int i = 0; i < jumlahRiwayatPeminjaman; i++) {
        printf("%u | %s | %s | %u\n", 
            riwayatPeminjaman[i].id_alat,
            riwayatPeminjaman[i].nama_alat,
            riwayatPeminjaman[i].username_peminjam,
            riwayatPeminjaman[i].jumlah_peminjaman);
    }
}

// Fungsi untuk login
int login() {
    char username[50], password[50];
    printf("Masukkan username: ");
    scanf("%s", username);
    printf("Masukkan password: ");
    scanf("%s", password);

    for (int i = 0; i < jumlahAkun; i++) {
        if (strcmp(username, akun[i].username) == 0 && strcmp(password, akun[i].password) == 0) {
            return i; // Mengembalikan index akun yang berhasil login
        }
    }
    return -1; // Login gagal
}

// Fungsi untuk menambah alat oleh admin
void tambahAlat() {
    if (jumlahAlat >= MAX_ALAT) {
        printf("Jumlah alat mencapai batas maksimum.\n");
        return;
    }

    AlatLab alat;
    printf("Masukkan ID alat: ");
    scanf("%u", &alat.id);
    printf("Masukkan nama alat: ");
    getchar(); // Membersihkan newline
    fgets(alat.nama, sizeof(alat.nama), stdin);
    alat.nama[strcspn(alat.nama, "\n")] = '\0'; // Menghapus newline
    printf("Masukkan merek alat: ");
    fgets(alat.merek, sizeof(alat.merek), stdin);
    alat.merek[strcspn(alat.merek, "\n")] = '\0'; // Menghapus newline
    printf("Masukkan model alat: ");
    fgets(alat.model, sizeof(alat.model), stdin);
    alat.model[strcspn(alat.model, "\n")] = '\0'; // Menghapus newline
    printf("Masukkan tahun produksi: ");
    scanf("%u", &alat.tahunProduksi);
    printf("Masukkan jumlah unit: ");
    scanf("%u", &alat.jumlahUnit);

    alat.jumlahTersedia = alat.jumlahUnit;
    alatLab[jumlahAlat] = alat;
    jumlahAlat++;
    simpanAlat(); // Simpan data alat yang baru ditambahkan ke file
    printf("Alat berhasil ditambahkan.\n");
}

// Fungsi untuk menghapus alat oleh admin
void hapusAlat() {
    unsigned int id;
    printf("Masukkan ID alat yang ingin dihapus: ");
    scanf("%u", &id);

    int index = -1;
    for (int i = 0; i < jumlahAlat; i++) {
        if (alatLab[i].id == id) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        for (int i = index; i < jumlahAlat - 1; i++) {
            alatLab[i] = alatLab[i + 1];
        }
        jumlahAlat--;
        simpanAlat(); // Simpan data setelah penghapusan
        printf("Alat berhasil dihapus.\n");
    } else {
        printf("Alat dengan ID %u tidak ditemukan.\n", id);
    }
}

// Fungsi untuk mengedit alat oleh admin
void editAlat() {
    unsigned int id;
    printf("Masukkan ID alat yang ingin diedit: ");
    scanf("%u", &id);

    int index = -1;
    for (int i = 0; i < jumlahAlat; i++) {
        if (alatLab[i].id == id) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        printf("Masukkan nama alat baru: ");
        getchar(); // Membersihkan newline
        fgets(alatLab[index].nama, sizeof(alatLab[index].nama), stdin);
        alatLab[index].nama[strcspn(alatLab[index].nama, "\n")] = '\0'; // Menghapus newline

        printf("Masukkan merek alat baru: ");
        fgets(alatLab[index].merek, sizeof(alatLab[index].merek), stdin);
        alatLab[index].merek[strcspn(alatLab[index].merek, "\n")] = '\0'; // Menghapus newline

        printf("Masukkan model alat baru: ");
        fgets(alatLab[index].model, sizeof(alatLab[index].model), stdin);
        alatLab[index].model[strcspn(alatLab[index].model, "\n")] = '\0'; // Menghapus newline

        printf("Masukkan tahun produksi baru: ");
        scanf("%u", &alatLab[index].tahunProduksi);

        printf("Masukkan jumlah unit baru: ");
        scanf("%u", &alatLab[index].jumlahUnit);

        alatLab[index].jumlahTersedia = alatLab[index].jumlahUnit;
        simpanAlat(); // Simpan data alat yang sudah diedit
        printf("Alat berhasil diedit.\n");
    } else {
        printf("Alat dengan ID %u tidak ditemukan.\n", id);
    }
}

// Fungsi untuk melihat daftar alat
void lihatAlat() {
    printf("Daftar alat yang tersedia:\n");
    for (int i = 0; i < jumlahAlat; i++) {
     printf("ID: %u, Nama: %s, Merek: %s, Model: %s, Tahun: %u, Jumlah: %u, Tersedia: %u\n",
                alatLab[i].id, alatLab[i].nama, alatLab[i].merek, alatLab[i].model,
                alatLab[i].tahunProduksi, alatLab[i].jumlahUnit, alatLab[i].jumlahTersedia);
    }
}

// Fungsi untuk meminjam alat
void pinjamAlat() {
    unsigned int id;
    printf("Masukkan ID alat yang ingin dipinjam: ");
    scanf("%u", &id);

    int index = -1;
    for (int i = 0; i < jumlahAlat; i++) {
        if (alatLab[i].id == id) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        unsigned int jumlahPeminjaman;
        printf("Masukkan jumlah alat yang ingin dipinjam: ");
        scanf("%u", &jumlahPeminjaman);

        if (jumlahPeminjaman <= alatLab[index].jumlahTersedia) {
            alatLab[index].jumlahTersedia -= jumlahPeminjaman;
            simpanAlat(); // Simpan status setelah peminjaman
            printf("Alat berhasil dipinjam.\n");

            // Menambahkan peminjaman ke riwayat
            Peminjaman peminjaman_baru;
            peminjaman_baru.id_alat = alatLab[index].id;
            strcpy(peminjaman_baru.nama_alat, alatLab[index].nama);
            printf("Masukkan username peminjam: ");
            scanf("%s", peminjaman_baru.username_peminjam);

            peminjaman_baru.jumlah_peminjaman = jumlahPeminjaman; // Menyimpan jumlah peminjaman

            riwayatPeminjaman[jumlahRiwayatPeminjaman++] = peminjaman_baru;
            simpanPeminjaman();  // Menyimpan peminjaman ke file
        } else {
            printf("Alat tidak tersedia dalam jumlah yang cukup.\n");
        }
    } else {
        printf("Alat dengan ID %u tidak ditemukan.\n", id);
    }
}

// Fungsi untuk mengembalikan alat
void kembalikanAlat() {
    unsigned int id;
    printf("Masukkan ID alat yang ingin dikembalikan: ");
    scanf("%u", &id);

    int index = -1;
    for (int i = 0; i < jumlahAlat; i++) {
        if (alatLab[i].id == id) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        // Cari peminjaman berdasarkan alat yang dikembalikan
        for (int i = 0; i < jumlahRiwayatPeminjaman; i++) {
            if (riwayatPeminjaman[i].id_alat == id) {
                // Mengembalikan alat sesuai jumlah yang dipinjam
                alatLab[index].jumlahTersedia += riwayatPeminjaman[i].jumlah_peminjaman;
                simpanAlat(); // Simpan status setelah pengembalian

