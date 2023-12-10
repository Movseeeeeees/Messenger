#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QMap>
#include "Headers/user.h"
#include <QTextBrowser>
#include <QListWidget>
#include <QList>

class Database
{
    QSqlDatabase _db;
public:
    Database();
    static Database& instance();
    bool _performlogin(QString , QString);
    bool _activeateuser(QString);
    bool _deactivateuser(QString);
    bool _markmessagestatuseread(QString, QString);
    bool _sendmessage(QString , QString, QString);
    bool _createuser(QString , QString , QString , QString , QString , QString , QByteArray);
    bool _checkmail(QString );
    bool _insertdata(QString , QString , QString , QString , QString ,QString , QByteArray );
    bool _checkonlineusers(QMap<QString,User> &map ,QString);
    bool _updatelistmessages(QTextBrowser *text , QString , QString);
    bool _getusersfromdb(QMap<QString,User> &map,QListWidget*,QString);
    bool _checknewmessage(QListWidget*,QMap<QString,User>,QString);
    QByteArray _getimagefromdbquery(QString);
};

#endif // DATABASE_H
