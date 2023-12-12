#include "Headers/registration.h"
#include <QWidget>
#include <QLabel>
#include <QMessageBox>
#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QtSql/QSql>
#include <QSqlDatabase>
#include <QCryptographicHash>
#include <QFileDialog>
#include <QPixmap>
#include <QBuffer>
#include <QFileInfo>
#include "Headers/login.h"

SecondWidget::SecondWidget( QWidget *parent) : QWidget(parent),db(Database::instance())
{
    _designinterface();
    _connect();
}

void SecondWidget::_definedesign()
{
    _name=new QLineEdit;
    _surname=new QLineEdit;
    _mail=new QLineEdit;
    _phone=new QLineEdit;
    _password=new QLineEdit;
    _password_check=new QLineEdit;
    _create=new QPushButton(tr("Create new account"));
    _load = new QPushButton(tr("Load image"));
    _login_page= new QPushButton(tr("Back to login page"));
    _name->setPlaceholderText("Name");
    _surname->setPlaceholderText("Surname");
    _mail->setPlaceholderText("Mail");
    _phone->setPlaceholderText("Phone");
    _password->setPlaceholderText("Password");
    _password_check->setPlaceholderText("Password again");
    _password->setEchoMode(QLineEdit::Password);
    _password_check->setEchoMode(QLineEdit::Password);
    _pixmap = new QPixmap("/home/movses/Desktop/Messenger/Messenger/Resources/registration.png");
    _label_png = new QLabel;
    _label_png->setPixmap(*_pixmap);
}

void SecondWidget::_designinterface()
{
    _definedesign();
    QGridLayout *Lay = new QGridLayout;
    Lay->addWidget(_label_png,1,0);
    Lay->addWidget(_name,2,0);
    Lay->addWidget(_surname,3,0);
    Lay->addWidget(_mail,4,0);
    Lay->addWidget(_phone,5,0);
    Lay->addWidget(_create,9 ,0);
    Lay->addWidget(_load,8,0);
    Lay->addWidget(_login_page,10,0);
    Lay->addWidget(_password,6,0);
    Lay->addWidget(_password_check,7,0);
    setLayout(Lay);
    setWindowTitle(tr("Create account "));
}

void SecondWidget::_connect()
{
    connect(_login_page,SIGNAL(clicked(bool)),this,SLOT(_openmainwidget()));
    connect(_login_page,&QPushButton::clicked,this,&SecondWidget::_openmainwidget);
    connect(_create,SIGNAL(clicked(bool)) , this,SLOT(_createaccount()));
    connect(_load,SIGNAL(clicked(bool)), this , SLOT(_loadimage()));

}

void SecondWidget::_createaccount()
{
    QString name_ = _name->text();
    QString surname_ = _surname->text();
    QString mail_ = _mail->text();
    QString phone_ = _phone->text();
    QString password_ = _hashpassword(_password ->text());
    if(_checkdata()){
        db._insertdata(name_,surname_,mail_,phone_,password_,_imagename,_fdtos);
        QMessageBox::information(this, "Info", "Succesfuly");
        close();
    }
}

bool SecondWidget::_checkdata()
{
    if(_name->text().size()<=2){
        QMessageBox::information(this, "info", "The length of the name must be more than 2 letters");
        return false;
    }
    if(_surname->text().size()<=2){
        QMessageBox::information(this, "info", "The length of the surname must be more than 2 letters");
        return false;
    }
    if(_mail->text().size()<=8){
        QMessageBox::information(this, "info", "The length of the mail must be more than 8 letters");
        return false;
    }
    if(_phone->text().size()<=8){
        QMessageBox::information(this, "info", "The length of the phone must be more than 8 letters");
        return false;
    }
    if(_password->text().size()<8){
        QMessageBox::information(this, "info", "The length of the password must be more than 7 letters");
        return false;
    }
    if(_password ->text()!= _password_check->text()){
        QMessageBox::information(this, "info", "Passwords are not same");
        return false;
    }
    QString mail=_mail->text();
    if(!db._checkmail(mail)){
        QMessageBox::information(this, "info", "Wrong email");
        return false;
    }
    return true;
}

QString SecondWidget::_hashpassword(const QString &password)
{
    QByteArray passwordBytes = password.toUtf8();
    QByteArray hashBytes = QCryptographicHash::hash(passwordBytes, QCryptographicHash::Sha256);
    return QString(hashBytes.toHex());
}

void SecondWidget::_loadimage()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Choose"),"",tr("Images(*.png *.jpg *.jpeg *.bmp *.gif)"));
    QPixmap image(filename);
    QBuffer bufferdata;
    if(bufferdata.open(QIODevice::ReadWrite)){
        image.save(&bufferdata,"JPG");
    }
    _fdtos = bufferdata.buffer().toBase64();
    QFileInfo fileinfo(filename);
    _imagename = fileinfo.fileName();
}

void SecondWidget::_openmainwidget()
{
    this->hide();
    emit mysignal();
}

SecondWidget::~SecondWidget()
{

}
