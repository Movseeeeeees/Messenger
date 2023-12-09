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

    bool authenticateuser(const QString &email, const QString &password) const;
    bool activateuser(QString);
    bool deactivateuser(QString );

    void adduser(const User &user);
    bool userexists(const QString &email) const;
    User getuser(const QString &email) const;
private:
    QMap<QString,User> users;
};

#endif // USER_H
