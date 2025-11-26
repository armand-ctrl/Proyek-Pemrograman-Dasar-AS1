#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "Member.h"
#include "roti.h"

void Member::tampilkandetailpembelian() const {
// fungsi untuk menampilkan inventory member, untuk member
    if (detailPembelian.empty()) {
        std::cout << "Anda belum melakukan pembelian roti.\n";
        return;
    }
    std::cout << "Detail Pembelian Roti:\n";
    for (const auto& pair : detailPembelian) {
        std::cout << "Roti: " << pair.first << ", Jumlah: " << pair.second << std::endl;
    }
}

