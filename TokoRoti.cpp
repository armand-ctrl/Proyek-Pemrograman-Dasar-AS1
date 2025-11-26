#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "IsiAdmin.h"

void MemberBeliRoti(std::vector<Roti>& daftar, Member& member) {
    std::string namaRoti;
    int jumlahBeli;
    tampilkanroti(daftar);
    std::cout << "Masukkan nama roti yang ingin dibeli: ";
    std::getline(std::cin, namaRoti);
    std::cout << "Masukkan jumlah roti yang ingin dibeli: ";
    std::cin >> jumlahBeli;
    std::cin.ignore(); 
    member.CookiesCounter += jumlahBeli;
    int newBonuses = member.CookiesCounter / 3;
    member.CookiesCounter = member.CookiesCounter % 3;
    for (auto& roti : daftar) {
        if (roti.nama == namaRoti) {
            if (roti.stok >= jumlahBeli) {
                double totalHarga = roti.harga * jumlahBeli;
                if (member.getSaldo() >= totalHarga) {
                    roti.stok -= jumlahBeli;
                    roti.terjual += jumlahBeli;
                    member.kurangsaldroti(totalHarga);
                    member.rotiDibeli += jumlahBeli;
                    member.detailPembelian[namaRoti] += jumlahBeli;
                    std::cout << "Pembelian berhasil! Total harga: " << totalHarga << "\n";
                    if (newBonuses > 0 && member.getnama() != "Guest") {
                        std::cout << "Selamat! Anda mendapatkan " << newBonuses << " cookies bonus dari pembelian roti ini!\n";
                        member.detailPembelian["Cookies"] += newBonuses;
                    }
                } else {
                    std::cout << "Saldo tidak cukup untuk melakukan pembelian.\n";
                }
            } else {
                std::cout << "Stok roti tidak mencukupi.\n";
            }
            return;
        }
    }
    std::cout << "Roti dengan nama tersebut tidak ditemukan.\n";
}



void MenuAdmin (admin& adm, std::vector<Roti>& daftarRoti){
    int pilihanAdmin;
    do {
        std::cout << "\nMenu Admin:\n1. Lihat Daftar Roti\n2. Tambah Roti\n3. Tambah Stok Roti\n4. Hapus Roti\n5. Lihat Keuntungan Penjualan\n6. Tampilkan Member Toko\n7. Hapus Member\n8. Kurangi Stok\n0. Keluar\nPilih: ";
        std::cin >> pilihanAdmin;
        std::cin.ignore(); 
        switch (pilihanAdmin){
            case 1:
                tampilkanroti(daftarRoti);
                break;
            case 2:
                adm.tambahRoti(daftarRoti);
                break;
            case 3:
                adm.tambahStok(daftarRoti);
                break;
            case 4:
                adm.hapusroti(daftarRoti);
                break;
            case 5:
                adm.keuntungan(daftarRoti);
                break;
            case 6:
                adm.lihatMember(adm.daftarMember);
                break;
            case 7:
                {
                    std::string usernameToDelete;
                    std::cout << "Masukkan username member yang ingin dihapus: ";
                    std::getline(std::cin, usernameToDelete);
                    adm.hapusMember(usernameToDelete);
                }
                break;
            case 8:
                {
                    std::string namaRoti;
                    int jumlah;
                    tampilkanroti(daftarRoti);
                    std::cout << "Masukkan nama roti yang stoknya ingin dikurangi: ";
                    std::getline(std::cin, namaRoti);
                    std::cout << "Masukkan jumlah stok yang ingin dikurangi: ";
                    std::cin >> jumlah;
                    std::cin.ignore(); 
                    adm.kurangistok(namaRoti, jumlah, daftarRoti);
                }
                break;
            case 0:
                std::cout << "Keluar dari menu admin.\n";
                break;
            default:
                std::cout << "Pilihan tidak valid.\n";
        }
    } while (pilihanAdmin != 0);
}

void MenuCustomer(std::vector<Roti>& daftarRoti){
    Member customer("Guest", "guest", "guest", 0, 'L'); // Member sementara untuk customer biasa
    int pilihanCustomer;
    do {
        std::cout << "\nMenu Customer:\n"
                  << "1. Lihat Daftar Roti\n"
                  << "2. Beli Roti\n"
                  << "3. Cek Saldo\n"
                  << "4. Top Up Saldo\n"
                  << "5. Lihat Detail Pembelian Roti\n"
                  << "0. Keluar\n"
                  << "Pilih (0-5): ";
        std::cin >> pilihanCustomer;
        std::cin.ignore(); 
        switch (pilihanCustomer) {
            case 1:
                tampilkanroti(daftarRoti);
                break;
            case 2:
                MemberBeliRoti(daftarRoti, customer);
                break;
            case 3:
                std::cout << "Saldo Anda: " << customer.getSaldo() << "\n";
                break;
            case 4:
                {
                    double jumlahTopUp;
                    std::cout << "Masukkan jumlah saldo yang ingin di-top up: ";
                    std::cin >> jumlahTopUp;
                    std::cin.ignore(); 
                    customer.tambahsaldo(jumlahTopUp);
                    std::cout << "Top up saldo berhasil! Saldo baru Anda: "  << customer.getSaldo()  << "\n";
                }
                break;
            case 5:
                customer.tampilkandetailpembelian();
                break;
            case 0:
                std::cout << "Berhasil keluar dari menu customer.\n";
                break;
            default:
                std::cout << "Pilihan tidak valid.\n";
        }
    } while (pilihanCustomer != 0);
}

