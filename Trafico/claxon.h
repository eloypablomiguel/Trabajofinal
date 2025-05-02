#ifndef CLAXON_H
#define CLAXON_H

#include <iostream>

// Clase base Claxon
class Claxon {
public:
    virtual ~Claxon() = default;
    virtual void tocarClaxon() const {
        std::cout << "Piii piiii, que ya esta verde!" << std::endl;
    }
};

// Claxon específico para coche
class ClaxonCoche : public Claxon {
public:
    void tocarClaxon() const override {
        std::cout << "Beep beep! Claxon de coche!" << std::endl;
    }
};

// Claxon específico para camión
class ClaxonCamion : public Claxon {
public:
    void tocarClaxon() const override {
        std::cout << "Hoooooooonk! Claxon de camión!" << std::endl;
    }
};

#endif // CLAXON_H
