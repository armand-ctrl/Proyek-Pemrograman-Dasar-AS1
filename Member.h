#ifndef MEMBER_H
#define MEMBER_H

#include <iostream>
#include <string>
#include <map>

class Member {
private:
    std::string nama;
    std::string username;
    std::string password;
    double saldo;
public:
    int CookiesCounter = 0;
    int CookiesBonus = 0;
    int rotiDibeli;
    int umur;
    std::string kelamin;
    std::map<std::string, int> detailPembelian; // nama roti dan jumlah yang dibeli

    Member() : nama(""), username(""), password(""), umur(0), kelamin(""), saldo(0.0), rotiDibeli(0) {}

    Member(const std::string& name,const std::string& user, const std::string& pass, int usia, char gender)
    : nama(name),
      username(user),
      password(pass),
      umur(usia),
      kelamin(gender == 'L' ? "Laki-laki" : (gender == 'l'? "Laki-laki" : "Perempuan")),
      saldo(0.0),
      rotiDibeli(0){
    }    
    
    void tambahsaldo(double jumlah) {saldo += jumlah;}
    const std::string getnama() const {return nama; }
    bool login(const std::string& user, const std::string& pass) {return (user == username && pass == password);}
    const std::string& getUsername() const { return username; }
    double getSaldo() const { return saldo; }
    void kurangsaldroti(double jumlah) {saldo -= jumlah; }
    bool verifyPassword(const std::string& p) const { return password == p; }
    int getRotiDibeli() const { return rotiDibeli; }
    void tampilkandetailpembelian() const;
};

#endif