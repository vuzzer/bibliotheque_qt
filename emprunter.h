#ifndef LOGIN_H
#define LOGIN_H


#include <QObject>
#include <QtWidgets>
#include <QWidget>
#include <QSqlRelationalTableModel>

class emprunter : public QDialog
{
    Q_OBJECT
public:
    emprunter(QWidget *parent = nullptr);
    void load_book_db();
     void textFilterChanged();
     public slots:
      void afficher_emprunt();
      void emprunter_livre();
      void rendre_livre();
      void effacer_champ();
private:

    QLineEdit *m_titre, *m_auteur, *m_identifiant_etu, *m_identifiant_livre;
    QLabel *m_exemplaire_livre ;
    QTableView *m_livreVue, *m_livreVue_emprunter;
    QComboBox *m_recherche;
    QLineEdit *m_searchBar;
    QDateEdit *m_dateInscription;
    QPushButton *m_annuler, *m_ajouter, *m_emprunter, *m_rendre, *m_retour, *m_afficher;
    QSqlRelationalTableModel *m_model, *m_model_emprunter;
    QDataWidgetMapper *m_mapper;
    QSortFilterProxyModel *m_proxyModel;
};

#endif // LOGIN_H
