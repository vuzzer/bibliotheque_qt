#ifndef ETUDIANTMANAGER_H
#define ETUDIANTMANAGER_H
#include <QSqlDatabase>
#include <etudiant.h>

class etudiantManager
{
public:
    etudiantManager();
    void insertion_db(etudiant& inscrit);
    void delete_db();
    etudiant select_db();
    void update_db();

private:
    QSqlDatabase m_db;
};

#endif // ETUDIANTMANAGER_H
