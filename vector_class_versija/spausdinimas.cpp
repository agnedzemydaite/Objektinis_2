#include "spausdinimas.h"

using std::vector;
using std::string;
using std::cout;
using std::setw;
using std::left;
using std::right;
using std::fixed;
using std::setprecision;
using std::endl;
using std::ofstream;
using std::ostringstream;
using std::ios;
using std::to_string;

void spausdinimas(vector<studentas> & studentai, int pasirinkimas){
    cout << setw(15) << left << "Vardas" << setw(20) << left << "Pavarde";

    if (pasirinkimas == 1) {
        cout << setw(17) << left << "Galutinis (Vid.)" << endl;
        for(int i = 0; i < 51; i++) cout << "-";
        cout << endl;
        for(auto s:studentai){
            cout << setw(15) << left << s.vardas() << setw(20) << left << s.pavarde();
            cout << fixed << setprecision(2) << setw(17) << s.gal_vid() << endl;
        }
    }
    else if (pasirinkimas == 2) {
        cout << setw(17) << left << "Galutinis (Med.)" << endl;
        for(int i = 0; i < 51; i++) cout << "-";
        cout << endl;
        for(auto s:studentai){
            cout << setw(15) << left <<s.vardas() << setw(20) << left << s.pavarde();
            cout << fixed << setprecision(2) << setw(17) << s.gal_med() << endl;
        }
    }
    else if (pasirinkimas == 3) {
        cout << setw(17) << left << "Galutinis (Vid.) " << setw(17) << left << "Galutinis (Med.)" << endl;
        for(int i = 0; i < 69; i++) cout << "-";
        cout << endl;
        for(auto s:studentai){
            cout << setw(15) << left << s.vardas() << setw(20) << left << s.pavarde();
            cout << fixed << setprecision(2) << setw(17) << s.gal_vid() << setw(17) << s.gal_med() << endl;
        }
    }
}

void spausd_f(vector<studentas> studentai, string pav, int pasirinkimas) {
    int w = static_cast<int>(studentai.size());
    int n = to_string(w).length();
    
    pav = pav + ".txt";
    ofstream fout(pav, ios::out | ios::binary);
    ostringstream antraste;
    antraste << setw(n + 8) << left << "Vardas"
             << setw(n + 8) << left << "Pavarde";
    if(pasirinkimas == 1){
        antraste << setw(17) << left << "Galutinis (Vid.)" << "\n";
    }
    else if(pasirinkimas == 2){
        antraste << setw(17) << left << "Galutinis (Med.)" << "\n";
    }
    else if(pasirinkimas == 3){
        antraste << setw(17) << left << "Galutinis (Vid.) " << setw(17) << left << "Galutinis (Med.)" << "\n";
    }
    string buffer = antraste.str();
    buffer.reserve(10000000);
    
    ostringstream oss;
    for (const auto& s: studentai) {
        oss.str(""); // clear content
        oss.clear();
        oss << setw(n+8) << left << s.vardas() << setw(n+8) << left << s.pavarde();
        buffer += oss.str();

        if (pasirinkimas == 1) {
            oss.str(""); // clear content
            oss.clear();
            oss << setw(17) << left << fixed << setprecision(2) << s.gal_vid();
            buffer += oss.str() + "\n";
        }
        else if (pasirinkimas == 2) {
            oss.str(""); // clear content
            oss.clear();
            oss << setw(17) << left << fixed << setprecision(2) << s.gal_med();
            buffer += oss.str() + "\n";
        }
        else if (pasirinkimas == 3) {
            oss.str("");
            oss.clear();
            oss << setw(17) << left << fixed << setprecision(2) << s.gal_vid();
            string vid = oss.str();

            oss.str("");
            oss.clear();
            oss << setw(17) << left << fixed << setprecision(2) << s.gal_med();
            string med = oss.str();

            buffer += vid + med + "\n";
        }
    }

    if (!buffer.empty()) {
        fout.write(buffer.data(), buffer.size());
    }
}

void vieta_atmintyje(vector <studentas> studentai){
    cout << setw(15) << left << "Vardas" << setw(20) << left << "Pavarde" << setw(16) << left << "Vieta atmintyje" << endl;
    for(int i = 0; i < 51; i++) cout << "-";
    cout << endl;
    for(auto &s: studentai){
        cout <<setw(15) << left << s.vardas() << setw(20) << left << s.pavarde() << setw(16) << left << &s << endl;

    }
    cout << endl;
}
