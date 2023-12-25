#ifndef CHATMODEL_H
#define CHATMODEL_H
#include <QObject>
#include "Headers/Chatwidget.h"
#include "Headers/Database.h"

class Chatmodel : public QObject
{
    Q_OBJECT
    Database& db;
    Chatwidget *_view;
    QString _to_mail=NULL;
    QString _mail;
    QPixmap *_image;

    QMap<QString,User> _mapactiveusers;
    QMap<QString,User> _mapallusers;
public:
    Chatmodel(Chatwidget *, QString);
public slots:
    void Logout();
    void Connectwithuser();
    void Connectwithuserfromonline();
    void Updatelistmessages();
    void Showactiveusers();
    void Getusersfromdb();
    void Checknewmessage();
    void Sendmessage();
};

#endif // CHATMODEL_H
