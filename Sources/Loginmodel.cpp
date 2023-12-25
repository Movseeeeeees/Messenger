#include "Headers/Loginmodel.h"
#include <QCryptographicHash>

Loginmodel::Loginmodel(MainWidget &view):db(Database::instance()),_view(view)
{

}

QString Loginmodel::Hashpassword(const QString &password)
{
    QByteArray passwordBytes = password.toUtf8();
    QByteArray hashBytes = QCryptographicHash::hash(passwordBytes, QCryptographicHash::Sha256);
    return QString(hashBytes.toHex());
}

bool Loginmodel::PerformLogin(QString a, QString b)
{
    if(!_view.Get("log").isEmpty() and !_view.Get("pass").isEmpty()){
        if(db.Performlogin(a,Hashpassword(b))){
            emit Loginsuccessful();
            db.Activeateuser(_view.Get("log"));
            return true;
        }else{
            emit Loginfailed();
            return false;
        }
    }
    else{
        _view.Showsomething("Wrong");
        return false;
    }
}
