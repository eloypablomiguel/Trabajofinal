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

#endif // VEHICULO_H
