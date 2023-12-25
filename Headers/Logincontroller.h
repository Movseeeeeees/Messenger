#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include <QObject>
#include "Headers/Loginmodel.h"
#include "Headers/Login.h"
#include "Headers/Logincontroller.h"
#include "Headers/Registration.h"
#include "Headers/Chatwidget.h"
#include "Headers/Chatmodel.h"
#include "Headers/Chatcontroller.h"
#include "Headers/Registrationmodel.h"
#include "Headers/Registrationcontroller.h"

class Logincontroller : public QObject
{
    Q_OBJECT
public:
    Logincontroller(Loginmodel &,MainWidget &);
    ~Logincontroller();
private slots:
    void Createaccountclicked();//opensecondwidget
    void Loginsuccessful();//openchatwidget
    void Loginfailed();
    void Openmainwidget();
    void Performlogin();
private:
    Loginmodel &_model;
    MainWidget &_view;
    SecondWidget *secondwidget;
    Registrationmodel *regmodel;
    Registrationcontroller *regcontroller;

    Chatwidget *chat;
    Chatmodel *chatmodel;
    Chatcontroller *chatcontroller;

};

#endif // LOGINCONTROLLER_H
