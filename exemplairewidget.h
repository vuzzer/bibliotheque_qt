#ifndef EXEMPLAIREWIDGET_H
#define EXEMPLAIREWIDGET_H

#include <QDialog>
#include <QRegExp>
#include <QtWidgets>

class exemplaireWidget : public QDialog
{
public:
    exemplaireWidget(QWidget *parent = nullptr);

public slots:
  void ajouter_exemplaire();

private:
   QLineEdit *m_searchBar, *m_niveau, *m_nom, *m_prenom, *m_matricule, *m_identifiant_livre;
   QPushButton *m_retour, *m_ajouter;
   QComboBox *m_etat;
};

#endif // EXEMPLAIREWIDGET_H
