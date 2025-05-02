#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qlabel.h"
#include <QMainWindow>
#include <QTimer>
#include <vector>
#include <algorithm>


class VehiculoBase; // Declaración adelantada
class Coche;
class Camion;
class Semaforo;
class Peaton;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void cambiarSemaforo();
    void moverVehiculos(); // Función para mover todos los vehículos
    void moverPeaton();

protected:
    void resizeEvent(QResizeEvent *event);

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QTimer *timerparpadeo;

    Semaforo *semaforoCoches;
    Semaforo *semaforoPeatones;

    VehiculoBase *cocheRojo;
    VehiculoBase *camioncito;

    QTimer *timerVehiculos; // Un único timer para mover los vehículos
    int cocheY;  // Posición y actual del coche
    int camionY; // Posición y actual del camión

    QTimer *timerPeaton;

    // CAMION SE PARA
    int yPasoPeatones = 200; // Puedes ajustar según dónde esté tu paso de peatones

    bool camionDetenido = false;
    bool semaforoRojo;  // true = rojo, false = verde

    std::vector<Peaton*> peatones;  // Contenedor para los peatones
};
#endif // MAINWINDOW_H
