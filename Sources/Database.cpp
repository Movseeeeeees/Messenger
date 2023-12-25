#include "Headers/Database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDateTime>

Database::Database()
{
    _db = QSqlDatabase::addDatabase("QMYSQL");
    _db.setHostName("127.0.0.1");
    _db.setDatabaseName("my_database");
    _db.setUserName("hp");
    _db.setPassword("7777777");
    _db.setPort(3306);
}

Database& Database::instance()
{
    static Database instance;
    return instance;
}

bool Database::Performlogin(QString user, QString password)
{
    QSqlDatabase::database().transaction();
    _db.open();
    QSqlQuery query(_db);
    query.prepare("SELECT * FROM my_database.users WHERE mail = :username AND passwordh = :password");
    query.bindValue(":username", user);
    query.bindValue(":password", password);
    query.exec();
    if(query.next())
        {}
    else
    {
        qDebug() << "Login failed. Incorrect username or password.";
        qDebug() << "Error details: " << query.lastError();
        return false;
    }
    _db.close();
    QSqlDatabase::database().commit();
    return true;
}

bool Database::Activeateuser(QString mail)
{
    QSqlDatabase::database().transaction();
    _db.open();
    QSqlQuery query(_db);
    bool isActive = true;
    query.prepare("UPDATE my_database.users SET active = :active WHERE mail = :mail");
    query.bindValue(":active", isActive);
    query.bindValue(":mail", mail);
    if (query.exec()) {
        qDebug() << "User status updated successfully";
    }
    else {
        qDebug() << "Failed to update user status:" << query.lastError().text();
        return false;
    }
    _db.close();
    QSqlDatabase::database().commit();
    return true;
}

bool Database::Deactivateuser(QString mail)
{
    QSqlDatabase::database().transaction();
    _db.open();
    QSqlQuery query(_db);
    bool isActive = false;
    query.prepare("UPDATE my_database.users SET active = :active WHERE mail = :mail");
    query.bindValue(":active", isActive);
    query.bindValue(":mail", mail); // Provide the user ID for the specific user
    if (query.exec()) {
        qDebug() << "User status updated successfully";
    } else {
        qDebug() << "Failed to update user status:" << query.lastError().text();
        return false;
    }
    _db.close();
    QSqlDatabase::database().commit();
    return true;
}

bool Database::Createuser(QString name, QString surname, QString mail, QString phone , QString password,QString imagename , QByteArray fdtos)
{
    bool activ=false;
    QSqlDatabase::database().transaction();
    _db.open();
    QSqlQuery query(_db);
    query.prepare("INSERT INTO my_database.users (name,surname,mail,phone,passwordh,imagename,imagedata,active) VALUES (?,?,?,?,?,?,?,?);");
    query.bindValue(0, name);
    query.bindValue(1, surname);
    query.bindValue(2, mail);
    query.bindValue(3, phone);
    query.bindValue(4, password);
    query.bindValue(5, imagename);
    query.bindValue(6, fdtos);
    query.bindValue(7, activ);
    if (!query.exec()) {
        qDebug() << "Created"<<_db.lastError().text();
        _db.rollback();
    }
    if (query.numRowsAffected() > 0) {
        qDebug() << "User created successfully";
    }
    else {
        return false;
        qDebug() << "Failed to create user";
    }
    _db.close();
    QSqlDatabase::database().commit();
    return true;
}

bool Database::Checkmail(QString email)
{
    QSqlDatabase::database().transaction();
    _db.open();
    QString queryStr = "SELECT * FROM my_database.users WHERE mail = :email";
    QSqlQuery query(_db);
    query.prepare(queryStr);
    query.bindValue(":email", email);
    query.exec();
    if (query.next()) {
        qDebug()<< "Email exists in the Database";
        return false;
    }
    else {
        qDebug()<< "Email does not exist in the Database";
    }
    _db.close();
    return true;
}

