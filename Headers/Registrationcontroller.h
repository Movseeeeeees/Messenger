#ifndef REGISTRATIONCONTROLLER_H
#define REGISTRATIONCONTROLLER_H

#include <QObject>
#include "Headers/Registrationmodel.h"
#include "Headers/Registration.h"

class Registrationcontroller : public QObject
{
    Q_OBJECT
    SecondWidget *_view;
    Registrationmodel *_model;

public:
    Registrationcontroller(Registrationmodel *,SecondWidget *);
    ~Registrationcontroller();
public slots:
private slots:
signals:
};

#endif // REGISTRATIONCONTROLLER_H
