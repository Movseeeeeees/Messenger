#include "Headers/Registrationmodel.h"
#include <QCryptographicHash>

Registrationmodel::Registrationmodel( SecondWidget *view):db(Database::instance()),_view(view)
{

}

void Registrationmodel::Loadimage()
{

    QString filename = QFileDialog::getOpenFileName(_view,tr("Choose"),"",tr("Images(*.png *.jpg *.jpeg *.bmp *.gif)"));
    QPixmap image(filename);
    QBuffer bufferdata;
    if(bufferdata.open(QIODevice::ReadWrite)){
        image.save(&bufferdata,"JPG");
    }
    _fdtos = bufferdata.buffer().toBase64();
    QFileInfo fileinfo(filename);
    _imagename = fileinfo.fileName();
}


QString Registrationmodel::Hashpassword(const QString &password)
{
    QByteArray passwordBytes = password.toUtf8();
    QByteArray hashBytes = QCryptographicHash::hash(passwordBytes, QCryptographicHash::Sha256);
    return QString(hashBytes.toHex());
}


bool Registrationmodel::Checkdata()
{

    if(_view->_name->text().size()<=2){
        QMessageBox::information(_view, "info", "The length of the name must be more than 2 letters");
        return false;
    }
    if(_view->_surname->text().size()<=2){
        QMessageBox::information(_view, "info", "The length of the surname must be more than 2 letters");
        return false;
    }
    if(_view->_mail->text().size()<=8){
        QMessageBox::information(_view, "info", "The length of the mail must be more than 8 letters");
        return false;
    }
    if(_view->_phone->text().size()<=8){
        QMessageBox::information(_view, "info", "The length of the phone must be more than 8 letters");
        return false;
    }
    if(_view->_password->text().size()<8){
        QMessageBox::information(_view, "info", "The length of the password must be more than 7 letters");
        return false;
    }
    if(_view->_password ->text()!= _view->_passwordcheck->text()){
        QMessageBox::information(_view, "info", "Passwords are not same");
        return false;
    }
    QString mail=_view->_mail->text();
    if(!db.Checkmail(mail)){
        QMessageBox::information(_view, "info", "Wrong email");
        return false;
    }
    return true;
}

void Registrationmodel::Createaccount()
{
    QString name_ = _view->_name->text();
    QString surname_ = _view->_surname->text();
    QString mail_ = _view->_mail->text();
    QString phone_ = _view->_phone->text();
    QString password_ = Hashpassword(_view->_password ->text());
    if(Checkdata()){
        db.Insertdata(name_,surname_,mail_,phone_,password_,_imagename,_fdtos);
        QMessageBox::information(_view, "Info", "Succesfuly");
        _view->close();
    }

}