void MenuMember(std::vector<Roti>& daftarRoti, Member& currentUser){
    int pilihanMember;
    do {
        std::cout << "\nMenu Member:\n"
                  << "1. Lihat Daftar Roti\n"
                  << "2. Beli Roti\n"
                  << "3. Cek Saldo\n"
                  << "4. Top Up Saldo\n"
                  << "5. Lihat Detail Pembelian Roti\n"
                  << "0. Keluar\nPilih: ";
        std::cin >> pilihanMember;
        std::cin.ignore(); 
        switch (pilihanMember) {
            case 1:
                tampilkanroti(daftarRoti);
                break;
            case 2:
                MemberBeliRoti(daftarRoti, currentUser);
                break;
            case 3:
                std::cout << "Saldo Anda: " << currentUser.getSaldo() << "\n";
                break;
            case 4:
                {
                    double jumlahTopUp;
                    std::cout << "Masukkan jumlah saldo yang ingin di-top up: ";
                    std::cin >> jumlahTopUp;
                    std::cin.ignore(); 
                    currentUser.tambahsaldo(jumlahTopUp);
                    std::cout << "Top up saldo berhasil! Saldo baru Anda: " << currentUser.getSaldo() << "\n";
                }
                break;
            case 5:
                currentUser.tampilkandetailpembelian();
                break;
            case 0:
                std::cout << "Keluar dari menu member.\n";
                break;
            default:
                std::cout << "Pilihan tidak valid.\n";
        }
    } while (pilihanMember != 0);
}

int main() {
    std::vector<Roti> daftarRoti;
    int pilihan;
    admin dm;
    do{
        std::cout << "~~Selamat datang di Toko Roti Mr. Farhan!~~\n" 
                  << "silahkan pilih salah satu di bawah ini! \n"
                  << "0. Keluar \n"
                  << "1. Saya sebagai Admin\n"
                  << "2. Saya sebagai Customer\n"
                  << "Silahkan pilih (0-2): ";
        std::cin >> pilihan;
        std::cin.ignore(); 
        switch (pilihan){
            case 1:
                {
                    std::string user, pass;
                    std::cout << "Masukkan username admin: ";
                    std::getline(std::cin, user);
                    std::cout << "Masukkan password admin: ";
                    std::getline(std::cin, pass);
                    if (dm.login(user, pass)){
                        std::cout << "Login berhasil. Selamat datang, Admin " << user << "!\n";
                        MenuAdmin(dm, daftarRoti);
                    } else {
                        std::cout << "Username atau password salah. Akses ditolak.\n";
                    }
                }
                break;
            case 2:
                {
                    std::cout << "Apakah Anda memiliki member? (y/n): ";
                    char isMember;
                    std::cin >> isMember;
                    std::cin.ignore(); 
                    if (isMember == 'y' || isMember == 'Y') {
                        std::string username, password;
                        std::cout << "Masukkan username: ";
                        std::getline(std::cin, username);
                        std::cout << "Masukkan password: ";
                        std::getline(std::cin, password);
                        auto it = dm.daftarMember.find(username);
                        if (it != dm.daftarMember.end() && it->second.verifyPassword(password)) {
                            Member& currentUser = it->second;
                            std::cout << "Login berhasil. Selamat datang, " << username << "!\n";
                            MenuMember(daftarRoti, currentUser);
                        } else {
                            std::cout << "Username atau password salah.\n";
                        }
                    } else {
                        char konfdaftar;
                        std::cout << "Apakah anda ingin mendaftar menjadi member? (y/n)";
                        std::cin >> konfdaftar;
                        std::cin.ignore();
                        if (konfdaftar == 'y' || konfdaftar == 'Y') {
                            std::string nama, username, password;
                            int umur;
                            char kelamin;
                            std::cout << "Masukkan nama lengkap: ";
                            std::getline(std::cin, nama);
                            std::cout << "Masukkan username: ";
                            std::getline(std::cin, username);
                            if (dm.daftarMember.find(username) != dm.daftarMember.end()) {
                                std::cout << "Username sudah terdaftar. Silahkan coba username lain.\n";
                                break;
                            }
                            std::cout << "Masukkan password: ";
                            std::getline(std::cin, password);
                            std::cout << "Masukkan umur: ";
                            std::cin >> umur;
                            std::cin.ignore(); 
                            std::cout << "Masukkan kelamin (L/P): ";
                            std::cin >> kelamin;
                            std::cin.ignore(); 
                            Member newMember(nama, username, password, umur, kelamin);
                            dm.daftarMember[username] = newMember;
                            std::cout << "Pendaftaran member berhasil! Silahkan login kembali.\n";
                            break;
                        }
                        MenuCustomer(daftarRoti);
                    }
                }
                break;
            case 0:
                std::cout << "Terima kasih sudah datang!.\n";
                break;
            default:
                std::cout << "Pilihan tidak valid.\n";
        }
    }while (pilihan != 0);
}
