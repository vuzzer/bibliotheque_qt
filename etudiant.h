#ifndef ETUDIANT_H
#define ETUDIANT_H

#include <QString>
#include <QVariant>

class etudiant
{
public:
    etudiant(QString m_nom, QString prenom, QString classe, QString matricule);
    QVariant getNom() const;
    QVariant getPrenom() const;
    QVariant getClasse() const;
    QVariant getMatricule() const;

private:
    QString m_nom, m_prenom, m_classe, m_matricule;
};

#endif // ETUDIANT_H
