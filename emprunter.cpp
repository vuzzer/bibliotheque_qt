#include "emprunter.h"
#include <QSql>
#include <QSqlQuery>
#include <QSqlRecord>

emprunter::emprunter(QWidget *parent) : QDialog(parent)
{
    m_proxyModel = new QSortFilterProxyModel();

    setMinimumSize(QSize(1000, 600));
    //Title of window
    QLabel *title = new QLabel(tr("Gestion Des Emprunts Des Oeuvres"));
    title->setFont(QFont("Times", 15, QFont::DemiBold));

    //![QPushButton]
    //m_ajouter = new QPushButton(tr("Ajouter"));
    //m_afficher = new QPushButton(tr("Afficher"));
    m_emprunter = new QPushButton(tr("Emprunter"));
    m_annuler = new QPushButton(tr("Annuler"));
    m_rendre = new QPushButton(tr("Rendre"));
    m_retour = new QPushButton(tr("Retour"));


    //![QLineEdit]
     m_searchBar = new QLineEdit();
    //m_identifiant_etu = new QLineEdit();
    //m_identifiant_etu->setReadOnly(true);
    //m_identifiant->setPlaceholderText(nb_etudiant);
    //m_auteur = new QLineEdit();
    //m_auteur->setPlaceholderText(tr("Auteur"));
    //m_titre = new QLineEdit();
    //m_titre->setPlaceholderText(tr("Titre"));
    //m_reservation = new QLineEdit();
    m_identifiant_livre = new QLineEdit();
    m_identifiant_livre->setPlaceholderText(tr("Identifiant livre"));
    m_identifiant_etu = new QLineEdit();
    m_identifiant_etu->setPlaceholderText(tr("Matricule"));
    m_exemplaire_livre = new QLabel(tr("exemplaire nulle pour l'instant pour chaque oeuvre"));
    m_exemplaire_livre->setStyleSheet("color:blue");
    m_exemplaire_livre->setAlignment(Qt::AlignCenter);

    //![grid] 1&2
    QGridLayout *grid_lineEdit = new QGridLayout();
    grid_lineEdit->addWidget(m_identifiant_livre,0,0,1,4);
    grid_lineEdit->addWidget(m_identifiant_etu,1,0,1,4);
    grid_lineEdit->addWidget(m_emprunter,2,0);
    grid_lineEdit->addWidget(m_annuler,2,1);

    QGridLayout *grid = new QGridLayout();
    grid->addWidget(m_rendre,2,0,1,4);
    grid->addWidget(m_retour,3,0,1,4);

    //Groupbox recherche
    QVBoxLayout *main = new QVBoxLayout();//Contient tous les elements de ma fenetre
    QFormLayout *form_search = new QFormLayout();
    QVBoxLayout *recherche_layout = new QVBoxLayout();
    //QVBoxLayout *recherche_vlayout = new QVBoxLayout();
    //QPushButton *bt_recherche = new QPushButton(tr("Recherche"));
    QGroupBox *groupBoxRecherche = new QGroupBox(tr("Recherche des livres"));
    QGroupBox *groupBoxListe = new QGroupBox(tr("Liste des livres"));
    QHBoxLayout *horizontal_layout_vue = new QHBoxLayout();
    QGroupBox *groupBoxEmprunt = new QGroupBox(tr("Liste des emprunts"));
    QVBoxLayout *group_vlayout = new QVBoxLayout();//Contient la barre de recherche et le bouton recherche
    QHBoxLayout *main_hlayout = new QHBoxLayout();//Contient les boutons de fonction(ajouter, supprimer, ...) et le groupbox recherche

    form_search->addRow("Recherche par", m_searchBar);
    //recherche_layout->addWidget(bt_recherche);
    //recherche_vlayout->addLayout(form_search);
    //recherche_vlayout->addLayout(recherche_layout);


    QVBoxLayout *liste_layout = new QVBoxLayout();
    QVBoxLayout *emprunt_layout = new QVBoxLayout();
    recherche_layout->addLayout(form_search);
    groupBoxRecherche->setLayout(recherche_layout);


    //MANIPULATION OF VUE FOR DISPLAYING DATA FROM DB

    m_livreVue = new QTableView();
    m_livreVue_emprunter = new QTableView();

    //METHOD THAT INITIALISE THE OBJECT QSRELATIONALTABLEMODEL
    load_book_db();

     m_livreVue->setModel(m_model);

     m_livreVue->horizontalHeader()->setSectionResizeMode(m_model->fieldIndex("id"),QHeaderView::ResizeToContents);
     m_livreVue->horizontalHeader()->setSectionResizeMode(m_model->fieldIndex("titre"),QHeaderView::ResizeToContents);
     m_livreVue->setColumnHidden(m_model->fieldIndex("id_auteur"), true);
     m_livreVue->setColumnHidden(m_model->fieldIndex("exemplaire"), true);
     m_livreVue->setColumnHidden(m_model->fieldIndex("reservation"), true);
     m_livreVue->setSelectionBehavior(QAbstractItemView::SelectRows);
     m_livreVue->setSelectionMode(QAbstractItemView::SingleSelection);


//    m_livreVue_emprunter->horizontalHeader()->setSectionResizeMode(m_model->fieldIndex("titre"),QHeaderView::ResizeToContents);
//    m_livreVue_emprunter->horizontalHeader()->setSectionResizeMode(m_model->fieldIndex("titre"),QHeaderView::ResizeToContents);


    liste_layout->addWidget(m_livreVue);
    groupBoxListe->setLayout(liste_layout);
    emprunt_layout->addWidget(m_livreVue_emprunter);
    groupBoxEmprunt->setLayout(emprunt_layout);

    //Layout pour les groupbox recherche et liste
    horizontal_layout_vue->addWidget(groupBoxListe);
    horizontal_layout_vue->addWidget(groupBoxEmprunt);

    group_vlayout->addWidget(groupBoxRecherche);
    group_vlayout->addLayout(horizontal_layout_vue);
    group_vlayout->addWidget(m_exemplaire_livre);

    //Layout contenent les fonctions ajouter, supprimer ... et les groupbox
    main_hlayout->addLayout(grid);
    main_hlayout->addLayout(group_vlayout);
    main_hlayout->addLayout(grid_lineEdit);

    //INSERTION IN THE MAIN PAGE OF WINDOW
    main->addWidget(title);
    main->addLayout(main_hlayout);

    //![mapper]
//    m_mapper = new QDataWidgetMapper(this);
//    m_mapper->setModel(m_model);

//    m_mapper->addMapping(m_titre, m_model->fieldIndex("titre"));
//    m_mapper->addMapping(m_auteur, m_model->fieldIndex("auteur"));
//    m_mapper->addMapping(m_reservation, m_model->fieldIndex("reservation"));
//    m_mapper->addMapping(m_Btexemplaire, m_model->fieldIndex("exemplaire"));
//    m_mapper->addMapping(m_identifiant, m_model->fieldIndex("id"));

    setLayout(main);

    //! [connect]
      connect(m_searchBar, &QLineEdit::textChanged, this, &emprunter::textFilterChanged);
//    connect(m_ajouter, &QPushButton::clicked, this, &livre::add_livre);
//    connect(m_modifier, &QPushButton::clicked, this, &livre::modifier_livre);
//    connect(m_retour, &QPushButton::clicked, this, &livre::accept);
//    connect(m_supprimer, &QPushButton::clicked, this, &livre::supprimer_livre);
    connect(m_livreVue->selectionModel(), &QItemSelectionModel::currentRowChanged,this,&emprunter::afficher_emprunt);
    connect(m_retour, &QPushButton::clicked, this, &emprunter::accept);
    connect(m_emprunter, &QPushButton::clicked, this, &emprunter::emprunter_livre);
    connect(m_rendre, &QPushButton::clicked, this, &emprunter::rendre_livre);
    connect(m_annuler, &QPushButton::clicked, this, &emprunter::effacer_champ);
//    m_vue->setCurrentIndex(m_model->index(0,0));

}

