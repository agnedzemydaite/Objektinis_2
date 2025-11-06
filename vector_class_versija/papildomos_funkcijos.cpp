#include "papildomos_funkcijos.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;


bool arskaicius(string i){
    for(char ch : i){
        if(!isdigit(ch)) return false;
    }
    return true;
}

void rikiavimas(vector<studentas> & studentai, int pasirinkimas){
    if(pasirinkimas == 1){
        sort(studentai.begin(), studentai.end(), [](const studentas &a, const studentas &b){
                return a.vardas() < b.vardas();
            });
    }
    else if(pasirinkimas == 2){
        sort(studentai.begin(), studentai.end(), [](const studentas &a, const studentas &b){
                return a.pavarde() < b.pavarde();
            });
    }
    else if(pasirinkimas == 3){
        sort(studentai.begin(), studentai.end(), [](const studentas &a, const studentas &b){
                return a.gal_vid() < b.gal_vid();
            });
    }
    else if(pasirinkimas == 4){
        sort(studentai.begin(), studentai.end(), [](const studentas &a, const studentas &b){
                return a.gal_med() < b.gal_med();
            });
    }
}

void rusiavimas_strat1(vector <studentas> & studentai, vector <studentas> & vargsai, vector <studentas> & kieti, int & pasirinkimas){
    if(pasirinkimas == 1){
        for(const auto& s:studentai){
            if(s.gal_vid() < 5.0){
                vargsai.push_back(s);
            }
            else{
                kieti.push_back(s);
            }
        }
    }
    else if(pasirinkimas == 2){
        for(const auto& s:studentai){
            if(s.gal_med() < 5.0){
                vargsai.push_back(s);
            }
            else{
                kieti.push_back(s);
            }
        }
    }
}
void rusiavimas_strat2(vector <studentas> & studentai, vector <studentas> & vargsai, int & pasirinkimas){
    if(pasirinkimas == 1){
        sort(studentai.begin(), studentai.end(), [](const studentas &a, const studentas &b){
            return a.gal_vid() > b.gal_vid();
        });
        while(true){
            studentas s = studentai.back();
            if(s.gal_vid() < 5.0){
                vargsai.push_back(s);
                studentai.pop_back();
            }
            else break;
        }
        studentai.shrink_to_fit();
    }
    else if(pasirinkimas == 2){
        sort(studentai.begin(), studentai.end(), [](const studentas &a, const studentas &b){
            return a.gal_med() > b.gal_med();
        });
        while(true){
            studentas s = studentai.back();
            if(s.gal_med() < 5.0){
                vargsai.push_back(s);
                studentai.pop_back();
            }
            else break;
        }
        studentai.clear();
        studentai.shrink_to_fit();
        
    }
}
void rusiavimas_strat3(vector<studentas>& studentai, vector<studentas>& vargsai, vector<studentas>& kieti, int& pasirinkimas){
    
    auto partition_taskas = partition(studentai.begin(), studentai.end(),
        [pasirinkimas](const studentas& s) {
            return (pasirinkimas == 1) ? (s.gal_vid() < 5.0) : (s.gal_med() < 5.0);
        });
    
    vargsai.assign(make_move_iterator(studentai.begin()), make_move_iterator(partition_taskas));
    kieti.assign(make_move_iterator(partition_taskas), make_move_iterator(studentai.end()));
    
    studentai.clear();
    studentai.shrink_to_fit();
}
