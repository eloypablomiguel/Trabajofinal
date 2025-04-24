#ifndef SEMAFORO_H
#define SEMAFORO_H

#include <QLabel>

class Semaforo {
public:
    Semaforo(QLabel *v, QLabel *a, QLabel *r);
    virtual ~Semaforo() = default;

    void mostrarVerde();
    void mostrarAmarillo();
    void mostrarRojo();

private:
    QLabel *verde;
    QLabel *amarillo;
    QLabel *rojo;
};

#endif // SEMAFORO_H
