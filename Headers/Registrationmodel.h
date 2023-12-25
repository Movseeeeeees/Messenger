#ifndef REGISTRATIONMODEL_H
#define REGISTRATIONMODEL_H

#include <QObject>
#include "Headers/Database.h"
#include "Headers/Registration.h"
#include <QBuffer>
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>

class Registrationmodel : public QObject
{
    Q_OBJECT
    Database& db;
    SecondWidget *_view;
    QByteArray _fdtos;
    QString _imagename;

public:
    Registrationmodel(SecondWidget *);
public slots:
    void Loadimage();
    QString Hashpassword(const QString &);
    bool Checkdata();
    void Createaccount();
private slots:
};


#endif // REGISTRATIONMODEL_H
