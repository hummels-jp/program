// filepath: d:\mygit_code\program\C++11\EffectiveC++\extern\global.cpp
/* --- global.cpp --- */

/* ------------------------------------------
author: Huqianqian
date: 7/5/2025
------------------------------------------ */

#include "global.h"
#include <iostream>
using namespace std;

int global_age = 0;
string global_name = "default_name";

void print_global_info() {
    cout << "Global Age: " << global_age << endl;
    cout << "Global Name: " << global_name << endl;
}