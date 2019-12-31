#include "etudiant.h"

etudiant::etudiant(QString nom, QString prenom, QString classe, QString matricule): m_nom(nom), m_prenom(prenom), m_classe(classe), m_matricule(matricule)
{

}

QVariant etudiant::getNom() const{
    return  m_nom;
}

QVariant etudiant::getPrenom() const{
    return  m_prenom;
}

QVariant etudiant::getClasse() const{
    return  m_classe;
}

QVariant etudiant::getMatricule() const{
    return  m_matricule;
}
