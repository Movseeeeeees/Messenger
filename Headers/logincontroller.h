#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include <QObject>
#include "Headers/loginmodel.h"
#include "Headers/login.h"
#include "Headers/logincontroller.h"
#include "Headers/registration.h"
#include "Headers/chatwidget.h"
#include "Headers/Chatmodel.h"
#include "Headers/Chatcontroller.h"
#include "Headers/registrationmodel.h"
#include "Headers/Registrationcontroller.h"

class Logincontroller : public QObject
{
    Q_OBJECT
public:
    Logincontroller(Loginmodel &model,MainWidget &view);
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

    chatwidget *chat;
    Chatmodel *chatmodel;
    Chatcontroller *chatcontroller;

};

#endif // LOGINCONTROLLER_H
