#include "ajouterWidget.h"
#include <QToolButton>
#include <QWidgetAction>
#include <QDebug>
#include <QMenu>
#include <etudiantmanager.h>
#include <etudiant.h>
#include "inscription.h"

ajouterWidget::ajouterWidget(QWidget *parent)
    : QDialog (parent)
{
    QSqlQuery query("SELECT etudiant FROM sqlite_sequence");
    QString nb_etudiant(query.value(0).toInt()+1);

    setMinimumSize(QSize(500, 200));
    QLabel *title = new QLabel(tr("Nouveau inscrit"));
    //![0]
    m_identifiant = new QLineEdit();
    m_identifiant->setReadOnly(true);
    m_identifiant->setPlaceholderText(nb_etudiant);

    m_nom = new QLineEdit();
    m_nom->setPlaceholderText(tr("Nom"));
    m_niveau = new QLineEdit();
    m_niveau->setPlaceholderText(tr("Niveau"));
    m_prenom = new QLineEdit();
    m_prenom->setPlaceholderText(tr("Prenom"));
    m_matricule = new QLineEdit();
    m_matricule->setPlaceholderText(tr("Matricule"));

    //![1]
    m_ajouter = new QPushButton(tr("Ajouter"));
    m_retour = new QPushButton(tr("Retour"));

    //![2]
    QGridLayout *grid = new QGridLayout();
    grid->addWidget(m_identifiant,0,0,1,4);
    grid->addWidget(m_nom,1,0,1,4);
    grid->addWidget(m_prenom,2,0,1,4);
    grid->addWidget(m_niveau,3,0,1,4);
    grid->addWidget(m_matricule,4,0,1,4);
    grid->addWidget(m_retour,6,0);
    grid->addWidget(m_ajouter,6,1);

    //![3]
    QVBoxLayout *main = new QVBoxLayout();
    main->addWidget(title);
    main->addLayout(grid);

    setLayout(main);

    //![4]
    connect(m_retour, &QPushButton::clicked, this, &ajouterWidget::accept);
    connect(m_ajouter, &QPushButton::clicked, this, &ajouterWidget::ajouter_etudiant);

}

void ajouterWidget::ajouter_etudiant(){
    QString nom = m_nom->text(), prenom= m_prenom->text(), niveau = m_niveau->text(), matricule = m_matricule->text();
    if(nom.isEmpty() || prenom.isEmpty() || niveau.isEmpty() || matricule.isEmpty()){
        QMessageBox::critical(this, "Saisie incorrect", "Vous n'avez pas rempli au moins un champ");
    }
    else{
        insert(nom, prenom, niveau, matricule);
        hide();
    }
}


