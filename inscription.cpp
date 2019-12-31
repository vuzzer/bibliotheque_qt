#include "inscription.h"
#include "homepage.h"
#include "QtWidgets"
#include <QSqlQuery>
#include <etudiant.h>
#include <etudiantmanager.h>
#include <QSqlRecord>
#include <ajouterWidget.h>

//![0]
inscription::inscription(QWidget *parent)  : QDialog(parent)
{


    m_proxyModel = new QSortFilterProxyModel();
    //! [0]

    //m_filterWidget = new FilterWidget();
    //m_filterWidget->setText("Grace|Sports");

    //! [1]


    QVBoxLayout *main = new QVBoxLayout();
    //QHBoxLayout *layout_button = new QHBoxLayout();

    setMinimumSize(QSize(1000, 600));

    //Button to control the app
    QPushButton *valider=new QPushButton(tr("Valider"));
    QPushButton *retour = new QPushButton(tr("Retour"));

    QLabel *title = new QLabel(tr("Gestion Des inscriptions"));

    //PART FOR INSCRIPTION, DELETING AND UPDATE
    m_searchBar = new QLineEdit();

    QGroupBox *groupBoxRecherche = new QGroupBox(tr("Recherche"));
    QGroupBox *groupBoxListe = new QGroupBox(tr("Listes des Etudiants"));
    QFormLayout *form_search = new QFormLayout();
    QHBoxLayout *recherche_layout = new QHBoxLayout();
    QVBoxLayout *recherche_vlayout = new QVBoxLayout();
    QVBoxLayout *group_vlayout = new QVBoxLayout();
    //QVBoxLayout *layout_liste = new QVBoxLayout();
    QHBoxLayout *main_hlayout = new QHBoxLayout();

    //MANIPULATION OF DATA
    QVBoxLayout *vlayout = new QVBoxLayout();
    m_vue = new QTreeView();

    m_vue->setSortingEnabled(false);
    selection_db();

    m_proxyModel->setSourceModel(m_model);

    m_vue->setModel(m_model);
    m_vue->setColumnHidden(m_model->fieldIndex("id"), true);
    m_vue->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_vue->setSelectionMode(QAbstractItemView::SingleSelection);
    m_vue->setCurrentIndex(m_model->index(0,0));
    vlayout->addWidget(m_vue);
    groupBoxListe->setLayout(vlayout);

    //QCombox pour les inscriptions
    m_genre = new QComboBox();
    m_genre->addItem("M");
    m_genre->addItem("Mlle");

    //QCombox pour les recherches
    m_recherche = new QComboBox();
    m_recherche->addItem("Identifiant");
    m_recherche->addItem("Nom");
    m_recherche->addItem("Tout afficher");


    m_identifiant = new QLineEdit();
    m_identifiant->setReadOnly(true);
    m_identifiant->setPlaceholderText(tr("12"));

    m_dateInscription = new QDateEdit();

    m_number = new QLineEdit();
    m_number->setPlaceholderText(tr("01-01-01-01"));
    m_number->setInputMask("[99-99-99-99]");
    m_number->setDisabled(true);

    m_supprimer = new QPushButton(tr("Supprimer"));
    m_modifier = new QPushButton(tr("Modifier"));
    m_ajouter = new QPushButton(tr("Ajouter"));
    //QPushButton *bt_recherche = new QPushButton(tr("Recherche"));

    QGridLayout *grid = new QGridLayout();

    //m_formlayout = new QFormLayout();
    m_nom = new QLineEdit();
    m_nom->setPlaceholderText(tr("Nom"));
    m_niveau = new QLineEdit();
    m_niveau->setPlaceholderText(tr("Niveau"));
    m_prenom = new QLineEdit();
    m_prenom->setPlaceholderText(tr("Prenom"));
    m_matricule = new QLineEdit();
    m_matricule->setPlaceholderText(tr("Matricule"));

    //m_formlayout->addRow("Nom : ", m_nom);
    //m_formlayout->addRow("Prenom : ", m_prenom);
    //m_formlayout->addRow("Niveau", m_niveau);
    //m_formlayout->addRow("N° carte etudiant  : ", m_matricule);

    grid->addWidget(m_genre,0,0,1,4);
    grid->addWidget(m_identifiant,1,0,1,4);
    grid->addWidget(m_nom,2,0,1,4);
    grid->addWidget(m_prenom,3,0,1,4);
    grid->addWidget(m_niveau,4,0,1,4);
    grid->addWidget(m_matricule,5,0,1,4);
    grid->addWidget(m_dateInscription,6,0,1,4);
    grid->addWidget(m_number,7,0,1,4);
    grid->addWidget(m_supprimer,8,0);
    grid->addWidget(m_modifier,8,1);
    grid->addWidget(m_ajouter,8,3);
    //! [grid]

    form_search->addRow("Recherche par", m_searchBar);
    //recherche_layout->addWidget(m_searchBar);
    recherche_vlayout->addLayout(form_search);
    recherche_vlayout->addLayout(recherche_layout);

    groupBoxRecherche->setLayout(recherche_vlayout);

    //INSERTION OF GROUPBOX IN LAYOUT

    group_vlayout->addWidget(groupBoxRecherche);
    group_vlayout->addWidget(groupBoxListe);

    main_hlayout->addLayout(grid);
    main_hlayout->addLayout(group_vlayout);

    main->addWidget(title);
    main->addLayout(main_hlayout);

    //Bind data and QLineEdit
    m_mapper = new QDataWidgetMapper(this);
    m_mapper->setModel(m_model);
    m_mapper->addMapping(m_nom, m_model->fieldIndex("nom"));
    m_mapper->addMapping(m_prenom, m_model->fieldIndex("prenom"));
    m_mapper->addMapping(m_niveau, m_model->fieldIndex("classe"));
    m_mapper->addMapping(m_matricule, m_model->fieldIndex("matricule"));
    m_mapper->addMapping(m_identifiant, m_model->fieldIndex("id"));



    //layout_button->addWidget(retour);
    //layout_button->addWidget(valider);

    //main->addLayout(m_formlayout);
    //main->addLayout(layout_button);

    setLayout(main);

    //This instruction control the events of QDialog by creating an insertion to database
    connect(retour, SIGNAL(clicked()), this, SLOT(reject()));
    connect(valider, SIGNAL(clicked()), this, SLOT(accept()));
    connect(m_recherche, &QComboBox::currentTextChanged, this, &inscription::recherche_etudiant);
    connect(m_searchBar, &QLineEdit::textChanged, this, &inscription::textFilterChanged);
    connect(m_vue->selectionModel(),
            &QItemSelectionModel::currentRowChanged,
            m_mapper,
            &QDataWidgetMapper::setCurrentModelIndex
            );
    connect(m_modifier, &QPushButton::clicked, this, &inscription::submit);
    connect(m_supprimer, &QPushButton::clicked, this, &inscription::supprimer_etudiant);
    connect(m_ajouter, &QPushButton::clicked, this, &inscription::ajouter_etudiant);
    //connect(m_filterWidget, &QLineEdit::textChanged,this, &inscription::textFilterChanged);

    //connect(m_filterWidget, &FilterWidget::filterChanged, this, &inscription::textFilterChanged);

}

