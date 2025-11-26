#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "Member.h"
#include "IsiAdmin.h"

void admin::lihatMember(const std::map<std::string, Member>& daftarMember) {
// fungsi untuk melihat daftar member, untuk admin
    std::cout << "Daftar Member:\n";
    for (const auto& pair : daftarMember) {
        const Member& member = pair.second;
        std::cout << "Nama: " << member.getnama() << ", Umur :" << member.umur << ", Kelamin: " << member.kelamin << ", Roti Dibeli: " << member.getRotiDibeli() << std::endl;
    }
}

void admin::keuntungan(const std::vector<Roti>& daftarRoti) {
    std::cout << "Keuntungan masing-masing roti:\n";
    for (const auto& roti : daftarRoti) {
        std::cout << "Roti: " << roti.nama <<", Keuntungan per-roti: " << roti.keuntungan <<", Roti Terjual: "<< roti.terjual << ", Keuntungan: " << roti.keuntungan * roti.terjual << std::endl;
    }
    std::cout << "Total Keuntungan: ";
    int total = 0;
    for (const auto& roti : daftarRoti) {
        total += roti.keuntungan * roti.terjual;
    }
    std::cout << total << std::endl;
}

void admin::hapusMember(const std::string& username) {
// fungsi untuk menghapus member, untuk admin
    lihatMember(daftarMember); 
    auto it = daftarMember.find(username);
    if (it != daftarMember.end()) {
        daftarMember.erase(it);
        std::cout << "Member dengan username " << username << " berhasil dihapus.\n";
    } else {
        std::cout << "Member dengan username " << username << " tidak ditemukan.\n";
    }
}

void admin::tambahRoti(std::vector<Roti>& daftarRoti) {
// fungsi untuk menambah roti, untuk admin
    Roti rotiBaru;
    std::cout << "Masukkan nama roti: ";
    std::getline(std::cin, rotiBaru.nama);
    std::cout << "Masukkan harga roti: ";
    std::cin >> rotiBaru.harga;
    std::cout << "Masukkan stok roti: ";
    std::cin >> rotiBaru.stok;
    std::cout << "Masukkan keuntungan per roti: ";
    std::cin >> rotiBaru.keuntungan;
    rotiBaru.terjual = 0; 
    daftarRoti.push_back(rotiBaru);
    std::cin.ignore(); 
    std::cout << "Roti " << rotiBaru.nama << " berhasil ditambahkan ke daftar.\n";
}

void admin::tambahStok(std::vector<Roti>& daftarRoti) {
    std::string namaRoti;
    int tambahanStok;
    tampilkanroti(daftarRoti);
    std::cout << "Masukkan nama roti yang stoknya ingin ditambah: ";
    std::getline(std::cin, namaRoti);
    std::cout << "Masukkan jumlah stok yang ingin ditambahkan: ";
    std::cin >> tambahanStok;
    std::cin.ignore(); 
    for (auto& roti : daftarRoti) {
        if (roti.nama == namaRoti) {
            roti.stok += tambahanStok;
            std::cout << "Stok roti " << namaRoti << " berhasil ditambahkan. Stok sekarang: " << roti.stok << "\n";
            return;
        }
    }
    std::cout << "Roti dengan nama tersebut tidak ditemukan.\n";
}

void admin::hapusroti(std::vector<Roti>& daftarRoti) {
// fungsi untuk menghapus roti, untuk admin
    std::string namaRoti;
    tampilkanroti(daftarRoti);
    std::cout << "Masukkan nama roti yang ingin dihapus: ";
    std::getline(std::cin, namaRoti);
    for (auto it = daftarRoti.begin(); it != daftarRoti.end(); ++it) {
        if (it->nama == namaRoti) {
            daftarRoti.erase(it);
            std::cout << "Roti " << namaRoti << " berhasil dihapus dari daftar.\n";
            return;
        }
    }
    std::cout << "Roti dengan nama tersebut tidak ditemukan.\n";
    
}

void admin::kurangistok(const std::string& namaRoti, int jumlah, std::vector<Roti>& daftarRoti) {
    for (auto& roti : daftarRoti) {
        if (roti.nama == namaRoti) {
            if (roti.stok >= jumlah) {
                roti.stok -= jumlah;
                std::cout << "Stok roti " << namaRoti << " berhasil dikurangi. Stok sekarang: " << roti.stok << "\n";
            } else {
                std::cout << "Stok roti tidak mencukupi untuk pengurangan.\n";
            }
            return;
        }
    }
    std::cout << "Roti dengan nama tersebut tidak ditemukan.\n";
}
