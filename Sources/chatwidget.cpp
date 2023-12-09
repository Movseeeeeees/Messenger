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

chatwidget::chatwidget(const QString &user, QWidget *parent):QWidget(parent){
    qDebug() << "2";
    _setuser(user);
    _initialize_db();
    _designinterface();
    _getusersfromdb();
    _connect();
    _showactiveusers();
}

void chatwidget::_initialize_db(){
    _db = QSqlDatabase::addDatabase("QMYSQL");
    _db.setHostName("127.0.0.1");
    _db.setDatabaseName("my_database");
    _db.setUserName("hp");
    _db.setPassword("7777777");
    _db.setPort(3306);
}

void chatwidget::_designinterface(){
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

void chatwidget::_designinterfacefirsthbox(){
    _status = new QWidget;
    _logout = new QPushButton(tr("Log out"));
    _username = new QLabel(_mail);
    QHBoxLayout *hbox_up = new QHBoxLayout;
    hbox_up->addWidget(_getimagefromdb(_mail));
    hbox_up->addWidget(_username);
    hbox_up->addWidget(_logout);
    _status->setLayout(hbox_up);
}

void chatwidget::_designinterfaceusersgroupbox(){
    _activ_users= new QGroupBox(tr("Active users"));
    _activ_users->setFixedHeight(100);
    _group_lay_active = new QHBoxLayout;
    _activ_users->setLayout(_group_lay_active);
    _active_users_list = new QListWidget;
    _group_lay_active->addWidget(_active_users_list);
}

void chatwidget::_designinterfacecommunicategroupbox(){
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

void chatwidget::_connect(){
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

void chatwidget::_connectwithuser(){
    _l->addWidget(_communicate);
    _to_mail=_users_list->currentItem()->text();
    _updatelistmessages();
    _users_list->currentItem()->setBackground(Qt::color0);
    _markmessagesstatuseread(_to_mail,_mail);
}

void chatwidget::_connectwithuserfromonline(){
    _l->addWidget(_communicate);
    _to_mail=_active_users_list->currentItem()->text();
    _updatelistmessages();
    _markmessagesstatuseread(_to_mail,_mail);
}

void chatwidget::_checkonlineusers(){
    QSqlDatabase::database().transaction();
    _db.open();
    QSqlQuery query(_db);
    if (query.exec("SELECT * FROM my_database.users WHERE active = '1';")) {
        _map_active_users.clear();
        while (query.next()) {
            QString name = query.value(0).toString();
            QString surname = query.value(1).toString();
            QString mail = query.value(2).toString();
            QString phone = query.value(3).toString();
            if(mail!=this->_mail){
                _map_active_users.insert(mail,User(name,surname,mail,phone));
            }
        }
    }
    else {
        qDebug() << "Query failed: " << query.lastError().text();
    }
    _db.close();
    _showactiveusers();
}

void chatwidget::_deactivate(){
    QSqlDatabase::database().transaction();
    _db.open();
    QSqlQuery query(_db);
    bool isActive = 0;
    query.prepare("UPDATE my_database.users SET active = :active WHERE mail = :mail");
    query.bindValue(":active", isActive);
    query.bindValue(":mail", _mail);
    if (query.exec()) {
        qDebug() << "User status updated successfully";
    }
    else {
        qDebug() << "Failed to update user status:" << query.lastError().text();
    }
    _db.close();
    QSqlDatabase::database().commit();
    this->close();
}

void chatwidget::_showactiveusers(){
    QMapIterator<QString,User> i(_map_active_users);
    _active_users_list->clear();
    while(i.hasNext()){
        i.next();
        QString labelText = i.key();
        _active_users_list->addItem(labelText);
    }
}

void chatwidget::_setuser(const QString &user){
    _mail=user;
}

void chatwidget::_sendmessage(){
    if(!_message->text().isEmpty() and _to_mail != ""){
        QString textuser=QString("%1 : %2 \n").arg(_mail).arg(_message->text());
        _text->insertPlainText(textuser);
        _text->moveCursor(QTextCursor::End);
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QString datetime = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");
        QString status="new";
        QSqlDatabase::database().transaction();
        _db.open();
        QSqlQuery query(_db);
        query.prepare("INSERT INTO my_database.messages (user1,user2,date,message,status) VALUES (?,?,?,?,?);");
        query.bindValue(0, _mail);
        query.bindValue(1, _to_mail);
        query.bindValue(2, datetime);
        query.bindValue(3, _message->text());
        query.bindValue(4, status);
        query.exec();
        _db.close();
        QSqlDatabase::database().commit();
        _message->clear();
    }
}

void chatwidget::_updatelistmessages(){
    if(_to_mail != ""){
        _text->clear();
        QSqlDatabase::database().transaction();
        _db.open();
        QSqlQuery query;
        query.prepare("SELECT * FROM my_database.messages WHERE (user1=:mail or user1=:to_mail) and (user2=:to_mail or user2=:mail)");
        query.bindValue(":mail",_mail);
        query.bindValue(":to_mail",_to_mail);
        if (query.exec()) {
            while (query.next()) {
                QString user = query.value("user1").toString();
                QString message = query.value("message").toString();
                QString textuser = QString("%1 : %2 \n").arg(user).arg(message);
                _text->insertPlainText(textuser);
            }
            _text->moveCursor(QTextCursor::End);
        }
        else {
            qDebug() << "Error executing query: " << query.lastError().text();
        }
        _db.close();
        QSqlDatabase::database().commit();
    }
}

void chatwidget::_getimagefromdbquery(QString user){
    QByteArray image_data;
    _image = new QPixmap("/home/movses/QT_messenger/Resources/user.png");
    QString image_name;
    QSqlDatabase::database().transaction();
    _db.open();
    QSqlQuery query(_db);
    query.prepare("SELECT * FROM my_database.users WHERE mail=:user");
    query.bindValue(":user",user);
    if(query.exec()){
        if(query.next()){
            image_name=query.value("imagename").toString();
            image_data=QByteArray::fromBase64(query.value("imagedata").toByteArray());
        }
    }
    else{
        qDebug() << "Error executing query: " << query.lastError().text();
    }
    _db.close();
    QSqlDatabase::database().commit();
    if(!image_data.isEmpty()){
        _image->loadFromData(image_data,"JPG");
    }
}

QLabel* chatwidget::_getimagefromdb(QString user){
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

void chatwidget::_getusersfromdb(){
    QSqlDatabase::database().transaction();
    _db.open();
    QSqlQuery query(_db);
    _map_all_users.clear();
    _users_list->clear();
    if (query.exec("SELECT * FROM my_database.users")) {
        while (query.next()) {
            QString name = query.value(0).toString();
            QString surname = query.value(1).toString();
            QString mail = query.value(2).toString();
            QString phone = query.value(3).toString();
            if(mail!=this->_mail){
                _map_all_users.insert(mail,User(name,surname,mail,phone));
            }
        }
        QList<QString> keys = _map_all_users.keys();
        for (int i = 0; i < keys.size(); ++i) {
            QListWidgetItem *item=new QListWidgetItem(keys.at(i));
            _users_list->addItem(item);
        }
    }
    else {
        qDebug() << "Query failed: " << query.lastError().text();
    }
    _db.close();
}

void chatwidget::_checknewmessage(){
    QSqlDatabase::database().transaction();
    _db.open();
    QSqlQuery query(_db);
    QString user="new";
    query.exec("SELECT * FROM my_database.messages WHERE (user2=?) AND (status=?)");
    query.bindValue(0,_mail);
    query.bindValue(1,user);
    if(query.exec()){
        while (query.next()) {
            QString from = query.value(0).toString();
            int index = _map_all_users.keys().indexOf(from);
            _users_list->item(index)->setBackground(Qt::yellow);
        }
    }
    else {
        qDebug() << "Query failed: " << query.lastError().text();
    }
    _db.close();
}

void chatwidget::_markmessagesstatuseread(QString user1, QString user2){
    QSqlDatabase::database().transaction();
    _db.open();
    QSqlQuery query(_db);
    QString status="Readed";
    query.prepare("UPDATE my_database.messages SET status = :status WHERE user1 = :user1 and user2=:user2");
    query.bindValue(":status", status);
    query.bindValue(":user1",user1);
    query.bindValue(":user2", user2);
    if (query.exec()) {
        qDebug() << "Messages status updated successfully";
    }
    else {
        qDebug() << "Failed to update messages status:" << query.lastError().text();
    }
    _db.close();
    QSqlDatabase::database().commit();
}