//![1]
void emprunter::load_book_db(){
    m_model = new QSqlRelationalTableModel(m_livreVue);
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    m_model->setTable("oeuvre");

    m_model->setHeaderData(m_model->fieldIndex(("titre")),Qt::Horizontal,tr("Titre"));
    m_model->setHeaderData(m_model->fieldIndex(("id")),Qt::Horizontal,tr("Identifiant"));


  m_model_emprunter = new QSqlRelationalTableModel(m_livreVue_emprunter);
  m_model_emprunter->setEditStrategy(QSqlTableModel::OnManualSubmit);
  m_model_emprunter->setTable("emprunter");
  m_model_emprunter->setHeaderData(m_model_emprunter->fieldIndex(("id_livre")),Qt::Horizontal,tr("Id livre"));
  m_model_emprunter->setHeaderData(m_model_emprunter->fieldIndex(("id_etudiant")),Qt::Horizontal,tr("Id etudiant"));

    // Populate the model:
    if (!m_model->select() and !m_model_emprunter->select()) {
        return;
    }
}

//![2]
void emprunter::textFilterChanged(){
    QRegExp regExp(m_searchBar->text());
    m_proxyModel->setSourceModel(m_model);
    m_proxyModel->setFilterRegExp(regExp);
    //m_proxyModel->setFilterRegExp(regExp);
    //m_vue->setRootIsDecorated(false);
    m_livreVue->setAlternatingRowColors(true);
    m_proxyModel->setFilterKeyColumn(1);
    m_livreVue->setModel(m_proxyModel);
    m_livreVue->setSortingEnabled(false);
    m_livreVue->update();
}

