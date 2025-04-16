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

    // CAMION SE PARA
    int yPasoPeatones = 200; // Puedes ajustar según dónde esté tu paso de peatones

    bool camionDetenido = false;
    bool semaforoRojo;  // true = rojo, false = verde



};
#endif // MAINWINDOW_H
