#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>

class database
{
    QSqlDatabase _db;
public:
    database();
    void _initialize_db();
    bool _performlogin(QString , QString);
    bool _activeateuser(QString);
    bool _deactivateuser(QString);

    bool _createuser(QString , QString , QString , QString , QString , QString , QByteArray);
    bool _checkmail(QString );
    bool _insertdata(QString name, QString surname, QString mail, QString phone , QString password,QString imagename , QByteArray fdtos);

};

#endif // DATABASE_H
