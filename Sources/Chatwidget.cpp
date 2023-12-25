#include <QWidget>
#include "Headers/Chatwidget.h"
#include "Headers/Login.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QMenu>
#include <QMainWindow>
#include <QAction>
#include <QSqlQuery>
#include <QSqlError>
#include <QLabel>
#include <QDateTime>
#include <QTimer>
#include <QUrl>
#include <QBitmap>
#include <QPainter>
#include <QListWidget>
#include <QListWidgetItem>
#include <QCheckBox>

Chatwidget::Chatwidget(const QString &user, QWidget *parent):QWidget(parent),db(Database::instance())
{
    Setuser(user);
    Designinterfacefirsthbox();
    Designinterfaceusersgroupbox();
    Designinterfacecommunicategroupbox();
    Designinterface();

}

void Chatwidget::Designinterface()
{
    //list of users
    QWidget *userlistw=new QWidget;
    _l=new QHBoxLayout;
    _userslist=new QListWidget;
    _l->addWidget(_userslist);
    userlistw->setLayout(_l);
    //end
    //set design
    _all=new QVBoxLayout(this);
    _all->addWidget(_status);
    _all->addWidget(_activusers);
    _all->addWidget(userlistw);
    setLayout(_all);
    setWindowTitle(tr("Messenger"));
}

void Chatwidget::Designinterfacefirsthbox()
{
    _status = new QWidget;
    _logout = new QPushButton(tr("Log out"));
    _username = new QLabel(_mail);
    QHBoxLayout *hboxup = new QHBoxLayout;
    hboxup->addWidget(Getimagefromdb(_mail));
    hboxup->addWidget(_username);
    hboxup->addWidget(_logout);
    _status->setLayout(hboxup);
}

void Chatwidget::Designinterfaceusersgroupbox()
{
    _activusers= new QGroupBox(tr("Active users"));
    _activusers->setFixedHeight(100);
    _grouplayactive = new QHBoxLayout;
    _activusers->setLayout(_grouplayactive);
    _activeuserslist = new QListWidget;
    _grouplayactive->addWidget(_activeuserslist);
}

void Chatwidget::Designinterfacecommunicategroupbox()
{
    _communicate= new QGroupBox(tr("Area"));
    _message = new QLineEdit;
    _message->setPlaceholderText("Message");
    _send= new QPushButton(tr("Send"));
    QWidget *w=new QWidget;
    QHBoxLayout *hbox=new QHBoxLayout;
    hbox->addWidget(_message);
    hbox->addWidget(_send);
    w->setLayout(hbox);
    _text = new QTextBrowser;
    _grouplaycommunicate= new QVBoxLayout;
    _grouplaycommunicate->addWidget(_text);
    _grouplaycommunicate->addWidget(w);
    _communicate->setLayout(_grouplaycommunicate);
}

void Chatwidget::Setuser(const QString &user)
{
    _mail=user;
}

QLabel* Chatwidget::Getimagefromdb(QString user)
{
    _image = new QPixmap("/home/movses/Desktop/Messenger/Messenger/Resources/user.png");
    QByteArray image_data;
    image_data=db.Getimagefromdbquery(user);
    if(!image_data.isEmpty()){
        _image->loadFromData(image_data,"JPG");
    }
    *_image = _image->scaled(100,100,Qt::KeepAspectRatio);
    QLabel *label_png = new QLabel;
    label_png->setPixmap(*_image);
    QBitmap mask(_image->size());
    mask.fill(Qt::color0);
    QPainter painter(&mask);
    painter.setBrush(Qt::color1);
    painter.drawEllipse(0,0,_image->width(),_image->width());
    label_png->setMask(mask);
    label_png->setFixedSize(100,100);
    return label_png;
}
