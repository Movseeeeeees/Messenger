#include "Headers/database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

database::database()
{

}

void database::_initialize_db(){
    _db = QSqlDatabase::addDatabase("QMYSQL");
    _db.setHostName("127.0.0.1");
    _db.setDatabaseName("my_database");
    _db.setUserName("hp");
    _db.setPassword("7777777");
    _db.setPort(3306);
}

bool database::_performlogin(QString user, QString password){

        QSqlDatabase::database().transaction();
        _db.open();
        QSqlQuery query(_db);
        query.prepare("SELECT * FROM my_database.users WHERE mail = :username AND passwordh = :password");
        query.bindValue(":username", user);
        query.bindValue(":password", password);
        query.exec();
        if(query.next()) {
            return true;
            /*qDebug() << "Login successful";
            _activateuser(_line_log->text());
            _openchatwidget();
            _main->hide();
            this->setVisible(false);*/
        }
        else{
            //QMessageBox::information(this, "Info", "Login failed. Incorrect username or password.");
            qDebug() << "Login failed. Incorrect username or password.";
            qDebug() << "Error details: " << query.lastError();
            return false;
        }
        _db.close();
        QSqlDatabase::database().commit();
}

bool database::_activeateuser(QString mail){
    QSqlDatabase::database().transaction();
    _db.open();
    QSqlQuery query(_db);
    bool isActive = true;
    query.prepare("UPDATE my_database.users SET active = :active WHERE mail = :mail");
    query.bindValue(":active", isActive);
    query.bindValue(":mail", mail);
    if (query.exec()) {
        qDebug() << "User status updated successfully";
            return true;
    }
    else {
        qDebug() << "Failed to update user status:" << query.lastError().text();
            return false;
    }
    _db.close();
    QSqlDatabase::database().commit();
}

bool database::_deactivateuser(QString mail){
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
    }
    _db.close();
    QSqlDatabase::database().commit();
}

bool database::_createuser(QString name, QString surname, QString mail, QString phone , QString password,QString imagename , QByteArray fdtos){
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
        return true;
    }
    else {
        qDebug() << "Failed to create user";
    }
    _db.close();
    QSqlDatabase::database().commit();
}

bool database::_checkmail(QString email){
    QSqlDatabase::database().transaction();
    _db.open();
    QString queryStr = "SELECT * FROM my_database.users WHERE mail = :email";
    QSqlQuery query(_db);
    query.prepare(queryStr);
    query.bindValue(":email", email);
    query.exec();
    if (query.next()) {
        qDebug() << "Email exists in the database";
        //QMessageBox::information(this, "info", "Wrong email");
        return false;
    }
    else {
        qDebug() << "Email does not exist in the database";
    }
    _db.close();
    return true;
}

bool database::_insertdata(QString name, QString surname, QString mail, QString phone , QString password,QString imagename , QByteArray fdtos){
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
        return true;
    }
    else {
        qDebug() << "Failed to create user";
        return false;
    }
    _db.close();
    QSqlDatabase::database().commit();
}

