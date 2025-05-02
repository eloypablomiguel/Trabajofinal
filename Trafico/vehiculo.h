#ifndef VEHICULO_H
#define VEHICULO_H

#include "claxon.h"
#include <QLabel>
#include <QPixmap>
#include <QString>

class VehiculoBase {
public:
    VehiculoBase(QLabel *lbl, const QString &rutaImagen,int ancho = 100, int alto = 100);
    virtual ~VehiculoBase() {

    }

    virtual void mover(int x, int y);
    virtual void escalar(int ancho, int alto);
    virtual void ocultar();
    virtual void mostrar();

   virtual void hacerSonarClaxon() const = 0;

    QLabel *label;

protected:
    QPixmap imagenOriginal;

};

class Coche : public VehiculoBase, public ClaxonCoche{
public:
    Coche(QLabel *lbl, const QString &rutaImagen, int ancho = 100, int alto = 100)
        : VehiculoBase(lbl, rutaImagen, ancho, alto) {}


    void mover(int x, int y) override;

    void hacerSonarClaxon() const override {
        tocarClaxon();  // Llamada directa al claxon heredado
    }

};

class Camion : public VehiculoBase, public ClaxonCamion {
public:
    Camion(QLabel *lbl, const QString &rutaImagen, int ancho = 100, int alto = 100)
        : VehiculoBase(lbl, rutaImagen, ancho, alto) {}


    void mover(int x, int y) override;

    void hacerSonarClaxon() const override {
        tocarClaxon();  // Llamada directa al claxon heredado
    }
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

    void hacerSonarClaxon() const override {}
    //// La clase 'Peaton' hereda de 'VehiculoBase', que contiene una función virtual pura 'hacerSonarClaxon()',
    // lo que obliga a todas las clases derivadas a implementarla. Aunque el peatón no tenga un claxon en el sentido
    // convencional, la implementación de esta función vacía o neutral en la clase 'Peaton' es necesaria para cumplir
    // con la jerarquía de clases y evitar errores de compilación debido a la función virtual pura en la clase base.
    // En este caso, la función 'hacerSonarClaxon()' no realiza ninguna acción significativa para el peatón,
    // pero su implementación es obligatoria para garantizar que la clase 'Peaton' sea instanciable y compatible
    // con la estructura del código que se basa en la herencia de 'VehiculoBase'.

};

#endif // VEHICULO_H
