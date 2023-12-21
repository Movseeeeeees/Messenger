#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include <QPixmap>
#include <QSqlDatabase>
#include "Headers/database.h"

class SecondWidget : public QWidget
{
    friend class Registrationmodel;
    friend class Registrationcontroller;
    Q_OBJECT
public:
    SecondWidget(QWidget *parent = nullptr);
    ~SecondWidget();
private:
    QPushButton* _create;
    QPushButton* _load;
    QPushButton* _loginpage;
    QLineEdit* _name;
    QLineEdit* _surname;
    QLineEdit* _mail;
    QLineEdit* _phone;
    QLineEdit* _password;
    QLineEdit* _passwordcheck;
    QPixmap* _pixmap;
    QLabel* _labelpng;
public slots:
    void Designinterface();
    void Definedesign();
    void Openmainwidget();
signals:
    void Mysignal();
};

#endif // REGISTRATION_H
