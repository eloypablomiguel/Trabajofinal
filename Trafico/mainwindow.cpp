#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>


//ESTO ES UNA PRUEBA PARA VER SI FUNCIONA, HOLA SSSSSSSSSOCIO
//Ruta para cargar las imagenes
//ruta eloy-->"C:\\Users\\UGE\\Desktop\\Trabajo final\\Trabajofinal\\Trafico\\";
//ruta Pablo-->"C:\\Users\\pablo\\Desktop\\Trabajofinal\\Trafico\\";
//miguel -> C:\\Users\\migue\\Desktop\\Trabajofinal\\Trafico\\;
const QString ruta = "C:\\Users\\pablo\\Desktop\\Trabajofinal\\Trafico\\";

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
//MIGUEL NUEVO
class Vehiculo {
public:
    QLabel *label;
    QPixmap imagenOriginal;

    Vehiculo(QLabel *lbl, const QString &rutaImagen, int ancho = 100, int alto = 100)
        : label(lbl) {
        imagenOriginal.load(rutaImagen);
        QPixmap imagenEscalada = imagenOriginal.scaled(ancho, alto, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        label->setPixmap(imagenEscalada);
        label->setVisible(true);
    }

    void mover(int x, int y) {
        if (label) label->move(x, y);
    }

    void escalar(int ancho, int alto) {
        if (!imagenOriginal.isNull()) {
            QPixmap imagenEscalada = imagenOriginal.scaled(ancho, alto, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            label->setPixmap(imagenEscalada);
        }
    }

    void ocultar() {
        if (label) label->setVisible(false);
    }

    void mostrar() {
        if (label) label->setVisible(true);
    }
};
//ACABA MIGUEL NUEVO

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Se cargan las imagenes semaforo coches y se escalan
    QPixmap verde(ruta + "semaforo_verde.jpg");
    QPixmap amarillo(ruta + "semaforo_amarillo.jpg");
    QPixmap rojo(ruta + "semaforo_rojo.jpg");
    QPixmap pixmapEscalador = rojo.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QPixmap pixmapEscaladoa = amarillo.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QPixmap pixmapEscaladov = verde.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    ui->label->setPixmap(pixmapEscaladov);
    ui->label_2->setPixmap(pixmapEscaladoa);
    ui->label_3->setPixmap(pixmapEscalador);
    //imagenes cargadas

    //Se carga  imagen calle
    QPixmap calle(ruta + "calle.png");
    QPixmap pixmapEscaladocalle = calle.scaledToHeight(this->height(), Qt::SmoothTransformation);
    ui->label_6->setPixmap(pixmapEscaladocalle);
    ui->label_6->resize(pixmapEscaladocalle.size());
    ui->label_6->setAlignment(Qt::AlignCenter);
    ui->label_6->setVisible(true);
    //imagen cargada

    //Se cargan las imagenes semaforo peatones y se escalan
    QPixmap verdep(ruta + "Semaforopeaton_verde.jpg");
    QPixmap rojop(ruta + "Semaforopeaton_rojo.jpg");
    QPixmap pixmapEscaladopr = rojop.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QPixmap pixmapEscaladopv = verdep.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    ui->label_4->setPixmap(pixmapEscaladopv);
    ui->label_5->setPixmap(pixmapEscaladopr);
    //imagenes cargadas

    //MIGUEL CLASE NUEVA
    cocheRojo = new Vehiculo(ui->label_7, ruta + "coche_rojo.png", 250, 250);
    camioncito = new Vehiculo(ui->label_8, ruta + "camion.png", 300, 300);


    //Se cargan las imagenes coches
    //QPixmap cocherojo(ruta + "coche_rojo.png");
    //QPixmap camion(ruta + "camion.png");
    //QPixmap pixmapEscaladocoche=cocherojo.scaled(250, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    //QPixmap pixmapEscaladocamion=camion.scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    //Prueba rotar imagen
    /*
    QTransform transform;
    transform.rotate(180);  // Rota 180 grados

    QPixmap rotada = camion.transformed(transform);
    rotada=rotada.scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_8->setPixmap(rotada);
    //Funciona :)
    */

    //ui->label_7->setPixmap(pixmapEscaladocoche);
    //ui->label_8->setPixmap(pixmapEscaladocamion);
    //imagenes cargadas

    //como no deja usar _sleep() usamos:
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

    QPixmap calle(ruta + "calle.png");
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

    //Prueba tamaño coche
    //ui->label_7->move(x+180,y+100); //Así el coche rojo esta carril izq
    //ui->label_8->move(x+330,y+100);
    //MIGUEL NUEVA CLASE
    if (cocheRojo) cocheRojo->mover(x+180,y+100);
    if (camioncito) camioncito->mover(x+330,y+100);
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

        /*int parpa = 0;
        //no me sale q parpadee
        timerparpadeo = new QTimer(this);
        connect(timerparpadeo, &QTimer::timeout, [this, &parpa]() {
            static bool estadoParpadeo = false;
            if (estadoParpadeo) {
                semaforoPeatones->mostrarRojo();
                parpa=parpa+1;
            } else {
                semaforoPeatones->mostrarVerde();
            }
            if (parpa==2) timerparpadeo->stop();
            estadoParpadeo = !estadoParpadeo;  // Alterna el estado
        });



        timerparpadeo->start(500);
        semaforoPeatones->mostrarRojo();
        timer->setInterval(500);
        semaforoPeatones->mostrarVerde();
        timer->setInterval(500);*/
        break;
    } //ELOY GAY
}
//ojjsjsjosaf
