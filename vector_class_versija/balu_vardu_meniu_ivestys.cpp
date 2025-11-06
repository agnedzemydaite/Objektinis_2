#include "balu_vardu_meniu_ivestys.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

int skaiciu_iv(string i){
    string x;
    bool tiesa = true;
    while(true){
        tiesa = true;
        getline(cin, x);
        if(x.empty()){
            cout << "Padarete klaida, bandykite is naujo" << endl;
            cout << i << " ";
            continue;
        }
        for(char ch : x){
            if(!isdigit(ch)){
                tiesa = false;
                cout << "Padarete klaida, bandykite is naujo" << endl;
                cout << i << " ";
                break;
            }
        }
        if(tiesa != false && (stoi(x) <= 0 || stoi(x) > 10)){
            cout << "Padarete klaida, bandykite is naujo" << endl;
            cout << i << " ";
            continue;
        }
        if(tiesa) return stoi(x);
    }
}

int n_iv(string i){
    string x;
    bool tiesa = true;
    while(true){
        tiesa = true;
        getline(cin, x);
        if(x.empty()){
            cout << "Padarete klaida, bandykite is naujo " << endl;
            cout << i;
            continue;
        }
        for(char ch : x){
            if(!isdigit(ch)){
                tiesa = false;
                cout << "Padarete klaida, bandykite is naujo" << endl;
                cout << i << " ";
                break;
            }
        }
        if(tiesa) return stoi(x);
        
    }
}

string vardo_iv(){
    string x;
    while(true){
        getline(cin, x);
        if(!x.empty()){
            return x;
        }
        cout << "Ivedimas negali buti tuscias, bandykite is naujo: ";
    }
}

int pasirink_iv(int min_r, int max_r){
    string x;
    int pasirinkimas;
    
    while(true){
        getline(cin, x);
        
        if(!arskaicius(x) || x.empty()){
            cout << "Padarete klaida, bandykite is naujo" << endl;
            continue;
        }
        
        pasirinkimas = stoi(x);
        
        if(pasirinkimas <min_r || pasirinkimas > max_r){
            cout << "Padarete klaida, bandykite is naujo" << endl;
            continue;
        }
        
        return pasirinkimas;
    }
}
