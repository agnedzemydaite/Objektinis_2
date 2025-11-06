#include "studentai.h"
#include "balu_vardu_meniu_ivestys.h"

using std::cout;
using std::endl;
using std::to_string;
using std::cin;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;
using std::chrono::duration_cast;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;


//Ivestis
void studentas::ivest_su_n(){
    
    int laik_paz;
    paz_.clear();
    
    suma_ = 0; n_ = 0;
    cout << "Iveskite studento duomenis" << endl;
    cout << "Vardas: "; var_ = vardo_iv();
    cout << "Pavarde: "; pav_ = vardo_iv();
    cout << "Kiek pazymiu turi studentas: " << var_ << " " << pav_ << ": ";
    n_ = n_iv("Kiek pazymiu turi studentas:");
    
    if(n_ != 0) cout << "Iveskite studento pazymius: " << endl;
    
    for(int i = 0; i < n_; i++)
    {
        cout << i+1 << " "; laik_paz = skaiciu_iv(to_string(i+1));
        paz_.push_back(laik_paz);
        suma_ += laik_paz;
    }
    
    cout << "Iveskite egzamino pazymi: "; egz_ = skaiciu_iv("Iveskite egzamino pazymi:");
    vidurkis();
    mediana();
}


void studentas::ivest_be_n(){
    
    n_ = 0; suma_ = 0;
    paz_.clear();
    int pazymys;
    string laik_paz;
    cout << "Iveskite studento duomenis" << endl;
    cout << "Vardas: "; var_ = vardo_iv();
    cout << "Pavarde: "; pav_ = vardo_iv();
    cout << "Iveskite studento pazymius: " << endl;
    
    while(true){
        cout << n_ + 1 << " ";
        getline(cin, laik_paz);
        if(laik_paz.empty()) break;
        
        else{
            bool neskaicius = false;
            for(char ch : laik_paz){
                if(!isdigit(ch)){
                    neskaicius = true;
                    break;
                }
            }
            
            if(neskaicius == true){
                cout << "Padarete klaida, bandykite is naujo " << endl;
                continue;
            }
            
            pazymys = stoi(laik_paz);
            if( pazymys == 0 || pazymys > 10){
                cout << "Padarete klaida, bandykite is naujo " << endl;
                continue;
            }
            paz_.push_back(pazymys);
            n_++;
            suma_ += pazymys;
            
        }
    }
    cout << "Iveskite egzamino pazymi: "; egz_ = skaiciu_iv("Iveskite egzamino pazymi:");
    vidurkis();
    mediana();
}

void studentas::rando(){
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> kiek_dist(0,20);
    uniform_int_distribution<int> paz_dist(1,10);
    
    n_ = 0; suma_ = 0;
    paz_.clear();
    int laik_paz;
    cout << "Iveskite studento duomenis" << endl;
    cout << "Vardas: "; var_ = vardo_iv();
    cout << "Pavarde: "; pav_ = vardo_iv();
    n_ =  kiek_dist(mt);
    for(int i = 0; i < n_; i++){
        laik_paz = paz_dist(mt);
        paz_.push_back(laik_paz);
        suma_ += laik_paz;
    }
    egz_ = paz_dist(mt);
    vidurkis();
    mediana();
}
bool studentas::failas(string vardas, string pavarde, string line){
    var_ = vardas;
    pav_ = pavarde;
    paz_.clear();
    egz_ = 0;
    gal_vid_ = 0;
    gal_med_ = 0;
    
    int sk = 0, n = 0, sum = 0;
    bool klaida = false;
    
    for (char c: line) {
        if (isdigit(c)) {
            if (!klaida) sk = sk * 10 + (c - '0');
        } else if (isalpha(c)) {
            klaida = true;
        } else {
            if (sk != 0 && !klaida) {
                if (sk >= 1 && sk <= 10) {
                    paz_.push_back(sk);
                    sum += sk;
                    n++;
                }
                else {
                    std::cout << "Eiluteje pazymys nera intervale 1-10. Si skaiciu praleisime." << std::endl;
                }
            }
            sk = 0;
            klaida = false;
        }
    }
    if (sk != 0 && !klaida) {
                if (sk >= 1 && sk <= 10) {
                    paz_.push_back(sk);
                    sum += sk;
                    n++;
                }
            }

            if (!paz_.empty()) {
                egz_ = paz_.back();
                paz_.pop_back();
                n--;
                sum -= egz_;
            }
    n_ = n;
    suma_ = sum;
    vidurkis();
    mediana();
    return !paz_.empty() || egz_ != 0;
}

    
//Galutinis balas
void studentas::vidurkis(){
    if( n_ == 0){
        gal_vid_ = egz_;
    }
    else{
        gal_vid_ =  double(suma_)/double(n_)*0.4 + egz_*0.6;
    }
}
void studentas::mediana(){
    if(n_ == 0){
        gal_med_ =  egz_;
    }
    else{
        vector <int> isrikiuoti_paz = paz_;
        sort(isrikiuoti_paz.begin(), isrikiuoti_paz.end());
        double med = 0;
        if (n_ % 2 == 0) {
            med = (isrikiuoti_paz[n_/2 - 1] + isrikiuoti_paz[n_/2]) / 2.0;
        }
        else {
            med = isrikiuoti_paz[n_/2];
        }
        gal_med_ = med*0.4+egz_*0.6;
    }
}
