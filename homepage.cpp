#include "homepage.h"
#include "inscription.h"
#include "emprunter.h"
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPixmap>
#include <QGridLayout>
#include <QInputDialog>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "livre.h"
/*
 * library to connect QT to databse myqsl
*/


homepage::homepage(QWidget *parent) : QDialog(parent)
{
    this->setMinimumSize(QSize(1000, 600));
    main_page();

}

//Main page of my program
void homepage::main_page() {
    //MINIMUN DIMENSION OF ELEMENT AND SETTING OF WINDOW

    this->setPalette(Qt::white);
    this->setStyleSheet("QPushButton {color: black;}");
    //QGridLayout is used to manage layout

    QPixmap imageMain(QSize(250,250));
    imageMain.load("/home/innovator/Bibliotheque/image/book.jpg");

    QLabel *title = new QLabel(tr("Bienvenu a la bibliotheque Esatic"));
    title->setAlignment(Qt::AlignCenter);
    QLabel *image = new QLabel();

    image->setPixmap(imageMain);

    main_vlayout = new QVBoxLayout();

    QHBoxLayout *title_hlayout = new QHBoxLayout();
    QVBoxLayout *button_vlayout = new QVBoxLayout();
    center_hlayout = new QHBoxLayout();

    QPushButton *bt_inscription = new QPushButton(tr("Inscription"));
    QPushButton *bt_ouvrage = new QPushButton(tr("Oeuvres && examplaires"));
    QPushButton *bt_emprunter = new QPushButton(tr("Emprunt && reservation"));
    QPushButton *bt_deconnecter = new QPushButton(tr("Deconnecter"));

    //INSERTION IN LAYOUT FOR GOOD SEE
    title_hlayout->addWidget(title);

    button_vlayout->addWidget(bt_inscription);
    button_vlayout->addWidget(bt_ouvrage);
    button_vlayout->addWidget(bt_emprunter);
    button_vlayout->addWidget(bt_deconnecter);

    //INSERTION IN GRIDLAYOUT

    center_hlayout->addLayout(button_vlayout);
    center_hlayout->addWidget(image);

    //INSERTION IN GRIDLAYOUT
    main_vlayout->addLayout(title_hlayout);
    main_vlayout->addLayout(center_hlayout);

    //CONNECTION TO DB
    this->setLayout(main_vlayout);

    //Connexion
    connect(bt_inscription,SIGNAL(clicked(bool)),this,SLOT(click_inscription()));
    connect(bt_ouvrage,SIGNAL(clicked(bool)),this,SLOT(click_ouvrage()));
    connect(bt_emprunter,SIGNAL(clicked(bool)),this,SLOT(click_emprunter()));
    connect(bt_deconnecter,&QPushButton::clicked,this,&homepage::accept);
}

//PAGE OF INSCRIPTION
void homepage::inscription_page(){
    
    class inscription *page_inscription = new class inscription(this);
    page_inscription->exec();
}

//DEFINITIONS OF SLOTS

void homepage::click_inscription(){
    //QString donnee = QInputDialog::getMultiLineText(this, "Inscription etudiant", "Etudiant");
    inscription_page();
}


void homepage::click_ouvrage(){
    livre *page_login = new livre(this);
    page_login->exec();
}

void homepage::click_emprunter(){
    emprunter *page_login = new emprunter(this);
    page_login->exec();
}




void connection_db(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
          db.setDatabaseName("/home/innovator/Bibliotheque/bibliotheque.db");
          bool ok = db.open();
          qDebug()<<ok;

}
