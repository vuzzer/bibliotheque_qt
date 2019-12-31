#include "livre.h"
#include "livreWidget.h"
#include <QtWidgets>
#include <QMessageBox>
#include <QSqlQuery>


livre::livre(QWidget *parent) : QDialog(parent)
    {
        m_proxyModel = new QSortFilterProxyModel();

        setMinimumSize(QSize(1000, 600));
        //Title of window
        QLabel *title = new QLabel(tr("Gestion Des Oeuvres Et Exemplaires"));
        title->setFont(QFont("Times", 15, QFont::DemiBold));

        //![QPushButton]
        m_ajouter = new QPushButton(tr("Ajouter"));
        //m_afficher = new QPushButton(tr("Afficher"));
        m_modifier = new QPushButton(tr("Modifier"));
        m_supprimer = new QPushButton(tr("Supprimer"));
        m_exemplaire = new QPushButton(tr("Exemplaire"));
        m_retour = new QPushButton(tr("Retour"));
        m_searchBar = new QLineEdit();

        //![QLineEdit]
        m_identifiant = new QLineEdit();
        m_identifiant->setReadOnly(true);
        //m_identifiant->setPlaceholderText(nb_etudiant);
        m_auteur = new QLineEdit();
        m_auteur->setPlaceholderText(tr("Auteur"));
        m_titre = new QLineEdit();
        m_titre->setPlaceholderText(tr("Titre"));
        m_reservation = new QLineEdit();
        m_Btexemplaire = new QLineEdit();

        QGridLayout *grid_lineEdit = new QGridLayout();
        grid_lineEdit->addWidget(m_identifiant,0,0,1,4);
        grid_lineEdit->addWidget(m_auteur,1,0,1,4);
        grid_lineEdit->addWidget(m_titre,2,0,1,4);
        grid_lineEdit->addWidget(m_Btexemplaire,3,0,1,4);
        grid_lineEdit->addWidget(m_reservation,4,0,1,4);
        grid_lineEdit->addWidget(m_supprimer,5,0);
        grid_lineEdit->addWidget(m_modifier,5,1);
        grid_lineEdit->addWidget(m_ajouter,5,2);


        //![grid]
        QGridLayout *grid = new QGridLayout();

        grid->addWidget(m_exemplaire,2,0,1,4);
        grid->addWidget(m_retour,3,0,1,4);

        //Groupbox recherche
        QVBoxLayout *main = new QVBoxLayout();//Contient tous les elements de ma fenetre
        QFormLayout *form_search = new QFormLayout();
        QVBoxLayout *recherche_layout = new QVBoxLayout();
        //QVBoxLayout *recherche_vlayout = new QVBoxLayout();
        //QPushButton *bt_recherche = new QPushButton(tr("Recherche"));
        QGroupBox *groupBoxRecherche = new QGroupBox(tr("Recherche des livres"));
        QGroupBox *groupBoxListe = new QGroupBox(tr("Liste des livres"));
        QVBoxLayout *group_vlayout = new QVBoxLayout();//Contient la barre de recherche et le bouton recherche
        QHBoxLayout *main_hlayout = new QHBoxLayout();//Contient les boutons de fonction(ajouter, supprimer, ...) et le groupbox recherche

        form_search->addRow("Recherche", m_searchBar);
        //recherche_layout->addWidget(bt_recherche);
        //recherche_vlayout->addLayout(form_search);
        //recherche_vlayout->addLayout(recherche_layout);

        recherche_layout->addLayout(form_search);
        groupBoxRecherche->setLayout(recherche_layout);


        //MANIPULATION OF DATA
        QVBoxLayout *vlayout = new QVBoxLayout();
        m_vue = new QTableView();
        livre_db();

        m_proxyModel->setSourceModel(m_model);

        m_vue->setModel(m_model);

        m_vue->horizontalHeader()->setSectionResizeMode(m_model->fieldIndex("titre"),QHeaderView::ResizeToContents);
        m_vue->horizontalHeader()->setSectionResizeMode(m_model->fieldIndex("id_auteur"),QHeaderView::ResizeToContents);
        m_vue->setColumnHidden(m_model->fieldIndex("id"), true);
        m_vue->setSelectionBehavior(QAbstractItemView::SelectRows);
        m_vue->setSelectionMode(QAbstractItemView::SingleSelection);
        vlayout->addWidget(m_vue);
        groupBoxListe->setLayout(vlayout);

        //Layout pour les groupbox recherche et liste
        group_vlayout->addWidget(groupBoxRecherche);
        group_vlayout->addWidget(groupBoxListe);

        //Layout contenent les fonctions ajouter, supprimer ... et les groupbox
        main_hlayout->addLayout(grid);
        main_hlayout->addLayout(group_vlayout);
        main_hlayout->addLayout(grid_lineEdit);

        main->addWidget(title);
        main->addLayout(main_hlayout); 

        //![mapper]
        m_mapper = new QDataWidgetMapper(this);
        m_mapper->setModel(m_model);

        m_mapper->addMapping(m_titre, m_model->fieldIndex("titre"));
        m_mapper->addMapping(m_auteur, m_model->fieldIndex("id_auteur"));
        m_mapper->addMapping(m_reservation, m_model->fieldIndex("reservation"));
        m_mapper->addMapping(m_Btexemplaire, m_model->fieldIndex("exemplaire"));
        m_mapper->addMapping(m_identifiant, m_model->fieldIndex("id"));

        setLayout(main);
        
        //! [connect]
        connect(m_searchBar, &QLineEdit::textChanged, this, &livre::textFilterChanged);
        connect(m_exemplaire, &QPushButton::clicked, this, &livre::ajouter_exemplaire);
        connect(m_ajouter, &QPushButton::clicked, this, &livre::add_livre);
        connect(m_modifier, &QPushButton::clicked, this, &livre::modifier_livre);
        connect(m_retour, &QPushButton::clicked, this, &livre::accept);
        connect(m_supprimer, &QPushButton::clicked, this, &livre::supprimer_livre);
        connect(m_vue->selectionModel(),
                &QItemSelectionModel::currentRowChanged,
                m_mapper,
                &QDataWidgetMapper::setCurrentModelIndex
                );

        m_vue->setCurrentIndex(m_model->index(0,0));

    }

