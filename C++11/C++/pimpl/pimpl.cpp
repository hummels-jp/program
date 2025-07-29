/* --- pimpl.cpp --- */

/* ------------------------------------------
author: Huqianqian
date: 7/25/2025
------------------------------------------ */

#include "pimpl.h"

class pimpl_impl
{
public:
    pimpl_impl(int data): _data(data)
    {

    }

    ~pimpl_impl()
    {

    }

    void show() const
    {
        cout << "pimpl_impl " << _data << endl;
    }
private:
    int _data;
};

pimpl::pimpl(int data):_pimpl_impl(make_unique<pimpl_impl>(data)) 
{
    // Constructor
}

pimpl::~pimpl() {
    // Destructor
}

// show 
void pimpl::show()
{
    _pimpl_impl->show();
}
