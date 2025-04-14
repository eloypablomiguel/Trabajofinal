#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>


class Semaforo {
public:
    QLabel *verde;
    QLabel *amarillo;
    QLabel *rojo;

    Semaforo(QLabel *v, QLabel *a, QLabel *r)
        : verde(v), amarillo(a), rojo(r) {}

    void mostrarVerde() {
        verde->setVisible(true);
        if (amarillo) amarillo->setVisible(false); //crashea sin if
        rojo->setVisible(false);
    }

    void mostrarAmarillo() {
        verde->setVisible(false);
        if (amarillo) amarillo->setVisible(true);  //crashea sin if
        rojo->setVisible(false);
    }

    void mostrarRojo() {
        verde->setVisible(false);
        if (amarillo) amarillo->setVisible(false);  //crashea sin if
        rojo->setVisible(true);
    }
};


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Se cargan las imagenes semaforo coches y se escalan
    QPixmap verde("C:\\Users\\UGE\\Desktop\\Trabajo final\\Trabajofinal\\Trafico\\semaforo_verde.jpg");
    QPixmap amarillo("C:\\Users\\UGE\\Desktop\\Trabajo final\\Trabajofinal\\Trafico\\semaforo_amarillo.jpg");
    QPixmap rojo("C:\\Users\\UGE\\Desktop\\Trabajo final\\Trabajofinal\\Trafico\\semaforo_rojo.jpg");
    QPixmap pixmapEscalador = rojo.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QPixmap pixmapEscaladoa = amarillo.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QPixmap pixmapEscaladov = verde.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    ui->label->setPixmap(pixmapEscaladov);
    ui->label_2->setPixmap(pixmapEscaladoa);
    ui->label_3->setPixmap(pixmapEscalador);
    //imagenes cargadas

    //Se carga  imagen calle
    QPixmap calle("C:\\Users\\UGE\\Desktop\\Trabajo final\\Trabajofinal\\Trafico\\calle.png");
    QPixmap pixmapEscaladocalle = calle.scaledToHeight(this->height(), Qt::SmoothTransformation);
    ui->label_6->setPixmap(pixmapEscaladocalle);
    ui->label_6->resize(pixmapEscaladocalle.size());
    ui->label_6->setAlignment(Qt::AlignCenter);
    ui->label_6->setVisible(true);
    //imagen cargada

    //Se cargan las imagenes semaforo peatones y se escalan
    QPixmap verdep("C:\\Users\\UGE\\Desktop\\Trabajo final\\Trabajofinal\\Trafico\\Semaforopeaton_verde.jpg");
    QPixmap rojop("C:\\Users\\UGE\\Desktop\\Trabajo final\\Trabajofinal\\Trafico\\Semaforopeaton_rojo.jpg");
    QPixmap pixmapEscaladopr = rojop.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QPixmap pixmapEscaladopv = verdep.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    ui->label_4->setPixmap(pixmapEscaladopv);
    ui->label_5->setPixmap(pixmapEscaladopr);

    //compo no deja usar _sleep() usamos:
    //QTimer *timer = new QTimer(this);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::cambiarSemaforo);
    timer->start();

    //creamos semaforos
    semaforoCoches = new Semaforo(ui->label, ui->label_2, ui->label_3);
    semaforoPeatones = new Semaforo(ui->label_4, nullptr, ui->label_5);
}


MainWindow::~MainWindow()
{
    delete ui;
}

//escalamos calle
void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    QPixmap calle("C:\\Users\\UGE\\Desktop\\Trabajo final\\Trabajofinal\\Trafico\\calle.png");
    QPixmap pixmapEscaladocalle = calle.scaledToHeight(this->height(), Qt::SmoothTransformation);
    ui->label_6->setPixmap(pixmapEscaladocalle);
    ui->label_6->resize(pixmapEscaladocalle.size());

    //centramos calle
    int x = (this->width() - ui->label_6->width()) / 2;
    int y = (this->height() - ui->label_6->height()) / 2;
    ui->label_6->move(x, y);

    //colocamos semaforos. Solo queda bien para pantalla completa
    ui->label->move(x+150, y+80);
    ui->label_2->move(x+150, y+80);
    ui->label_3->move(x+150, y+80);
    ui->label_4->move(x+145, y+90);
    ui->label_5->move(x+145, y+90);
}

//Funcion q cambia los estados del semaforo
void MainWindow::cambiarSemaforo()
{
    static int estado = 0;
    estado = (estado + 1) % 3;

    switch (estado) {
    case 0: // Verde
        semaforoCoches->mostrarVerde();
        semaforoPeatones->mostrarRojo();
        timer->setInterval(8000);
        break;
    case 1: // Amarillo
        semaforoCoches->mostrarAmarillo();
        semaforoPeatones->mostrarRojo();
        timer->setInterval(3000);
        break;
    case 2: // Rojo
        semaforoCoches->mostrarRojo();
        semaforoPeatones->mostrarVerde();
        timer->setInterval(6000);


        //nobme sale q parpadee
        /*timerparpadeo = new QTimer(this);
        connect(timerparpadeo, &QTimer::timeout, [this]() {
            static bool estadoParpadeo = false;
            if (estadoParpadeo) {
                semaforoPeatones->mostrarRojo();
            } else {
                semaforoPeatones->mostrarVerde();
            }
            estadoParpadeo = !estadoParpadeo;  // Alterna el estado
        });

        timerparpadeo->start(500);
        /*semaforoPeatones->mostrarRojo();
        timer->setInterval(500);
        semaforoPeatones->mostrarVerde();
        timer->setInterval(500);*/
        break;
    }
}
