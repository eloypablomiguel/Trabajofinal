#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Se cargan las imagenes semaforo coches
    QPixmap verde("C:\\Users\\UGE\\Desktop\\Trabajo final\\Trabajofinal\\Trafico\\semaforo_verde.jpg");
    QPixmap amarillo("C:\\Users\\UGE\\Desktop\\Trabajo final\\Trabajofinal\\Trafico\\semaforo_amarillo.jpg");
    QPixmap rojo("C:\\Users\\UGE\\Desktop\\Trabajo final\\Trabajofinal\\Trafico\\semaforo_rojo.jpg");
    QPixmap pixmapEscalador = rojo.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QPixmap pixmapEscaladoa = amarillo.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QPixmap pixmapEscaladov = verde.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    ui->label->setPixmap(pixmapEscaladov);
    ui->label_2->setPixmap(pixmapEscaladoa);
    ui->label_3->setPixmap(pixmapEscalador);

    ui->label->setVisible(true);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    //imagenes cargadas

    //Se carga  imagen calle
    QPixmap calle("C:\\Users\\UGE\\Desktop\\Trabajo final\\Trabajofinal\\Trafico\\calle.png");
    QPixmap pixmapEscaladocalle = calle.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_6->setPixmap(pixmapEscaladocalle);
    //imagen cargada

    //Se cargan las imagenes semaforo peatones
    QPixmap verdep("C:\\Users\\UGE\\Desktop\\Trabajo final\\Trabajofinal\\Trafico\\Semaforopeaton_verde.jpg");
    QPixmap rojop("C:\\Users\\UGE\\Desktop\\Trabajo final\\Trabajofinal\\Trafico\\Semaforopeaton_rojo.jpg");
    QPixmap pixmapEscaladopr = rojop.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QPixmap pixmapEscaladopv = verdep.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    ui->label_4->setPixmap(pixmapEscaladopv);
    ui->label_5->setPixmap(pixmapEscaladopr);

    ui->label_4->setVisible(false);
    ui->label_5->setVisible(true);
    //imagenes cargadas

    //QTimer *timer = new QTimer(this);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::cambiarSemaforo);
    timer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Funcion q cambia los estados del semaforo
void MainWindow::cambiarSemaforo()
{

        static int estado = 0;
        estado = (estado + 1) % 3;  // Cambia entre 0, 1, 2 (verde, amarillo, rojo)

        if (estado == 0) {  // Verde
            ui->label->setVisible(true);
            ui->label_2->setVisible(false);
            ui->label_3->setVisible(false);

            ui->label_4->setVisible(false);
            ui->label_5->setVisible(true);

            timer->setInterval(8000); // Cambia cada 3 segundos
        } else if (estado == 1) {  // Amarillo
            ui->label->setVisible(false);
            ui->label_2->setVisible(true);
            ui->label_3->setVisible(false);

            ui->label_4->setVisible(false);
            ui->label_5->setVisible(true);

            timer->setInterval(3000); // Cambia cada 3 segundos
        } else if (estado == 2) {  // Rojo
            ui->label->setVisible(false);
            ui->label_2->setVisible(false);
            ui->label_3->setVisible(true);

            ui->label_4->setVisible(true);
            ui->label_5->setVisible(false);

            timer->setInterval(8000); // Cambia cada 3 segundos
        }
}
