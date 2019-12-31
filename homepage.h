#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include "inscription.h"

class homepage : public QDialog
{
Q_OBJECT
public:
    homepage(QWidget *parent = nullptr);

signals:
    void inscription();
public slots:
    void click_inscription();
    void click_ouvrage();
    void click_emprunter();

private:
    class inscription *page_inscription;
    QVBoxLayout *main_vlayout;
    QHBoxLayout *center_hlayout;
    void main_page();
    void inscription_page();
};

void connection_db();

#endif // HOMEPAGE_H
