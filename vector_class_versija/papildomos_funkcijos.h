#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "studentai.h"

bool arskaicius(string i);
void rikiavimas(vector<studentas> & studentai, int pasirinkimas);
void rusiavimas_strat1(vector <studentas> & studentai, vector <studentas> & vargsai, vector <studentas> & kieti, int & pasirinkimas);
void rusiavimas_strat2(vector <studentas> & studentai, vector <studentas> & vargsai, int & pasirinkimas);
void rusiavimas_strat3(vector <studentas> & studentai, vector <studentas> & vargsai, vector <studentas> & kieti, int & pasirinkimas);
