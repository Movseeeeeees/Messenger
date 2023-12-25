#ifndef LOGINMODEL_H
#define LOGINMODEL_H

#include <QString>
#include "Headers/Database.h"
#include <Headers/Login.h>
#include <QObject>

class Loginmodel:public QObject
{
    Q_OBJECT
    Database& db;
    MainWidget& _view;
public:
    Loginmodel(MainWidget &);
    QString Hashpassword(const QString &);
    bool PerformLogin(QString,QString);
signals:
    void Loginsuccessful();
    void Loginfailed();
};

#endif // LOGINMODEL_H
