#ifndef VEHICULO_H
#define VEHICULO_H

#include "claxon.h"
#include <QLabel>
#include <QPixmap>
#include <QString>

class VehiculoBase {
public:
    VehiculoBase(QLabel *lbl, const QString &rutaImagen, int ancho = 100, int alto = 100);
    virtual ~VehiculoBase() {
        delete claxon;
    }

    virtual void mover(int x, int y);
    virtual void escalar(int ancho, int alto);
    virtual void ocultar();
    virtual void mostrar();

    void hacerSonarClaxon() const{
        if (claxon) claxon->tocarClaxon();
    }

    QLabel *label;

protected:
    QPixmap imagenOriginal;
    Claxon* claxon;
};

class Coche : public VehiculoBase, public Claxon{
public:
    Coche(QLabel *lbl, const QString &rutaImagen, int ancho = 100, int alto = 100)
        : VehiculoBase(lbl, rutaImagen, ancho, alto) {}

    void mover(int x, int y) override;

};

class Camion : public VehiculoBase {
public:
    Camion(QLabel *lbl, const QString &rutaImagen, int ancho = 100, int alto = 100)
        : VehiculoBase(lbl, rutaImagen, ancho, alto) {}

    void mover(int x, int y) override;
};

class Peaton : public VehiculoBase {
public:
    Peaton(QLabel *lbl, const QString &rutaImagen, int ancho = 100, int alto = 100, const QString& nombre = "")
        : VehiculoBase(lbl, rutaImagen, ancho, alto), cruzando(false), nombre(nombre) {}

    void mover(int x, int y) override; //{
        //VehiculoBase::mover(x, y);
    //}

    bool cruzando;  // Estado si el peatón está cruzando la calle
    int velocidad;  // Velocidad de movimiento del peatón
    QString nombre;  // NUEVO: Para identificar al peatón
};

#endif // VEHICULO_H
