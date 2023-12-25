#include "Headers/Login.h"
#include "Headers/Loginmodel.h"
#include "Headers/Logincontroller.h"
#include "Headers/Database.h"

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
