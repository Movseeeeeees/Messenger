#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include <QPixmap>
#include <QSqlDatabase>

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

    QSqlDatabase _db;
    QByteArray _fdtos;
    QString _imagename;

public slots:
    void _initialize_db();
    void _designinterface();
    void _definedesign();
    void _connect();

    bool _checkmail();
    QString _hashpassword(const QString &password);
    void _insertdata(QString name,QString surname,QString mail,QString phone ,QString password ,QString imagename, QByteArray fdtos);
    bool _checkdata();
    void _createaccount();
    void _loadimage();
    void _openmainwidget();
};

#endif // REGISTRATION_H
