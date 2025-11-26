#ifndef ISIADMIN_H
#define ISIADMIN_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Member.h"
#include "roti.h"

class admin{
    private:
        std::string username = "armandkun";
        std::string password = "armand123";
    public:
        std::map<std::string, Member> daftarMember;

        bool login(const std::string& user, const std::string& pass) {
            return (user == username && pass == password);}
        
        void lihatMember(const std::map<std::string, Member>& daftarMember);
        
        void keuntungan(const std::vector<Roti>& daftarRoti);
        
        void tambahRoti(std::vector<Roti>& daftarRoti);

        void tambahStok(std::vector<Roti>& daftarRoti);

        void hapusroti(std::vector<Roti>& daftarRoti);

        void hapusMember(const std::string& username);

        void kurangistok(const std::string& namaRoti, int jumlah, std::vector<Roti>& daftarRoti);
};

inline void tampilkanroti(const std::vector<Roti>& daftarRoti){
    std::cout << "Roti yang tersedia:\n";
    for (const auto& roti : daftarRoti) {
        std::cout << "Nama: " << roti.nama << ", Harga: " << roti.harga << ", Stok: " << roti.stok << std::endl;  
    }
}

#endif