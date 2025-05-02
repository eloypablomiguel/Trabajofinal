// claxon.h
#ifndef CLAXON_H
#define CLAXON_H

#include <iostream>

class Claxon {
public:
    virtual ~Claxon() = default;
    virtual void tocarClaxon() const {
        std::cout << "Piii piiii, que ya esta verde!" << std::endl;
    }
};

#endif // CLAXON_H
