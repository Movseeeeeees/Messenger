#include "Headers/Registration.h"
#include <QWidget>
#include <QLabel>
#include <QMessageBox>
#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QtSql/QSql>
#include <QSqlDatabase>
#include <QFileDialog>
#include <QPixmap>
#include <QBuffer>
#include <QFileInfo>
#include "Headers/Login.h"

SecondWidget::SecondWidget( QWidget *parent) : QWidget(parent)
{
    Definedesign();
    Designinterface();
}

void SecondWidget::Definedesign()
{
    _name=new QLineEdit;
    _surname=new QLineEdit;
    _mail=new QLineEdit;
    _phone=new QLineEdit;
    _password=new QLineEdit;
    _passwordcheck=new QLineEdit;
    _create=new QPushButton(tr("Create new account"));
    _load = new QPushButton(tr("Load image"));
    _loginpage= new QPushButton(tr("Back to login page"));
    _name->setPlaceholderText("Name");
    _surname->setPlaceholderText("Surname");
    _mail->setPlaceholderText("Mail");
    _phone->setPlaceholderText("Phone");
    _password->setPlaceholderText("Password");
    _passwordcheck->setPlaceholderText("Password again");
    _password->setEchoMode(QLineEdit::Password);
    _passwordcheck->setEchoMode(QLineEdit::Password);
    _pixmap = new QPixmap("/home/movses/Desktop/Messenger/Messenger/Resources/registration.png");
    _labelpng = new QLabel;
    _labelpng->setPixmap(*_pixmap);
}

void SecondWidget::Designinterface()
{
    QGridLayout *Lay = new QGridLayout;
    Lay->addWidget(_labelpng,1,0);
    Lay->addWidget(_name,2,0);
    Lay->addWidget(_surname,3,0);
    Lay->addWidget(_mail,4,0);
    Lay->addWidget(_phone,5,0);
    Lay->addWidget(_create,9 ,0);
    Lay->addWidget(_load,8,0);
    Lay->addWidget(_loginpage,10,0);
    Lay->addWidget(_password,6,0);
    Lay->addWidget(_passwordcheck,7,0);
    setLayout(Lay);
    setWindowTitle(tr("Create account "));
}

void SecondWidget::Openmainwidget()
{
    this->hide();
    emit Mysignal();
}

SecondWidget::~SecondWidget()
{

}
