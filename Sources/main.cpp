#include "Headers/login.h"
#include "Headers/loginmodel.h"
#include "Headers/logincontroller.h"
#include "Headers/database.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWidget view;
    Loginmodel model(view);
    Logincontroller controller(model,view);

    //SecondWidget *viewsec = new SecondWidget;
    //Registrationmodel modelreg(viewsec);
    //Registrationcontroller controllerreg(modelreg,viewsec);


    view.show();

    return a.exec();
}
