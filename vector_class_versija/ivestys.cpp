#include "ivestys.h"

using std::string;
using std::vector;
using std::function;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::to_string;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;
using std::chrono::duration_cast;
using std::istringstream;

void ivest_f(vector <studentas> & studentai, int & stud_n, string & pav, double & testavimas){
    testavimas = 0;
    pav = "";
    ifstream fin;
    
    while(true){
        cout << "Iveskite failo pavadinima: ";
        getline(cin, pav);
        
        fin.open(pav);
        if(!fin) {
            cout << "Nepavyko atidaryti failo. Bandykite dar karta." << endl;
            fin.clear();
        }
        else break;
    }
    
    auto start = high_resolution_clock::now();
    string line;
    getline(fin, line);
    
    stud_n = 0;
    
    studentai.clear();
    studentai.reserve(1000);
    
    string vardas, pavarde, eilute;
    while (fin >> vardas >> pavarde) {
        studentas s;
        getline(fin, eilute);
        
        if(s.failas(vardas, pavarde, eilute)) {
            studentai.push_back(s);
            stud_n++;
        }
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    testavimas = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Failo nuskaitymas uztruko: " << testavimas << " ms" << std::endl;
    
    fin.close();
    
}

void stud_iv(vector <studentas> & studentai, int & n, studentas (*funkc)()){
    cout << "Kiek studentu grupeje? "; n = n_iv("Kiek studentu grupeje?");
    for(auto i = 0; i < n; i++){
        studentai.push_back(funkc());
    }
}



