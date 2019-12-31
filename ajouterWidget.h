#ifndef FILTERWIDGET_H
#define FILTERWIDGET_H


#include <QDialog>
#include <QRegExp>
#include <QtWidgets>

class ajouterWidget : public QDialog
{
public:
  ajouterWidget(QWidget *parent = nullptr);

public slots:
  void ajouter_etudiant();

private:
   QLineEdit *m_searchBar, *m_niveau, *m_nom, *m_prenom, *m_matricule, *m_identifiant;
   QPushButton *m_retour, *m_ajouter;
};

#endif // FILTERWIDGET_H
