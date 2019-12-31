#ifndef MYSORTFILTER_H
#define MYSORTFILTER_H

#include <QSqlRelationalTableModel>
#include <QDate>
#include <QtWidgets>

//! [0]
class livreWidget : public QDialog
{
    Q_OBJECT

public:
    livreWidget();
    livreWidget(QDataWidgetMapper *mapper, QModelIndex *model);

public slots:
  void ajouter_livre();

private:
   QLineEdit *m_titre, *m_auteur, *m_identifiant, *m_reservation, *m_exemplaire;
   QPushButton *m_retour, *m_ajouter;
   QDataWidgetMapper *m_mapper;
   QSqlRelationalTableModel *m_model;
   QSortFilterProxyModel *m_proxyModel;
};
#endif // MYSORTFILTER_H
