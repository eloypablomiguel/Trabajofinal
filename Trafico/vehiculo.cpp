#include "vehiculo.h"

VehiculoBase::VehiculoBase(QLabel *lbl, const QString &rutaImagen, int ancho, int alto)
    : label(lbl) {
    imagenOriginal.load(rutaImagen);
    QPixmap imagenEscalada = imagenOriginal.scaled(ancho, alto, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    label->setPixmap(imagenEscalada);
    label->setVisible(true);
}

void VehiculoBase::mover(int x, int y) {
    if (label) label->move(x, y);
}

void VehiculoBase::escalar(int ancho, int alto) {
    if (!imagenOriginal.isNull()) {
        QPixmap imagenEscalada = imagenOriginal.scaled(ancho, alto, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        label->setPixmap(imagenEscalada);
    }
}

void VehiculoBase::ocultar() {
    if (label) label->setVisible(false);
}

void VehiculoBase::mostrar() {
    if (label) label->setVisible(true);
}

void Coche::mover(int x, int y) {
    VehiculoBase::mover(x, y);
    // Aquí podemos añadir un comportamiento de movimiento específico para el coche
    claxon = new Claxon();
}

void Camion::mover(int x, int y) {
    VehiculoBase::mover(x, y);
}

void Peaton::mover(int x, int y){
    VehiculoBase::mover(x, y);
}

