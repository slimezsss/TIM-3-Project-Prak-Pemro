#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int cekKataSudahAda(char daftarKata[][50], char *kataBaru, int jumlahKataSaatIni) {
    for (int i = 0; i < jumlahKataSaatIni; i++) {
        if (strcmp(daftarKata[i], kataBaru) == 0) {
            return 1;
        }
    }
    return 0; 
}

int main() {
    char daftarKata[200][50];
    int jumlahKataUnik = 0;
    char barisTeks[1000];
    
    FILE *fileinput, *fileoutput;
    fileinput = fopen("lirik.txt", "r");

 if (fileinput == NULL) {
        printf("Kesalahan: Tidak dapat membuka file lirik.txt\n");
        return 1;
    }
    
    fileoutput = fopen("kosa-kata.word", "w");
    if (fileoutput == NULL) {
        printf("Kesalahan: Tidak dapat membuat file kosa-kata.word\n");
        fclose(fileoutput);
        return 1;
    }

    fprintf(fileoutput, "[Judul: Drivers License - Olivia Rodrigo]\n\n");

    while (fgets(barisTeks, sizeof(barisTeks), fileinput)) {
        barisTeks[strcspn(barisTeks, "\n")] = '\0';

        char *kataDalamBaris = strtok(barisTeks, " ,.-\n");
        while (kataDalamBaris != NULL) {
            if (!cekKataSudahAda(daftarKata, kataDalamBaris, jumlahKataUnik)) {
                strcpy(daftarKata[jumlahKataUnik], kataDalamBaris);
                jumlahKataUnik++;
            }
            
            // Lanjutkan ke kata berikutnya
            kataDalamBaris = strtok(NULL, " ,.-\n");
        }
       }

    fclose(fileinput);

    for (int i = 0; i < jumlahKataUnik; i++) {
        fprintf(fileoutput, "%s=\n", daftarKata[i]);
    }

    fclose(fileoutput);
    printf("Kata unik berhasil disimpan dalam file kosa-kata.word.\n");
    return 0;
}                                 