//![1]
void inscription::main_page(){

    setMinimumSize(QSize(1000, 600));

    //MAIN LAYOUT

    QLabel nom("Nom"), prenom("Prenom"), numero_carte("N° carte etudiant");
    QLineEdit e_nom, e_prenom, e_numero_carte;

    //
    QPushButton valider("Valider"), retour("Retour");

}

//![2]
void inscription::done(int r){

    QString nom = m_nom->text(), prenom= m_prenom->text(), niveau = m_niveau->text(), matricule = m_matricule->text();

    if(r == 1){
        //Fields to fill at inscription of a student
        /*
         * if event 'accepted' is activated in this case verify fields and enter data in database
        */
        if(nom.isEmpty() || prenom.isEmpty() || niveau.isEmpty() || matricule.isEmpty()){
            QMessageBox::critical(this, "Saisie incorrect", "Vous n'avez pas rempli au moins un champ");
        }
        else{

            insert(nom, prenom, niveau, matricule);
        }
       this->hide();
    }

    else{
        this->hide();
    }

}

//![3]
void inscription::selection_db(){
    QSqlQuery query("SELECT etudiant FROM sqlite_sequence"), info_etudiant("SELECT * FROM etudiant");
    //int compteur = 1;
    //int id = info_etudiant.record().indexOf("id");
    /*int nom = info_etudiant.record().indexOf("nom");
    int prenom = info_etudiant.record().indexOf("prenom");
    int classe = info_etudiant.record().indexOf("classe");
    int matricule = info_etudiant.record().indexOf("matricule");

    int etudiant = query.value(0).toInt();*///Le nombre de etudiant

    m_model = new QSqlRelationalTableModel(m_vue);
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    m_model->setTable("etudiant");

    m_model->setHeaderData(m_model->fieldIndex(("nom")),Qt::Horizontal,tr("Nom"));
    m_model->setHeaderData(m_model->fieldIndex(("prenom")),Qt::Horizontal,tr("Prenom"));
    m_model->setHeaderData(m_model->fieldIndex(("classe")),Qt::Horizontal,tr("Classe"));
    m_model->setHeaderData(m_model->fieldIndex(("matricule")),Qt::Horizontal,tr("Matricule"));

    // Populate the model:
    if (!m_model->select()) {
        return;
    }

}


