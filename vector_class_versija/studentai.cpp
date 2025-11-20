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

using std::left;
using std::right;
using std::setw;
using std::fixed;
using std::setprecision;

using std::cerr;
using std::ifstream;
using std::ofstream;

//Operatoriu rezimai
ivestis_rezimas ivestis = ivestis_rezimas::rankinis;
isvesties_rezimas isvestis = isvesties_rezimas::abu;

//Operatoriai
istream& operator>>(istream& is, studentas& s){
    s.paz_.clear();
    s.suma_ = 0;
    bool pasirinkimas1 = (ivestis == ivestis_rezimas::generuojamas);
    bool pasirinkimas2 = (&is == &cin && ivestis == ivestis_rezimas::rankinis);
    
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> kiek_dist(0,20);
    uniform_int_distribution<int> paz_dist(1,10);
    
    int paz;
    if(&is == &cin) cout << "Vardas: ";
    is >> s.var_;
    if(&is == &cin) cout << "Pavarde: ";
    is >> s.pav_;
    
    if(pasirinkimas2) cout << "Iveskite pazymiu skaiciu: ";
    if(pasirinkimas1) s.n_ = kiek_dist(mt);
    else s.n_ = s.patikrinimas_n(is);
    for(int i = 0; i < s.n_; i++){
        if(pasirinkimas2) cout << i+1 << " ";
        if(pasirinkimas1) paz = paz_dist(mt);
        else paz = s.patikrinimas_paz(is);
        s.paz_.push_back(paz);
        s.suma_ += paz;
    }
    if(pasirinkimas2) cout << "Iveskite egzamino pazymi: ";
    if(pasirinkimas1) s.egz_ = paz_dist(mt);
    else s.egz_ = s.patikrinimas_paz(is);
    
    s.vidurkis();
    s.mediana();
    return is;
}
ostream& operator<<(ostream& os, const studentas& s){
    bool vid = (isvestis == isvesties_rezimas::vidurkis);
    bool med = (isvestis == isvesties_rezimas::mediana);
    bool abu = (isvestis == isvesties_rezimas::abu);
    
    os << left << setw(15) << s.var_ << setw(20) << s.pav_;
    if(vid) os << setw(17) << fixed << setprecision(2) << s.gal_vid_ << endl;
    if(med) os << setw(17) << fixed << setprecision(2) << s.gal_med_ << endl;
    if(abu) os << setw(17) << fixed << setprecision(2) << s.gal_vid_ << setw(17) << fixed << setprecision(2) << s.gal_med_ << endl;
    return os;
}

//Tikrinimas ar geras skaicius
int studentas::patikrinimas_n(istream& is){
    string x;

    while(true){
        is >> x;
        bool visas_skaicius = all_of(x.begin(), x.end(), ::isdigit);
        if(!visas_skaicius){
            if(&is == &cin){
                cout << "Padarėte klaidą, bandykite iš naujo: ";
            }
            else{
                cerr << "Ivestas netinkamas pazymys (" << x << "), praleidziam.\n";
                continue;
            }
        }
        else{
            return stoi(x);
        }
    }
}
int studentas::patikrinimas_paz(istream& is){
    string x;
    
    while(true){
        if(!(is >> x)) return 0;
        
        bool visas_skaicius = all_of(x.begin(), x.end(), ::isdigit);
        if(!visas_skaicius){
            if(&is == &cin){
                cout << "Padarėte klaidą, bandykite iš naujo: ";
            }
            else{
                cerr << "Įvestas netinkamas pažymys (" << x << "), praleidžiam.\n";
            }
            continue;
        }
        int sk = stoi(x);
        if (sk < 1 || sk > 10){
            if (&is == &cin) {
                cout << "Padarėte klaidą, bandykite iš naujo: ";
                continue;
            } else {
                cerr << "Įvestas netinkamas pažymys (" << x << "), praleidžiame.\n";
                continue;
            }
        }

        return sk;
        
    }
}

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

//Rule of three
void rule_of_three(){
    studentas s1;
    studentas s2;
    cout << "Iveskite vieno studento duomenis: " << endl;
    cin >> s1;
    ifstream fin("stud.txt");
    fin >> s2;
    fin.close();
    ofstream fout("Rule_of_Three.txt");
    
    fout << setw(3) << left << "Nr" << setw(16) << left << "Vieta atmintyje"<< setw(15) << left << "Vardas" << setw(20) << left << "Pavarde" << setw(17) << left << "Galutinis (Vid.)" << setw(17) << left << "Galutinis (Med.)"  <<endl;
    fout  <<setw(3) << left << "s1" << setw(16) << left << &s1 << s1;
    fout << setw(3) << left << "s2" << setw(16) << left << &s2 << s2;

    fout << endl << "Pakeiciame studenta s2 i s1 (s2 = s1)." << endl;
    s2 = s1;
    fout << setw(3) << left << "Nr" << setw(16) << left << "Vieta atmintyje"<< setw(15) << left << "Vardas" << setw(20) << left << "Pavarde" << setw(17) << left << "Galutinis (Vid.)" << setw(17) << left << "Galutinis (Med.)"  <<endl;
    fout  <<setw(3) << left << "s1" << setw(16) << left << &s1 << s1;
    fout << setw(3) << left << "s2" << setw(16) << left << &s2 << s2;
    
    fout << endl << "Sukuriam nauja studenta s3 is s1  (s3(s1))." << endl;
    studentas s3(s1);
    fout << setw(3) << left << "Nr" << setw(16) << left << "Vieta atmintyje"<< setw(15) << left << "Vardas" << setw(20) << left << "Pavarde" << setw(17) << left << "Galutinis (Vid.)" << setw(17) << left << "Galutinis (Med.)"  <<endl;
    fout  <<setw(3) << left << "s1" << setw(16) << left << &s1 << s1;
    fout << setw(3) << left << "s3" << setw(16) << left << &s3 << s3;
    fout.close();
    cout << "Testo rezultatai ivesti i faila 'Rule_of_Three'" << endl;
}
