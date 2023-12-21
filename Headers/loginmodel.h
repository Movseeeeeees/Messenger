#ifndef LOGINMODEL_H
#define LOGINMODEL_H

#include <QString>
#include "Headers/database.h"
#include <Headers/login.h>
#include <QObject>

class Loginmodel:public QObject
{
    Q_OBJECT
    Database& db;
    MainWidget& _view;
public:
    Loginmodel(MainWidget &view);
    QString Hashpassword(const QString &password);
    bool PerformLogin(QString,QString);
signals:
    void Loginsuccessful();
    void Loginfailed();
};

#endif // LOGINMODEL_H
