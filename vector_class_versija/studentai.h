#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip>
#include <fstream>

using std::string;
using std::vector;
using std::istream;
using std::ostream;

class studentas {
private:
    string var_;
    string pav_;
    vector <int> paz_;
    int egz_;
    double gal_vid_;
    double gal_med_;
    int n_;
    int suma_;
    
public:
    //Default konstruktorius
    studentas() : egz_(0), n_(0), suma_(0), gal_med_(0), gal_vid_(0) { }
    
    //Reiksmiu gavimas (get'eriai)
    inline string vardas() const { return var_; }
    inline string pavarde() const { return pav_; }
    inline int egz() const { return egz_; }
    inline int n() const { return n_; }
    inline int suma() const { return suma_; }
    inline double gal_vid() const { return gal_vid_; }
    inline double gal_med() const { return gal_med_; }
    
    //Ivedimas
    void ivest_su_n();
    void ivest_be_n();
    void rando();
    bool failas(string vardas, string pavarde, string line);
    int patikrinimas_n(istream& is);
    int patikrinimas_paz(istream& is);
    
    //Skaiciavimai
    void vidurkis();
    void mediana();
    
    // Perdengti operatoriai
    friend istream& operator>>(istream& is, studentas& s);
    friend ostream& operator<<(ostream& os, const studentas& s);
    
    //RULE OF THREE
    //I. Destruktorius
    ~studentas() {
        var_.clear();
        pav_.clear();
        paz_.clear();
        gal_vid_ = 0.0;
        gal_med_ = 0.0;
        egz_ = 0;
        n_ = 0;
        suma_ = 0;
    }
    //II. Copy konstruktorius
    studentas(const studentas& kitas)
        : var_(kitas.var_),
          pav_(kitas.pav_),
          paz_(kitas.paz_),
          egz_(kitas.egz_),
          gal_vid_(kitas.gal_vid_),
          gal_med_(kitas.gal_med_),
          n_(kitas.n_),
          suma_(kitas.suma_){}
    //III. Copy Assignment
    studentas& operator=(const studentas& kitas) {
        studentas temp(kitas);
        std::swap(var_, temp.var_);
        std::swap(pav_, temp.pav_);
        std::swap(paz_, temp.paz_);
        std::swap(egz_, temp.egz_);
        std::swap(gal_vid_, temp.gal_vid_);
        std::swap(gal_med_, temp.gal_med_);
        std::swap(n_, temp.n_);
        std::swap(suma_, temp.suma_);
        return *this;
    }
};

enum class ivestis_rezimas {rankinis, generuojamas};
extern ivestis_rezimas ivestis;

enum class isvesties_rezimas {vidurkis, mediana, abu};
extern isvesties_rezimas isvestis;

void rule_of_three();
