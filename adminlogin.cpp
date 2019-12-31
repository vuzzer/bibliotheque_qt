#include "adminlogin.h"
#include <QFont>
#include <homepage.h>

adminLogin::adminLogin(QWidget *parent): QWidget (parent)
{
    QGridLayout *grid = new QGridLayout();

    this->setFixedSize(300,200);

    m_title = new QLabel(tr("BIBLIOTHEQUE"));
    m_title->setAlignment(Qt::AlignHCenter);
    m_title->setStyleSheet("color:green");
    m_password = new QLineEdit();
    m_password->setEchoMode(QLineEdit::Password);
    m_admin = new QLineEdit();
    m_connexion = new QPushButton(tr("connexion"));
    m_messageError = new QLabel(tr("")); //Affiche les messges d'erreurs pour les connexions incorrectes
    m_messageError->hide();

    m_form = new QFormLayout();
    m_form->addRow("admin", m_admin);
    m_form->addRow("password", m_password);

    m_title->setFont(QFont("Times", 16, QFont::DemiBold));

    grid->addWidget(m_title,0,0,1,4);
    grid->addLayout(m_form,1,0,1,4);
    grid->addWidget(m_messageError,2,0,1,4);
    grid->addWidget(m_connexion,3,3);

    this->setLayout(grid);

    connect(m_connexion,SIGNAL(clicked(bool)),this,SLOT(openMain()));

}

void adminLogin::openMain(){
    homepage *fenetre = new homepage();
    QString tp_password((m_password->text()).toLower()), tp_admin((m_admin->text()).toLower());
    if(tp_password == password && tp_admin == admin){
        QTimer::singleShot(2000, this, SLOT(close()));
        QTimer::singleShot(2000, fenetre, SLOT(show()));
    }
    else{
        if(tp_password != password){
            m_messageError->setText("<font color='red'>Le mot de passe saisie est incorrecte</font>");
            m_messageError->setFont(QFont("Times", 10, QFont::DemiBold));
            m_messageError->show();
        }
        else if(tp_admin != admin){
            m_messageError->setText("<font color='red'>Le nom utilisateur est saisie incorrect</font>");
            m_messageError->setFont(QFont("Times", 10, QFont::DemiBold));
            m_messageError->show();
        }
        else{
            m_messageError->setText("<font color='red'>Le mot de passe et le nom d'utlisateur saisie sont incorrects</font>");
            m_messageError->setFont(QFont("Times", 10, QFont::DemiBold));
            m_messageError->show();
        }
    }
}

//Iniatlisation des des methodes statiques
QString adminLogin::password = "bienvenu";
QString adminLogin::admin = "admin";
