#include "exemplairewidget.h"
#include <QSqlQuery>

exemplaireWidget::exemplaireWidget(QWidget *parent): QDialog(parent)
{



    setMinimumSize(QSize(500, 200));
    QLabel *title = new QLabel(tr("Nouveau inscrit"));
    //![0]
    m_identifiant_livre = new QLineEdit();
    m_identifiant_livre->setPlaceholderText("identifiant livre");
    m_etat = new QComboBox();
    m_etat->addItem("Bon");
    m_etat->addItem("vieux");
    m_etat->addItem("neuf");

    //![1]
    m_ajouter = new QPushButton(tr("Ajouter"));
    m_retour = new QPushButton(tr("Retour"));

    //![2]
    QFormLayout *form_layout = new QFormLayout();
    form_layout->addRow("Identifiant livre",m_identifiant_livre);
    form_layout->addRow("Etat du livre",m_etat);


    //![3]
    QVBoxLayout *main = new QVBoxLayout();
    main->addWidget(title);
    main->addLayout(form_layout);

    setLayout(main);

    //![4]
    connect(m_retour, &QPushButton::clicked, this, &exemplaireWidget::accept);
    connect(m_ajouter, &QPushButton::clicked, this, &exemplaireWidget::ajouter_exemplaire);

}

void exemplaireWidget::ajouter_exemplaire(){

//        QSqlQuery query;
//        query.prepare("INSERT INTO exemplaire (id_livre)"
//                      "VALUES(:nom, :prenom, :classe, :matricule)");
//        query.bindValue(":nom", (inscrit.getNom()).toString().toUpper());
//        query.bindValue(":prenom", (inscrit.getPrenom()).toString().toUpper());
//        query.bindValue(":classe", (inscrit.getClasse()).toString().toUpper());
//        query.bindValue(":matricule", (inscrit.getMatricule()).toString().toUpper());
//        query.exec();
//        hide();

}
