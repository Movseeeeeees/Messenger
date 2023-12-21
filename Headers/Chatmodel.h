#ifndef CHATMODEL_H
#define CHATMODEL_H
#include <QObject>
#include "Headers/chatwidget.h"
#include "Headers/database.h"

class Chatmodel : public QObject
{
    Q_OBJECT
    Database& db;
    chatwidget *_view;
    QString _to_mail=NULL;
    QString _mail;
    QPixmap *_image;

    QMap<QString,User> _mapactiveusers;
    QMap<QString,User> _mapallusers;
public:
    Chatmodel(chatwidget *view , QString);
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
