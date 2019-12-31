#include <QtSql>
#include <QToolButton>
#include <QWidgetAction>
#include <QDebug>
#include <QMenu>
#include <etudiantmanager.h>
#include <etudiant.h>
#include "livreWidget.h"

livreWidget::livreWidget(): QDialog ()
{
    QSqlQuery query("SELECT etudiant FROM sqlite_sequence");
    QString nb_etudiant(query.value(0).toInt()+1);

    setMinimumSize(QSize(500, 600));
    QLabel *title = new QLabel(tr("Nouveau inscrit"));
    //![0]
    m_identifiant = new QLineEdit();
    m_identifiant->setReadOnly(true);
    m_identifiant->setPlaceholderText(nb_etudiant);

    m_auteur = new QLineEdit();
    m_auteur->setPlaceholderText(tr("Auteur"));
    m_titre = new QLineEdit();
    m_titre->setPlaceholderText(tr("Titre"));

    //![1]
    m_ajouter = new QPushButton(tr("Ajouter"));
    m_retour = new QPushButton(tr("Retour"));

    //![2]
    QGridLayout *grid = new QGridLayout();
    grid->addWidget(m_identifiant,0,0,1,4);
    grid->addWidget(m_auteur,1,0,1,4);
    grid->addWidget(m_titre,2,0,1,4);
    grid->addWidget(m_retour,6,0);
    grid->addWidget(m_ajouter,6,1);

    //![3]
    QVBoxLayout *main = new QVBoxLayout();
    main->addWidget(title);
    main->addLayout(grid);

    setLayout(main);

    //![4]
    connect(m_retour, &QPushButton::clicked, this, &livreWidget::accept);
    connect(m_ajouter, &QPushButton::clicked, this, &livreWidget::ajouter_livre);
}

livreWidget::livreWidget(QDataWidgetMapper *mapper,QModelIndex *model): QDialog ()
{   
      m_model = new QSqlRelationalTableModel(m_model);
      m_mapper = new QDataWidgetMapper(this);
        
//    QSqlQuery query("SELECT etudiant FROM sqlite_sequence");
//    QString nb_etudiant(query.value(0).toInt()+1);

    setMinimumSize(QSize(500, 600));
    QLabel *title = new QLabel(tr("Nouveau inscrit"));

    //![QLineEdit]
    m_identifiant = new QLineEdit();
    m_identifiant->setReadOnly(true);
    //m_identifiant->setPlaceholderText(nb_etudiant);
    m_auteur = new QLineEdit();
    m_auteur->setPlaceholderText(tr("Auteur"));
    m_titre = new QLineEdit();
    m_titre->setPlaceholderText(tr("Titre"));
    m_reservation = new QLineEdit();
    m_exemplaire = new QLineEdit();

    //![1]
    m_ajouter = new QPushButton(tr("Ajouter"));
    m_retour = new QPushButton(tr("Retour"));

    //![2]
    QGridLayout *grid = new QGridLayout();
    grid->addWidget(m_identifiant,0,0,1,4);
    grid->addWidget(m_auteur,1,0,1,4);
    grid->addWidget(m_titre,2,0,1,4);
    grid->addWidget(m_exemplaire,3,0,1,4);
    grid->addWidget(m_reservation,4,0,1,4);
    grid->addWidget(m_retour,5,0);
    grid->addWidget(m_ajouter,6,1);

    //![3]
    QVBoxLayout *main = new QVBoxLayout();
    main->addWidget(title);
    main->addLayout(grid);
    
    //![mapper]

    m_mapper->addMapping(m_titre, m_model->fieldIndex("titre"));
    m_mapper->addMapping(m_auteur, m_model->fieldIndex("auteur"));
    m_mapper->addMapping(m_reservation, m_model->fieldIndex("reservation"));
    m_mapper->addMapping(m_exemplaire, m_model->fieldIndex("exemplaire"));
    m_mapper->addMapping(m_identifiant, m_model->fieldIndex("id"));
    
    setLayout(main);

    //![4]
    connect(m_retour, &QPushButton::clicked, this, &livreWidget::accept);
    connect(m_ajouter, &QPushButton::clicked, this, &livreWidget::ajouter_livre);   
}



void livreWidget::ajouter_livre(){
    QString auteur = m_auteur->text(), titre = m_titre->text();
    if(auteur.isEmpty() || titre.isEmpty() ){
        QMessageBox::critical(this, "Saisie incorrect", "Vous n'avez pas rempli au moins un champ");
    }
    else{
        QSqlQuery query;
        query.prepare("INSERT INTO oeuvre (titre, auteur)"
                      "VALUES(:titre, :auteur)");
        query.bindValue(":titre", m_titre->text().toUpper());
        query.bindValue(":auteur", m_auteur->text().toUpper());
        query.exec();
        hide();
    }
}


//! [0]

//! [1]

//! [1]

//! [2]

//! [2]

//! [3]

//! [3]

//! [4] //! [5]

//! [4]

//! [6]
    
//! [5] //! [6]

//! [7]

//! [7]

