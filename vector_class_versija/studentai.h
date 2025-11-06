#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <random>

using std::string;
using std::vector;
using std::istream;

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
    studentas() : egz_(0), n_(0), suma_(0), gal_med_(0), gal_vid_(0) { }
    // Reiksmiu gavimas
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
    
    //Skaiciavimai
    void vidurkis();
    void mediana();
    
    ~studentas() { }
};

