#ifndef USER_H
#define USER_H

#include <QString>
#include <QMap>

class User
{
    QString name;
    QString surname;
    QString mail;
    QString phone;
    QString image;
    QString imagedata;
public:
    User(QString n, QString s, QString m , QString p);
};

#endif // USER_H
