# TIM-3-Project-Prak-Pemro
UAS PROJECT LAB PEMPROGRAMAN A

Kelompok 3
Hazairin_2408107010001
Rijaluddin Abdul Ghani_2408107010008
Raisa Salsa Nabila_2408107010007
Raisa Nabila_2408107010037
Dedek Saleha_2408107010023
Dara Ramadhani_2408107010028
Meurahmah Nushsharie_2408107010035

1.program peminjaman alat lab

terdapat dua pilihan mode akun yaitu, akun admin dan akun user. Dalam mode admin, admin dapat menambah, mengedit , menghapus, serta melihat alat yang tersedia. Sementara dalam mode user, user dapat melihat alat yang tersedia, meminjam alat, dan mengembalikan alat yang sudah dipinjam. Data Peminjaman oleh user akan terdata oleh file peminjaman.txt, data Peminjaman akan hilang jika user telah mengembalikan barang. Setelah, barang yang sudah dikembalikan akan muncul Kembali di file alatlab.txt, dan barang yg dipinjam akan bertambah sesuai jumlah peminjaman oleh user.
 
file uasproject3.c berisi Header, fungsi utama serta fungsi pemanggilan seperti fungsi login, fungsi menu user, menu admin, fungsi baca akun, fungsi baca alat, fungsi simpan alat, fungsi simpan alat, fungsi baca peminjaman alat, fungsi simpan peminjaman alat, fungsi lihat riwayat peminjaman alat, fungsi hapus riwayat peminjaman alat, fungsi tambah alat, fungsi hapus alat, fungsi kembalikan alat, fungsi mengedit alat, fungsi melihat alat, fungsi peminjaman alat, fungsi tampilkan alat, dan fungsi tampilkan riwayat.
file akun.txt menyimpan akun-akun yang terdaftar dalam sistem.
file alatlab.txt menyimpan informasi mengenai alat alat lab yang tersedia.
file peminjaman.txt berisi data peminjaman barang oleh user, dengan format ID alat_nama alat_username peminjam_jumlah peminjaman.

2.program kata unik

Program ini membaca file lirik.txt, mengekstrak kata-kata unik dari lirik tersebut, dan menyimpannya dalam file kosa-kata.word. Fungsi cekKataSudahAda memeriksa apakah kata yang baru ditemukan sudah ada sebelumnya dalam daftar kata unik. Fungsi main membuka file input dan output, membaca baris demi baris dari file lirik, memisahkan kata-kata dengan strtok, dan memastikan setiap kata unik hanya disimpan sekali. Setelah selesai, kata-kata unik ditulis ke dalam file output.

bonus.c berisi header, fungsi utama, fungsi cekKataSudahAda
lirik.txt berisi potongan lirik lagu yang akan digunakan oleh program sebagai data input.
kosa-kata.word file output yang dihasilkan oleh program. File ini berisi daftar kata-kata unik yang diambil dari file input 
