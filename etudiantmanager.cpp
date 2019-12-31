#include "etudiantmanager.h"
#include <QSqlQuery>
#include <QDebug>
/*
 * Constructor create the connection with the database
*/
etudiantManager::etudiantManager()
{

}

void etudiantManager::insertion_db(etudiant& inscrit){
    QSqlQuery query;
    query.prepare("INSERT INTO etudiant (nom, prenom, classe, matricule)"
                  "VALUES(:nom, :prenom, :classe, :matricule)");
    query.bindValue(":nom", (inscrit.getNom()).toString().toUpper());
    query.bindValue(":prenom", (inscrit.getPrenom()).toString().toUpper());
    query.bindValue(":classe", (inscrit.getClasse()).toString().toUpper());
    query.bindValue(":matricule", (inscrit.getMatricule()).toString().toUpper());
    query.exec();
}
