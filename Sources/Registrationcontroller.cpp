#include "Headers/Registrationcontroller.h"

Registrationcontroller::Registrationcontroller(Registrationmodel *model, SecondWidget *view):_view(view),_model(model)
{
    connect(_view->_loginpage,&QPushButton::clicked,_view,&SecondWidget::Openmainwidget);
    connect(_view->_load,&QPushButton::clicked,_model,&Registrationmodel::Loadimage);
    connect(_view->_create,&QPushButton::clicked,_model,&Registrationmodel::Createaccount);
}

Registrationcontroller::~Registrationcontroller(){
}
