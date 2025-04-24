#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <vehiculo.h>
#include <semaforo.h>
#include <QRandomGenerator>

//Ruta para cargar las imagenes
//ruta eloy-->"C:\\Users\\UGE\\Desktop\\Trabajo final\\Trabajofinal\\Trafico\\";
//ruta Pablo-->"C:\\Users\\pablo\\Desktop\\Trabajofinal\\Trafico\\";
//miguel -> C:\\Users\\migue\\Desktop\\Trabajofinal\\Trafico\\;
const QString ruta = "C:\\Users\\pablo\\Desktop\\Trabajofinal\\Trafico\\";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Se cargan las imagenes semaforo coches y se escalan
    QPixmap verde(ruta + "semaforo_verde.png");
    QPixmap amarillo(ruta + "semaforo_amarillo.png");
    QPixmap rojo(ruta + "semaforo_rojo.png");
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
    QPixmap verdep(ruta + "Semaforopeaton_verde.png");
    QPixmap rojop(ruta + "Semaforopeaton_rojo.png");
    QPixmap pixmapEscaladopr = rojop.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QPixmap pixmapEscaladopv = verdep.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    ui->label_4->setPixmap(pixmapEscaladopv);
    ui->label_5->setPixmap(pixmapEscaladopr);
    //imagenes cargadas

    //MIGUEL CLASE NUEVA
    cocheRojo = new Vehiculo(ui->label_7, ruta + "coche_rojo.png", 250, 250);
    camioncito = new Vehiculo(ui->label_8, ruta + "camion.png", 300, 300);


    //Prueba peatones
    QPixmap peaton(ruta + "foto_socio.png");
    QPixmap pixmapEscaladopeaton=peaton.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->peaton_socio->setPixmap(pixmapEscaladopeaton);
    peatonX = ui->peaton_socio->x(); // o valor inicial fijo
    timerPeaton = new QTimer(this);
    connect(timerPeaton, &QTimer::timeout, this, &MainWindow::moverPeaton);
    timerPeaton->start(50);

//Timer semaforo
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::cambiarSemaforo);
    timer->start();

    //creamos semaforos
    semaforoCoches = new Semaforo(ui->label, ui->label_2, ui->label_3);
    semaforoPeatones = new Semaforo(ui->label_4, nullptr, ui->label_5);

    //para que el coche se mueva
    // Posición inicial del coche y del camion
    cocheY = 0;
    camionY = 0;    // Comienza desde abajo
    peatonX=500;

    // Temporizador para animar el coche
    timerCoche = new QTimer(this);
    connect(timerCoche, &QTimer::timeout, this, &MainWindow::moverCoche);
    timerCoche->start(50);  // 50 ms = 20 FPS aprox.

    timerCamion = new QTimer(this);
    connect(timerCamion, &QTimer::timeout, this, &MainWindow::moverCamion);
    timerCamion->start(50);  // velocidad del camión


    //Velocidad Random incial Socio
    velocidadSocio = QRandomGenerator::global()->bounded(2, 10);
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

    //Prueba colocar peaton
    ui->peaton_socio->move(x+550, y+125);

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
        semaforoRojo=false;
        break;
    case 1: // Amarillo
        semaforoCoches->mostrarAmarillo();
        semaforoPeatones->mostrarRojo();
        timer->setInterval(3000);
        break;
    case 2: // Rojo
        semaforoRojo=true;
        semaforoCoches->mostrarRojo();
        semaforoPeatones->mostrarVerde();
        timer->setInterval(6000);
        break;
    }
}
void MainWindow::moverCoche()
{
    bool enZonaPaso = cocheY <= yPasoPeatones  && cocheY >= yPasoPeatones-250 ; //revisar peatones
    bool nomueveCoche= enZonaPaso && (semaforoRojo || cruzandoPeaton);
    if(nomueveCoche){
        cocheY += 0;}
    else{cocheY +=15;}

    // Si sale de la ventana, vuelve a empezar
    if (cocheY > height()) {
        cocheY = -300;  // reinicia por abajo
    }

    if (cocheRojo) {
        cocheRojo->mover(cocheRojo->label->x(), cocheY);  // y = altura deseada
    }
}
void MainWindow::moverCamion()
{
    // Ver si está en la zona del paso de peatones
    bool enZonaPaso = camionY <= yPasoPeatones + 200 && camionY >= yPasoPeatones ; //revisar peatones
    bool nomueveCamion= enZonaPaso && (semaforoRojo || cruzandoPeaton);



    if(nomueveCamion) {camionY-=0;}
    else{ camionY -= 15;}// Se mueve hacia arriba

    if (camionY <-400) {
            camionY = 450;  // Reaparece desde abajo
        }

        if (camioncito) camioncito->mover(camioncito->label->x(), camionY);


}
void MainWindow::moverPeaton() {
    if (!cruzandoPeaton && !semaforoRojo && (peatonX > 500 && peatonX < this->width() - 520)) {
        return;  // Solo puede empezar a cruzar cuando hay semáforo rojo (para coches)
    }

    // Si el peatón está dentro del paso de cebra, marcamos que está cruzando
    if (semaforoRojo && peatonX < this->width() - 520 && peatonX > 500) {
        cruzandoPeaton = true;
    }

    peatonX -= velocidadSocio;
    qDebug() << "PeatonX:" << peatonX;

    // Si ya ha cruzado, lo reinicias y desactivas el cruce
    if (peatonX < 450) {
        peatonX = this->width() - 420;
        cruzandoPeaton = false;
        velocidadSocio = QRandomGenerator::global()->bounded(2, 10); // nueva velocidad aleatoria
    }

    ui->peaton_socio->move(peatonX, ui->peaton_socio->y());
}
