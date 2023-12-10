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
    Q_OBJECT

public:
    SecondWidget(QWidget *parent = nullptr);
    ~SecondWidget();
private:

    QLineEdit* _name;
    QLineEdit* _surname;
    QLineEdit* _mail;
    QLineEdit* _phone;
    QLineEdit* _password;
    QLineEdit* _password_check;
    QPixmap* _pixmap;
    QLabel* _label_png;
    QPushButton* _create;
    QPushButton* _load;
    QPushButton* _login_page;
    Database& db;
    QByteArray _fdtos;
    QString _imagename;

public slots:
    void _designinterface();
    void _definedesign();
    void _connect();
    QString _hashpassword(const QString &password);
    bool _checkdata();
    void _createaccount();
    void _loadimage();
    void _openmainwidget();
};

#endif // REGISTRATION_H
