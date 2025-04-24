#include "semaforo.h"

Semaforo::Semaforo(QLabel *v, QLabel *a, QLabel *r)
    : verde(v), amarillo(a), rojo(r) {}

void Semaforo::mostrarVerde() {
    if (verde) verde->setVisible(true);
    if (amarillo) amarillo->setVisible(false);
    if (rojo) rojo->setVisible(false);
}

void Semaforo::mostrarAmarillo() {
    if (verde) verde->setVisible(false);
    if (amarillo) amarillo->setVisible(true);
    if (rojo) rojo->setVisible(false);
}

void Semaforo::mostrarRojo() {
    if (verde) verde->setVisible(false);
    if (amarillo) amarillo->setVisible(false);
    if (rojo) rojo->setVisible(true);
}
