#ifndef EMPRUNT_H
#define EMPRUNT_H

#include <QObject>
#include <QtWidgets>
#include <QWidget>
#include <QSqlRelationalTableModel>
/*
 *
*/
class livre : public QDialog
{
    Q_OBJECT
public:
    livre(QWidget *parent=nullptr);
    void livre_db();
signals:

public slots:
    void textFilterChanged();
    void add_livre();
    void modifier_livre();
    void supprimer_livre();
    void ajouter_exemplaire();
private:
    QLineEdit *m_titre, *m_auteur, *m_identifiant, *m_reservation, *m_Btexemplaire;
    QTableView *m_vue;
    QComboBox *m_recherche;
    QLineEdit *m_searchBar;
    QDateEdit *m_dateInscription;
    QPushButton *m_supprimer, *m_ajouter, *m_modifier, *m_exemplaire, *m_retour, *m_afficher;
    QSqlRelationalTableModel *m_model;
    QDataWidgetMapper *m_mapper;
    QSortFilterProxyModel *m_proxyModel;
};

#endif // EMPRUNT_H
