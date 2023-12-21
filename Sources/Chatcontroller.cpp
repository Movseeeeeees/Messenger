
#include "Headers/Chatcontroller.h"
#include <QTimer>

Chatcontroller::Chatcontroller(Chatmodel *model, chatwidget *view):_view(view),_model(model)
{
    connect(_view->_logout,&QPushButton::clicked,_model,&Chatmodel::Logout);
    connect(_view->_userslist,&QListWidget::doubleClicked,_model,&Chatmodel::Connectwithuser);
    connect(_view->_activeuserslist,&QListWidget::doubleClicked,_model,&Chatmodel::Connectwithuserfromonline);
    connect(_view->_send,&QPushButton::clicked,_model,&Chatmodel::Sendmessage);
    QTimer *timer = new QTimer(this);
    connect(timer,&QTimer::timeout,_model,&Chatmodel::Updatelistmessages);
    connect(timer,&QTimer::timeout,_model,&Chatmodel::Getusersfromdb);
    connect(timer,&QTimer::timeout,_model,&Chatmodel::Showactiveusers);
    connect(timer,&QTimer::timeout,_model,&Chatmodel::Checknewmessage);
    timer->start(2000);

}
