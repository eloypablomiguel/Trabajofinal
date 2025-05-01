#ifndef VEHICULO_H
#define VEHICULO_H

#include <QLabel>
#include <QPixmap>
#include <QString>

class VehiculoBase {
public:
    VehiculoBase(QLabel *lbl, const QString &rutaImagen, int ancho = 100, int alto = 100);
    virtual ~VehiculoBase() = default;

    virtual void mover(int x, int y);
    virtual void escalar(int ancho, int alto);
    virtual void ocultar();
    virtual void mostrar();

    QLabel *label;

protected:
    QPixmap imagenOriginal;
};

class Coche : public VehiculoBase {
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
