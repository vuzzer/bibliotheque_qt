#ifndef ADMINLOGIN_H
#define ADMINLOGIN_H

#include <QWidget>
#include <QLabel>
#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>

class adminLogin : public QWidget
{
Q_OBJECT
public:
    adminLogin(QWidget *parent=nullptr);
signals:

public slots:
    void openMain();

private:
    QLabel *m_title, *m_messageError;
    QFormLayout *m_form;
    QPushButton *m_connexion;
    QLineEdit *m_admin, *m_password;

    static QString password , admin;
};

#endif // ADMINLOGIN_H
