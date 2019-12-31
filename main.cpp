#include <QApplication>
#include "homepage.h"
#include "adminlogin.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    //splashscreen
    connection_db();
    QSplashScreen *splashscreen = new QSplashScreen();
    splashscreen->setPixmap(QPixmap("/home/innovator/Bibliotheque/image/library.jpeg"));
    splashscreen->show();

    adminLogin fenetre;

    QTimer::singleShot(2000, splashscreen, SLOT(close()));
    QTimer::singleShot(2000, &fenetre, SLOT(show()));


    return app.exec();
}
