#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QMap>
#include "Headers/User.h"
#include <QTextBrowser>
#include <QListWidget>
#include <QList>

class Database
{
    QSqlDatabase _db;
public:
    Database();
    static Database& instance();
    bool Performlogin(QString , QString);
    bool Activeateuser(QString);
    bool Deactivateuser(QString);
    bool Markmessagestatuseread(QString, QString);
    bool Sendmessage(QString , QString, QString);
    bool Createuser(QString , QString , QString , QString , QString , QString , QByteArray);
    bool Checkmail(QString );
    bool Insertdata(QString , QString , QString , QString , QString ,QString , QByteArray );
    bool Checkonlineusers(QMap<QString,User> & ,QString);
    bool Updatelistmessages(QTextBrowser * , QString , QString);
    bool Getusersfromdb(QMap<QString,User> &,QListWidget*,QString);
    bool Checknewmessage(QListWidget*,QMap<QString,User>,QString);
    QByteArray Getimagefromdbquery(QString);
};

#endif // DATABASE_H
