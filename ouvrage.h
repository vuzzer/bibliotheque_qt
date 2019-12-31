#ifndef OUVRAGE_H
#define OUVRAGE_H

#include <QObject>

class ouvrage : public QObject
{
    Q_OBJECT
public:
    explicit ouvrage(QObject *parent = nullptr);

signals:

public slots:
};

#endif // OUVRAGE_H