//![4]
void inscription::recherche_etudiant(QString recherche){
    QString mot1("Tout afficher");
    if(recherche =="Tout afficher"){

    }
}

//![5]
void insert(QString nom, QString prenom, QString niveau, QString matricule){

   etudiant inscrit(nom, prenom, niveau, matricule);
   etudiantManager db;
   db.insertion_db(inscrit);
}

QVariant nb_etudiant(){
    QSqlQuery query("SELECT etudiant FROM sqlite_sequence");
    return query.value(0).toInt();
}


//![7]
void inscription::textFilterChanged(const QString &arg)
{
//    m_model->setTable("etudiant");
//    if(m_model->select()){
//     m_model->setFilter(arg);
//     m_vue->setModel(m_model);
//     m_vue->setColumnHidden(m_model->fieldIndex("id"), true);
//     m_vue->setSelectionBehavior(QAbstractItemView::SelectRows);
//     m_vue->setSelectionMode(QAbstractItemView::SingleSelection);
//    }
//    else{
//       QMessageBox::critical(this, "Saisie incorrect", "Vous n'avez pas rempli au moins un champ");
//    }

    QRegExp regExp(m_searchBar->text());
    m_proxyModel->setFilterRegExp(regExp);
    //m_proxyModel->setFilterRegExp(regExp);
    m_vue->setRootIsDecorated(false);
    m_vue->setAlternatingRowColors(true);
    m_proxyModel->setFilterKeyColumn(4);
    m_vue->setModel(m_proxyModel);
    m_vue->setSortingEnabled(false);
}

//![8]
void inscription::setSourceModel(QAbstractItemModel *model)
{
    m_proxyModel->setSourceModel(model);
    m_vue->setModel(model);
}

//![9]
void inscription::submit()
{
   m_model->database().transaction();
   if (m_model->submitAll()) {
       m_model->database().commit();
   } else {
       m_model->database().rollback();
       QMessageBox::warning(this, tr("Cached Table"),
                            tr("The database reported an error: %1")
                            .arg(m_model->lastError().text()));
   }
}

//![10]
void inscription::supprimer_etudiant(){
    QSqlQuery query;
    query.prepare("DELETE FROM etudiant WHERE id ='"+m_identifiant->text()+"'");
    query.exec();
}

//![11]
void inscription::ajouter_etudiant(){
    ajouterWidget *ajouter = new ajouterWidget(this);
    ajouter->exec();
}


//   connect(submitButton, &QPushButton::clicked, this, &TableEditor::submit);
//   connect(revertButton, &QPushButton::clicked,  model, &QSqlTableModel::revertAll);
//   connect(quitButton, &QPushButton::clicked, this, &TableEditor::close);
//}