//![3]
void emprunter::afficher_emprunt(){

    QItemSelectionModel *selection = m_livreVue->selectionModel();
    QModelIndex indexElementSelectionne = selection->currentIndex();
    QVariant elementSelectionne = m_model->data(indexElementSelectionne,
    Qt::DisplayRole);
    QString data(elementSelectionne.toString().toLower());

    //EXECUTION OF REQUEST FROM DATABASE
    QSqlQuery query;
    query.prepare("SELECT id FROM oeuvre WHERE titre=:m_titre");
    query.bindValue(":m_titre", data);
    query.exec();

    if(query.next()){

        //    int fieldNo = query.record().indexOf("id");
            QString id = query.value(0).toString();

//            QMessageBox::information(this, "Elément sélectionné",
//            elementSelectionne.toString());
//            qDebug()<<id;

//            QSqlQuery qry;
//            qry.prepare("SELECT * FROM emprunter WHERE id_livre=:m_livre");
//            qry.bindValue(":m_livre", data);
//            qry.exec();
//            int fieldNo = query.record().indexOf("id_livre");
//            int field = query.record().indexOf("id_etudiant");
//            int i=0;

//            QStandardItemModel *modele = new QStandardItemModel(1,2);
//            while (qry.next()) {
//                modele->setItem(i,0, new QStandardItem(query.value(fieldNo).toString()));
//                modele->setItem(i,1, new QStandardItem(query.value(field).toString()));
//                i++;
//            }
            m_livreVue_emprunter->setModel(m_model_emprunter);
            m_model_emprunter->setFilter("id_livre='"+id+"'");
            m_model_emprunter->select();
            m_livreVue_emprunter->horizontalHeader()->setSectionResizeMode(m_model_emprunter->fieldIndex("id_livre"),QHeaderView::ResizeToContents);
            m_livreVue_emprunter->horizontalHeader()->setSectionResizeMode(m_model_emprunter->fieldIndex("id_etudiant"),QHeaderView::ResizeToContents);
            m_livreVue_emprunter->setSelectionBehavior(QAbstractItemView::SelectRows);
            m_livreVue_emprunter->setSelectionMode(QAbstractItemView::SingleSelection);

//            model->setFilter("id_livre = 1");
//            if(model->select()){
//                m_livreVue_emprunter->horizontalHeader()->setSectionResizeMode(model->fieldIndex("id_livre"),QHeaderView::ResizeToContents);
//                m_livreVue_emprunter->horizontalHeader()->setSectionResizeMode(model->fieldIndex("id_etudiant"),QHeaderView::ResizeToContents);
//                m_livreVue_emprunter->setSelectionBehavior(QAbstractItemView::SelectRows);
//                m_livreVue_emprunter->setSelectionMode(QAbstractItemView::SingleSelection);
//            }
    }

}

void emprunter::emprunter_livre(){
    QString id_livre(m_identifiant_livre->text().toLower());
    QString matricule_etudiant(m_identifiant_etu->text());

    QSqlQuery requete;
    requete.prepare("SELECT id FROM etudiant WHERE matricule = :mat");
        requete.bindValue(":mat", matricule_etudiant);
    requete.exec();
    if(requete.next())
    {
        int id_etudiant = requete.value(0).toInt();
        requete.prepare("SELECT id_etudiant FROM "
                        " emprunter WHERE id_etudiant = :id_etu");
            requete.bindValue(":id_etu", id_etudiant);

        requete.exec();

        if(requete.next()){// a deja emprunter
        QMessageBox::information(this,"Warning","Vous avez déjà emprunter un livre,\n veuillez retournez le livre pour un autre emprunt.");
        }

        else{// n'a pas enecore emprunter lelivre
            QSqlQuery query;
            query.prepare("INSERT INTO emprunter (id_livre, id_etudiant)"
                          "VALUES(:id_livre, :id_etudiant)");
            query.bindValue(":id_livre", m_identifiant_livre->text().toLower());
            query.bindValue(":id_etudiant", id_etudiant);
            query.exec();
            QMessageBox::information(this,"info","Emprunt reussie");
        }
    }
    else{//etudiant n'est pas membre

        QMessageBox::information(this,"Warning","Ce etudiant n'est pas inscrit à le biblipthèque,\n veuillez vous inscrire avant tout emprunt d'un livre");
    }



}


void emprunter::rendre_livre(){

    QItemSelectionModel *selection = m_livreVue_emprunter->selectionModel();
    QModelIndex indexElementSelectionne = selection->currentIndex();
    QVariant elementSelectionne = m_model_emprunter->data(indexElementSelectionne,Qt::DisplayRole);
    QString emprunt(elementSelectionne.toString().toLower());

    QSqlQuery query;
    query.prepare("DELETE FROM emprunter WHERE id_etudiant ='"+emprunt+"'");
    query.exec();

    QMessageBox::information(this,"element selectionné", "Le livre emprunté a été retourné avec succès");


}

void emprunter::effacer_champ(){
    m_identifiant_etu->clear();
    m_identifiant_livre->clear();
}
