#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qlabel.h"
#include <QMainWindow>
#include <QTimer>


class Semaforo;
class Vehiculo;


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
    void moverCoche();
    void moverCamion();
    void moverPeaton();



protected:
    void resizeEvent(QResizeEvent *event);

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QTimer *timerparpadeo;

    Semaforo *semaforoCoches;
    Semaforo *semaforoPeatones;

    Vehiculo *cocheRojo;
    Vehiculo *camioncito;


    QTimer *timerCoche;
    int cocheY;  // posición y actual

    QTimer *timerCamion;
    int camionY;  // posición y actual

    QTimer *timerPeaton;
    int peatonX; //posicion x actual peaton


    // CAMION SE PARA
    int yPasoPeatones = 200; // Puedes ajustar según dónde esté tu paso de peatones

    bool camionDetenido = false;
    bool semaforoRojo;  // true = rojo, false = verde
    bool cruzandoPeaton;

    int velocidadSocio;

    //el paso de peatones es 400px de alto y 500 de ancho
    // la calle es de 896px de ancho y 1241 de alto
    //y el paso esta en el px 802 arriba y el 415 abajo
    //a la izq en 270 px y a la derecha en 750


};
#endif // MAINWINDOW_H
