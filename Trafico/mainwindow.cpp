#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <vehiculo.h>
#include <semaforo.h>
#include <QRandomGenerator>
#include <vector>
#include <algorithm>

//Ruta para cargar las imagenes
//ruta eloy-->"C:\\Users\\UGE\\Desktop\\Trabajo final\\Trabajofinal\\Trafico\\";
//ruta Pablo-->"C:\\Users\\pablo\\Desktop\\Trabajofinal\\Trafico\\";
//miguel -> C:\\Users\\migue\\Desktop\\Trabajofinal\\Trafico\\";
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

    // MIGUEL CLASE NUEVA CON HERENCIA
    cocheRojo = new Coche(ui->label_7, ruta + "coche_rojo.png", 250, 250);
    camioncito = new Camion(ui->label_8, ruta + "camion.png", 300, 300);


    Peaton* nuevoPeaton = new Peaton(ui->peaton_socio, ruta + "foto_socio.png",100,100,"socio");
    peatones.push_back(nuevoPeaton);

    Peaton* nuevoPeaton2 = new Peaton(ui->peaton_miguel, ruta + "foto_miguel.png",100,100, "miguel");
    peatones.push_back(nuevoPeaton2);

    Peaton* nuevoPeaton3 = new Peaton(ui->peaton_pablo, ruta + "foto_pablo.png",100,100, "pablo");
    peatones.push_back(nuevoPeaton3);

    ui->peaton_miguel->resize(100, 100);  // Tamaño visible

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

    //para que los coches se muevan
    // Posición inicial del coche y del camion (ahora se gestiona en la creación del Vehiculo)
    cocheY = 0;
    camionY = 0;     // Comienza desde abajo

    // Temporizador para animar los coches (ahora es uno solo)
    timerVehiculos = new QTimer(this);
    connect(timerVehiculos, &QTimer::timeout, this, &MainWindow::moverVehiculos); // Conectamos a la nueva función
    timerVehiculos->start(50);  // 50 ms = 20 FPS aprox.
}

MainWindow::~MainWindow()
{
    delete cocheRojo;
    delete camioncito;
    for (auto p : peatones) delete p;
    peatones.clear();
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
    //ui->peaton_socio->move(x+550, y+125);

    //Prueba tamaño coche
    //ui->label_7->move(x+180,y+100); //Así el coche rojo esta carril izq
    //ui->label_8->move(x+330,y+100);
    //MIGUEL NUEVA CLASE
    if (cocheRojo) cocheRojo->mover(x+180,y+100);
    if (camioncito) camioncito->mover(x+330,y+100);

    for (auto peaton : peatones) {
        if (!peaton->cruzando) {//Cuando cambias de tamaño la ventana, los peatones se recolocan a valores fijos. Esto puede resultar en saltos visuales si están cruzando en ese momento.
            if (peaton->nombre=="socio"){
                peaton->mover(x,y+130); //muestra, pero no hace caso a x
            }
            if (peaton->nombre=="pablo"){
                peaton->mover(x,y+190); //muestra, pero no hace caso a x
            }
            if (peaton->nombre=="miguel"){
                peaton->mover(x,y+320); //muestra, pero no hace caso a x
            }
        }
    }
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

// Función para mover todos los vehículos
void MainWindow::moverVehiculos()
{
    bool hayPeatonCruzando = std::any_of(peatones.begin(), peatones.end(), [](Peaton* p){
        return p->cruzando;
    });
        int velocidad = 15;

        // Mover el coche rojo
        if (cocheRojo) {
            bool enZonaPasoCoche = cocheRojo->label->y() <= yPasoPeatones-150  && cocheRojo->label->y() >= yPasoPeatones-250 ;
            bool nomueveCoche= enZonaPasoCoche && (semaforoRojo || hayPeatonCruzando);
            if(nomueveCoche){
                cocheY += 0;}
            else{cocheY += velocidad;}

            if (cocheY > height()) {
                cocheY = -300;
            }
            cocheRojo->mover(cocheRojo->label->x(), cocheY);

            if(!semaforoRojo && hayPeatonCruzando){
                cocheRojo->hacerSonarClaxon();
            }
        }

        // Mover el camión
        if (camioncito) {
            bool enZonaPasoCamion = camioncito->label->y() <= yPasoPeatones + 200 && camioncito->label->y() >= yPasoPeatones ;
            bool nomueveCamion= enZonaPasoCamion && (semaforoRojo || hayPeatonCruzando);
            if(nomueveCamion) {camionY-=0;}
            else{ camionY -= velocidad;}

            if (camionY <-400) {
                camionY = 450;
            }
            camioncito->mover(camioncito->label->x(), camionY);
            if(!semaforoRojo && hayPeatonCruzando){
                camioncito->hacerSonarClaxon();
            }
        }
}


void MainWindow::moverPeaton() {
    for (auto peaton : peatones) {
        //peaton->mover(this->width() - 550, peaton->label->y());

        if (peaton->cruzando==false && !semaforoRojo && (peaton->label->x() > 530 && peaton->label->x() < this->width() - 520)) {
            //return;  // Solo puede empezar a cruzar cuando hay semáforo rojo (para coches)
            continue;  // Solo puede empezar a cruzar cuando hay semáforo rojo (para coches)
        }
        // Mover todos los peatones
        // Si el peatón está dentro del paso de cebra, marcamos que está cruzando
        if (semaforoRojo && peaton->label->x() < this->width() - 520 && peaton->label->x() > 500) {
            peaton->cruzando = true; //peaton-> necesario??
        }

        //acelera si se pone en rojo los peatones
        if (peaton->cruzando==true && !semaforoRojo){
            peaton->velocidad+=2;
        }
    //}

    //for (auto peaton : peatones) {
        if (peaton->nombre == "socio"||peaton->nombre == "pablo") {
            // Si ya ha cruzado, resetear su posición
            //qDebug() << "Peaton:" << peaton->label->x();
            if (peaton->label->x() < 500) {
                peaton->label->move(this->width() - 420, peaton->label->y());
                peaton->cruzando = false;  // El peatón ha terminado de cruzar
                peaton->velocidad = QRandomGenerator::global()->bounded(2, 10); // nueva velocidad aleatoria
            }

            peaton->mover(peaton->label->x() - peaton->velocidad, peaton->label->y());
        }

        if (peaton->nombre == "miguel") {
           // qDebug() << "Peaton2:" << peaton->label->x();
            // Si ya ha cruzado, resetear su posición
            if (peaton->label->x() > this->width() - 480) {
                peaton->label->move(450, peaton->label->y());
                peaton->cruzando = false;  // El peatón ha terminado de cruzar
                peaton->velocidad = QRandomGenerator::global()->bounded(2, 10); // nueva velocidad aleatoria
            }

            peaton->mover(peaton->label->x() + peaton->velocidad, peaton->label->y());
        }

    }
}
