#include "studentai.h"
#include "ivestys.h"
#include "generavimas.h"
#include "balu_vardu_meniu_ivestys.h"
#include "papildomos_funkcijos.h"
#include "spausdinimas.h"

#include <chrono>
using std::cout;
using std::endl;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;
using std::chrono::duration_cast;

int main(){
    
    //užtikrina skirtingą atsitiktinių skaičių gavimą
    srand(static_cast<unsigned int>(time(0)));
    
    int n = 0; //studentų skaičius
    int pasirinkimas = 0;
    vector <studentas> studentai;
    vector <studentas> vargsai;
    vector <studentas> kieti;
    vector <double> laikas;
    double testavimas = 0;
    string pav;
    
    cout << "--------------------------------------------------" << endl;
    cout << "---------- Ar norite sugeneruoti failus ----------" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "1. Taip." << endl;
    cout << "2. Ne." << endl;
    cout << "--------------------------------------------------" << endl;
    cout << endl << "Iveskite savo pasirinkima: ";
    pasirinkimas = pasirink_iv(1, 2);
    if(pasirinkimas == 1){
        for(int i = 1000; i <= 10000000; i*=10){
            auto start = high_resolution_clock::now();
            failu_gener(i);
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(end - start).count();
            cout << i << ".txt failo sukurimas uztruko: " << duration << " ms" << endl;
            laikas.push_back(duration);
        }
    }
 
    //Pagrindinis meniu
    pasirinkimas = 0;
    cout << "----------------------------------------------------------" << endl;
    cout << "---------- Studentu pazymiu pasirinkimo sistema ----------" << endl;
    cout << "----------------------------------------------------------" << endl;
    cout << "1. Studentu ivedimas su zinomu namu darbu skaiciumi (n)." << endl;
    cout << "2. Studentu ivedimas su nezinomu namu darbu skaiciumu (n)." << endl;
    cout << "3. Studentu ivedimas su automatiskai sugeneruotais balais." << endl;
    cout << "4. Studentu ivedimas is failo." << endl;
    cout << "----------------------------------------------------------" << endl;
    
    cout << endl << "Iveskite savo pasirinkima: ";
    pasirinkimas = pasirink_iv(1, 4);
    
    if(pasirinkimas == 1)
        stud_iv(studentai, n, []() {
            studentas s;
            s.ivest_su_n();
            return s;
        });
    else if(pasirinkimas == 2)
        stud_iv(studentai, n, []() {
            studentas s;
            s.ivest_be_n();
            return s;
        });
    else if(pasirinkimas == 3)
        stud_iv(studentai, n, [](){
            studentas s;
            s.rando();
            return s;
        });
    else if(pasirinkimas == 4){
        ivest_f(studentai, n, pav, testavimas);
    }
    
    if(n == 0){
        cout << "Studentu skaicius lygus 0. Rezultatai negelimi" << endl;
    }
    else{
        //Vieta atmintyje
        vector <studentas> studentai_org = studentai;
        if(pasirinkimas >= 1 && pasirinkimas <=3) vieta_atmintyje(studentai);
        
        //Rusiavimo meniu
        pasirinkimas = 0;
        int pasirinkimas_3 = 0;
        cout << "----------------------------" << endl;
        cout << "-- Rusiavimo pasirinkimai --" << endl;
        cout << "----------------------------" << endl;
        cout << "1. Vidurkis." << endl;
        cout << "2. Mediana." << endl;
        cout << "----------------------------" << endl;
        cout << endl << "Iveskite savo pasirinkima: ";
        pasirinkimas = pasirink_iv(1, 2);
        
        cout << "----------------------------" << endl;
        cout << "-- Rusiavimo strategija --" << endl;
        cout << "----------------------------" << endl;
        cout << "1. Pirma (du konteineriai)." << endl;
        cout << "2. Antra (vienas konteineris)." << endl;
        cout << "3. Trecia (optimizuota pirma strategija)." << endl;
        cout << "----------------------------" << endl;
        cout << endl << "Iveskite savo pasirinkima: ";
        pasirinkimas_3 = pasirink_iv(1, 3);
        
        auto start = high_resolution_clock::now();
        
        if(pasirinkimas_3 == 1) rusiavimas_strat1(studentai, vargsai, kieti, pasirinkimas);
        else if(pasirinkimas_3 == 2) rusiavimas_strat2(studentai, vargsai, pasirinkimas);
        else if(pasirinkimas_3 == 3) rusiavimas_strat3(studentai, vargsai, kieti, pasirinkimas);
        
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start).count();
        cout << "Studentu surusiavimas uztruko: " << duration << " ms" << endl;
        testavimas += duration;
        
        //Vidurkio ir medianos pasirinkimo meniu
        pasirinkimas = 0;
        cout << "-----------------------------------------------" << endl;
        cout << "-- Galutinio balo apskaiciavimo pasirinkimai --" << endl;
        cout << "-----------------------------------------------" << endl;
        cout << "1. Vidurkis." << endl;
        cout << "2. Mediana." << endl;
        cout << "3. Vidurkis ir mediana." << endl;
        cout << "-----------------------------------------------" << endl;
        
        cout << endl << "Iveskite savo pasirinkima: ";
        pasirinkimas = pasirink_iv(1, 3);
        
        //Rikiavimo pasirinkimo meniu
        int pasirinkimas_2 = 0;
        
        cout << "----------------------------" << endl;
        cout << "-- Rikiavimo pasirinkimai --" << endl;
        cout << "----------------------------" << endl;
        cout << "1. Pagal varda." << endl;
        cout << "2. Pagal pavarde." << endl;
        cout << "3. Pagal vidurki." << endl;
        cout << "4. Pagal mediana." << endl;
        cout << "----------------------------" << endl;
        
        cout << endl << "Iveskite savo pasirinkima: ";
        pasirinkimas_2 = pasirink_iv(1, 4);
        rikiavimas(studentai, pasirinkimas_2);
        rikiavimas(vargsai, pasirinkimas_2);
        rikiavimas(kieti, pasirinkimas_2);
        
        //Spausdinimo meniu
        cout << "------------------------------" << endl;
        cout << "-- Spausdinimo pasirinkimai --" << endl;
        cout << "------------------------------" << endl;
        cout << "1. Spausdinti i ekrana." << endl;
        cout << "2. Spausdinti i faila." << endl;
        cout << "------------------------------" << endl;
        pasirinkimas_2 = 0;
        cout << endl << "Iveskite savo pasirinkima: ";
        pasirinkimas_2 = pasirink_iv(1, 2);
        
        if(pasirinkimas_2 == 1){
            cout << "VARGSIUKAI" << endl;
            spausdinimas(vargsai, pasirinkimas);
            cout << "KIETIAKAI" << endl;
            if(pasirinkimas_3 == 1 || pasirinkimas_3 == 3){
                spausdinimas(kieti, pasirinkimas);
            }
            else if(pasirinkimas_3 == 2){
                spausdinimas(studentai, pasirinkimas);
            }
        }
        else if(pasirinkimas_2 == 2){
            
            auto start = high_resolution_clock::now();
            
            if(pasirinkimas_3 == 1) spausd_f(vargsai, "vargsiukai_strat1", pasirinkimas);
            else if(pasirinkimas_3 == 2) spausd_f(vargsai, "vargsiukai_strat2", pasirinkimas);
            else if(pasirinkimas_3 == 3) spausd_f(vargsai, "vargsiukai_strat3", pasirinkimas);
            
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(end - start).count();
            cout << "vargsiuku atspausdinimas i faila uztruko: " << duration << " ms" << endl;
            testavimas = testavimas + duration;
            
            auto start1 = high_resolution_clock::now();
            
            if(pasirinkimas_3 == 1) spausd_f(kieti, "kietiakai_strat1", pasirinkimas);
            else if(pasirinkimas_3 == 2) spausd_f(kieti, "kietiakai_strat2", pasirinkimas);
            else if(pasirinkimas_3 == 3) spausd_f(kieti, "kietiakai_strat3", pasirinkimas);
            
            auto end1 = high_resolution_clock::now();
            auto duration1 = duration_cast<milliseconds>(end1 - start1).count();
            cout << "kietiaku atspausdinimas i faila uztruko: " << duration1 << " ms" << endl;
            testavimas = testavimas + duration1;

        }
        cout << endl;
        cout << "-------------------------------------------------" << endl;
        cout << "-- Ar norite, kad atspausdintu visus studentus --" << endl;
        cout << "-------------------------------------------------" << endl;
        cout << "1. Taip." << endl;
        cout << "2. Ne." << endl;
        cout << "-------------------------------------------------" << endl;
        pasirinkimas_2 = 0;
        cout << endl << "Iveskite savo pasirinkima: ";
        pasirinkimas_2 = pasirink_iv(1, 2);
        if(pasirinkimas_2 == 1){
            spausdinimas(studentai_org, pasirinkimas);
        }

    }
    cout << endl << pav << " irasu testo laikas: " << testavimas << " ms" << endl;
    
    return 0;
    
}
