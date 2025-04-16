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


};
#endif // MAINWINDOW_H
