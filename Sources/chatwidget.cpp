#include <QWidget>
#include "Headers/chatwidget.h"
#include "Headers/login.h"
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

chatwidget::chatwidget(const QString &user, QWidget *parent):QWidget(parent),db(Database::instance())
{
    _setuser(user);
    _designinterface();
    _getusersfromdb();
    _connect();
    _showactiveusers();
}

void chatwidget::_designinterface()
{
    _designinterfacefirsthbox();
    _designinterfaceusersgroupbox();
    _designinterfacecommunicategroupbox();
    //list of users
    QWidget *user_list_w=new QWidget;
    _l=new QHBoxLayout;
    _users_list=new QListWidget;
    _l->addWidget(_users_list);
    user_list_w->setLayout(_l);
    //end
    //set design
    _all=new QVBoxLayout(this);
    _all->addWidget(_status);
    _all->addWidget(_activ_users);
    _all->addWidget(user_list_w);
    setLayout(_all);
    setWindowTitle(tr("Messenger"));
}

void chatwidget::_designinterfacefirsthbox()
{
    _status = new QWidget;
    _logout = new QPushButton(tr("Log out"));
    _username = new QLabel(_mail);
    QHBoxLayout *hbox_up = new QHBoxLayout;
    hbox_up->addWidget(_getimagefromdb(_mail));
    hbox_up->addWidget(_username);
    hbox_up->addWidget(_logout);
    _status->setLayout(hbox_up);
}

void chatwidget::_designinterfaceusersgroupbox()
{
    _activ_users= new QGroupBox(tr("Active users"));
    _activ_users->setFixedHeight(100);
    _group_lay_active = new QHBoxLayout;
    _activ_users->setLayout(_group_lay_active);
    _active_users_list = new QListWidget;
    _group_lay_active->addWidget(_active_users_list);
}

void chatwidget::_designinterfacecommunicategroupbox()
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
    _group_lay_communicate= new QVBoxLayout;
    _group_lay_communicate->addWidget(_text);
    _group_lay_communicate->addWidget(w);
    _communicate->setLayout(_group_lay_communicate);
}

void chatwidget::_connect()
{
    connect(_logout,SIGNAL(clicked(bool)),this,SLOT(_deactivate()));
    connect(_send,SIGNAL(clicked(bool)),this,SLOT(_sendmessage()));
    connect(_users_list,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(_connectwithuser()));
    connect(_active_users_list,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(_connectwithuserfromonline()));
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(_updatelistmessages()));
    connect(timer,SIGNAL(timeout()),this,SLOT(_getusersfromdb()));
    connect(timer,SIGNAL(timeout()),this,SLOT(_checkonlineusers()));
    connect(timer,SIGNAL(timeout()),this,SLOT(_checknewmessage()));
    timer->start(2000);
}

void chatwidget::_connectwithuser()
{
    _l->addWidget(_communicate);
    _to_mail=_users_list->currentItem()->text();
    _updatelistmessages();
    _users_list->currentItem()->setBackground(Qt::color0);
    db._markmessagestatuseread(_to_mail,_mail);
}

void chatwidget::_connectwithuserfromonline()
{
    _l->addWidget(_communicate);
    _to_mail=_active_users_list->currentItem()->text();
    _updatelistmessages();
    db._markmessagestatuseread(_to_mail,_mail);
}

void chatwidget::_checkonlineusers()
{
    db._checkonlineusers(_map_active_users,_mail);
    _showactiveusers();
}

void chatwidget::_deactivate()
{
    db._deactivateuser(_mail);
    this->close();
}

void chatwidget::_showactiveusers()
{
    QMapIterator<QString,User> i(_map_active_users);
    _active_users_list->clear();
    while(i.hasNext()){
        i.next();
        QString labelText = i.key();
        _active_users_list->addItem(labelText);
    }
}

void chatwidget::_setuser(const QString &user)
{
    _mail=user;
}

void chatwidget::_sendmessage()
{
    if(!_message->text().isEmpty() and _to_mail != ""){
        QString textuser=QString("%1 : %2 \n").arg(_mail).arg(_message->text());
        _text->insertPlainText(textuser);
        _text->moveCursor(QTextCursor::End);
        db._sendmessage(_mail,_to_mail,_message->text());
        _message->clear();
    }
}

void chatwidget::_updatelistmessages()
{
    if(_to_mail != ""){
        _text->clear();
        db._updatelistmessages(_text,_mail,_to_mail);
    }
}

void chatwidget::_getimagefromdbquery(QString user)
{
    _image = new QPixmap("/home/movses/Desktop/Messenger/Messenger/Resources/user.png");
    QByteArray image_data;
    image_data=db._getimagefromdbquery(user);
    if(!image_data.isEmpty()){
        _image->loadFromData(image_data,"JPG");
    }
}

QLabel* chatwidget::_getimagefromdb(QString user)
{
    _getimagefromdbquery(user);
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

void chatwidget::_getusersfromdb()
{
    db._getusersfromdb(_map_all_users,_users_list,_mail);
 }

void chatwidget::_checknewmessage()
{
    db._checknewmessage(_users_list,_map_all_users,_mail);
}
