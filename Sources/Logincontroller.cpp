#include "Headers/Logincontroller.h"
#include "Headers/Registration.h"
#include "Headers/Chatwidget.h"
#include "Headers/Registrationmodel.h"
#include "Headers/Registrationcontroller.h"
#include <QBuffer>
#include <QFileInfo>
#include <QFileDialog>
#include <QTime>
#include <QEventLoop>

Logincontroller::Logincontroller(Loginmodel &model, MainWidget &view):_model(model),_view(view)
{
    connect(_view._buttonlogin,SIGNAL(clicked(bool)),this,SLOT(Performlogin()));
    connect(_view._buttonnew,&QPushButton::clicked,this,&Logincontroller::Createaccountclicked);
    connect(&_model,&Loginmodel::Loginsuccessful,this,&Logincontroller::Loginsuccessful);
    connect(&_model,&Loginmodel::Loginfailed,this,&Logincontroller::Loginfailed);

    secondwidget = new SecondWidget;
    regmodel = new Registrationmodel(secondwidget);
    regcontroller = new Registrationcontroller(regmodel,secondwidget);
    connect(secondwidget,&SecondWidget::Mysignal,this,&Logincontroller::Openmainwidget);
}

void Logincontroller::Createaccountclicked()
{
    //mvc
    secondwidget->show();
    _view.hide();
}

void Logincontroller::Loginsuccessful()
{
    chat = new Chatwidget(_view.Get("log"),nullptr);
    chat->resize(600,700);
    chat->show();
    chatmodel = new Chatmodel(chat,_view.Get("log"));
    chatcontroller = new Chatcontroller(chatmodel,chat);
    _view.hide();
}

void Logincontroller::Loginfailed()
{
    _view.Showsomething("Login failed. Incorrect username or password.");
}

void Logincontroller::Openmainwidget()
{
    _view.show();
}

void Logincontroller::Performlogin()
{
    _model.PerformLogin(_view.Get("log"),_view.Get("pass"));
}

Logincontroller::~Logincontroller(){
    //qDebug()<<"login controller end";
}