bool Database::Insertdata(QString name, QString surname, QString mail, QString phone , QString password,QString imagename , QByteArray fdtos)
{
    bool activ=false;
    QSqlDatabase::database().transaction();
    _db.open();
    QSqlQuery query(_db);
    query.prepare("INSERT INTO my_database.users (name,surname,mail,phone,passwordh,imagename,imagedata,active) VALUES (?,?,?,?,?,?,?,?);");
    query.bindValue(0, name);
    query.bindValue(1, surname);
    query.bindValue(2, mail);
    query.bindValue(3, phone);
    query.bindValue(4, password);
    query.bindValue(5, imagename);
    query.bindValue(6, fdtos);
    query.bindValue(7, activ);
    if (!query.exec()) {
        qDebug() << "Created"<<_db.lastError().text();
        _db.rollback();
    }
    if (query.numRowsAffected() > 0) {
        qDebug() << "User created successfully";
    }
    else {
        qDebug() << "Failed to create user";
        return false;
    }
    _db.close();
    QSqlDatabase::database().commit();
    return true;
}

bool Database::Sendmessage(QString mail,QString tomail,QString text)
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString datetime = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");
    QString status="new";
    QSqlDatabase::database().transaction();
    _db.open();
    QSqlQuery query(_db);
    query.prepare("INSERT INTO my_database.messages (user1,user2,date,message,status) VALUES (?,?,?,?,?);");
    query.bindValue(0, mail);
    query.bindValue(1, tomail);
    query.bindValue(2, datetime);
    query.bindValue(3, text);
    query.bindValue(4, status);
    query.exec();
    _db.close();
    QSqlDatabase::database().commit();
    return true;
}

bool Database::Markmessagestatuseread(QString user1, QString user2)
{
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
        return false;
    }
    _db.close();
    QSqlDatabase::database().commit();
    return true;
}

QByteArray Database::Getimagefromdbquery(QString user )
{
    QByteArray image_data;
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
    return image_data;
}

bool Database::Checkonlineusers(QMap<QString,User> &map,QString _mail)
{
    QSqlDatabase::database().transaction();
    _db.open();
    QSqlQuery query(_db);
    if (query.exec("SELECT * FROM my_database.users WHERE active = '1';")) {
        map.clear();
        while (query.next()) {
            QString name = query.value(0).toString();
            QString surname = query.value(1).toString();
            QString mail = query.value(2).toString();
            QString phone = query.value(3).toString();
            if(mail!=_mail){
                map.insert(mail,User(name,surname,mail,phone));
            }
        }
    }
    else {
        qDebug() << "Query failed: " << query.lastError().text();
        return false;
    }
    _db.close();
    return true;
}

bool Database::Updatelistmessages(QTextBrowser *text, QString _mail, QString _to_mail)
{
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
            text->insertPlainText(textuser);
        }
        text->moveCursor(QTextCursor::End);
    }
    else {
        qDebug() << "Error executing query: " << query.lastError().text();
        return false;
    }
    _db.close();
    QSqlDatabase::database().commit();
    return true;
}

bool Database::Getusersfromdb(QMap<QString, User> &map,QListWidget *users_list, QString _mail)
{
    QSqlDatabase::database().transaction();
    _db.open();
    QSqlQuery query(_db);
    map.clear();
    users_list->clear();
    if (query.exec("SELECT * FROM my_database.users")) {
        while (query.next()) {
            QString name = query.value(0).toString();
            QString surname = query.value(1).toString();
            QString mail = query.value(2).toString();
            QString phone = query.value(3).toString();
            if(mail!=_mail){
                map.insert(mail,User(name,surname,mail,phone));
            }
        }
        QList<QString> keys = map.keys();
        for (int i = 0; i < keys.size(); ++i) {
            QListWidgetItem *item=new QListWidgetItem(keys.at(i));
            users_list->addItem(item);
        }
    }
    else {
        qDebug() << "Query failed: " << query.lastError().text();
        return false;
    }
    _db.close();
    return true;
}

bool Database::Checknewmessage(QListWidget *_users_list, QMap<QString, User> _map_all_users,QString _mail){
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
        return false;
    }
    _db.close();
    return true;
}
