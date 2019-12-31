#ifndef INSCRIPTION_H
#define INSCRIPTION_H

#include <QtWidgets>
#include <QWidget>
#include <QtSql>
#include "ajouterWidget.h"
#include "livreWidget.h"



class inscription : public QDialog
{

public:
     inscription(QWidget *parent = nullptr);

     /*
      * fonction initialise l'attribut m_model avec les données de la db
      *
    */
     void selection_db();
    void setSourceModel(QAbstractItemModel *model);
signals:

public slots:
    void done(int r)override;
    void recherche_etudiant(QString recherche);
    void textFilterChanged(const QString &arg);
    void dateFilterChanged();
    void submit();
    void ajouter_etudiant();
    void supprimer_etudiant();

private:
    QFormLayout *m_formlayout;
    QSqlRelationalTableModel *m_model;
    QTreeView *m_vue;
    QComboBox *m_genre, *m_recherche;
    QLineEdit *m_searchBar, *m_niveau, *m_nom, *m_prenom, *m_matricule, *m_identifiant, *m_number;
    QDateEdit *m_dateInscription;
    QPushButton *m_supprimer, *m_ajouter, *m_modifier;
    QDataWidgetMapper *m_mapper;
    //FilterWidget *m_filterWidget;
    QSortFilterProxyModel *m_proxyModel;
    void main_page();

    static QString nb_etudiant;
};

void insert(QString nom, QString prenom, QString niveau, QString matricle);
void connection();
QVariant nb_etudiant();

#endif // INSCRIPTION_H
