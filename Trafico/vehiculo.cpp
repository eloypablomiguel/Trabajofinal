#include "vehiculo.h"

Vehiculo::Vehiculo(QLabel *lbl, const QString &rutaImagen, int ancho, int alto)
    : label(lbl) {
    imagenOriginal.load(rutaImagen);
    QPixmap imagenEscalada = imagenOriginal.scaled(ancho, alto, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    label->setPixmap(imagenEscalada);
    label->setVisible(true);
}

void Vehiculo::mover(int x, int y) {
    if (label) label->move(x, y);
}

void Vehiculo::escalar(int ancho, int alto) {
    if (!imagenOriginal.isNull()) {
        QPixmap imagenEscalada = imagenOriginal.scaled(ancho, alto, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        label->setPixmap(imagenEscalada);
    }
}

void Vehiculo::ocultar() {
    if (label) label->setVisible(false);
}

void Vehiculo::mostrar() {
    if (label) label->setVisible(true);
}