//! [1]
void livre::livre_db(){

    m_model = new QSqlRelationalTableModel(m_vue);
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    m_model->setTable("oeuvre");

    m_model->setHeaderData(m_model->fieldIndex(("titre")),Qt::Horizontal,tr("Titre"));
    m_model->setHeaderData(m_model->fieldIndex(("id_auteur")),Qt::Horizontal,tr("Auteur"));
    m_model->setHeaderData(m_model->fieldIndex(("exemplaire")),Qt::Horizontal,tr("Exemplaire"));
    m_model->setHeaderData(m_model->fieldIndex(("reservation")),Qt::Horizontal,tr("Reservation"));

    // Populate the model:
    if (!m_model->select()) {
        return;
    }
}

//! [2]
void livre::textFilterChanged(){
    QRegExp regExp(m_searchBar->text());
    m_proxyModel->setFilterRegExp(regExp);
    //m_proxyModel->setFilterRegExp(regExp);
    //m_vue->setRootIsDecorated(false);
    m_vue->setAlternatingRowColors(true);
    m_proxyModel->setFilterKeyColumn(1);
    m_vue->setModel(m_proxyModel);
    m_vue->setSortingEnabled(false);
}

void livre::add_livre(){
    livreWidget *ajouter = new livreWidget();
    ajouter->exec();
}

void livre::modifier_livre(){
    m_model->database().transaction();
    if (m_model->submitAll()) {
        m_model->database().commit();
    } else {
        m_model->database().rollback();
        QMessageBox::warning(this, tr("Cached Table"),tr("The database reported an error: %1"));
    }
}

void livre::supprimer_livre(){
    QSqlQuery query;
    query.prepare("DELETE FROM etudiant WHERE id ='"+m_identifiant->text()+"'");
    query.exec();
}

void livre::ajouter_exemplaire(){

}


