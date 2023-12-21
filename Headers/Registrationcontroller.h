#ifndef REGISTRATIONCONTROLLER_H
#define REGISTRATIONCONTROLLER_H

#include <QObject>
#include "Headers/registrationmodel.h"
#include "Headers/registration.h"

class Registrationcontroller : public QObject
{
    Q_OBJECT
    SecondWidget *_view;
    Registrationmodel *_model;

public:
    Registrationcontroller(Registrationmodel *model,SecondWidget *view);
    ~Registrationcontroller();
public slots:
private slots:
signals:
};

#endif // REGISTRATIONCONTROLLER_H
