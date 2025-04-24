#ifndef VEHICULO_H
#define VEHICULO_H

#include <QLabel>
#include <QPixmap>
#include <QString>

class Vehiculo {
public:
    Vehiculo(QLabel *lbl, const QString &rutaImagen, int ancho = 100, int alto = 100);
    virtual ~Vehiculo() = default;

    void mover(int x, int y);
    void escalar(int ancho, int alto);
    void ocultar();
    void mostrar();

    QLabel *label;

protected:
    QPixmap imagenOriginal;
};

#endif // VEHICULO_H
