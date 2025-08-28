/* --- pimpl.h --- */

/* ------------------------------------------
Author: Huqianqian
Date: 7/25/2025
------------------------------------------ */

#ifndef PIMPL_H
#define PIMPL_H

#include <memory>
#include <iostream>
using namespace std;

class pimpl_impl;

class pimpl {
public:
    pimpl(int data);
    ~pimpl();

    void show();

private:
    unique_ptr<pimpl_impl> _pimpl_impl;
};

#endif // PIMPL_H
