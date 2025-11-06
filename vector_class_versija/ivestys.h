#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>

#include "studentai.h"
#include "balu_vardu_meniu_ivestys.h"

void ivest_f(vector <studentas> & studentai, int & stud_n, string & pav, double & testavimas);
void stud_iv(vector <studentas> & studentai, int & n, studentas (*funkc)());

