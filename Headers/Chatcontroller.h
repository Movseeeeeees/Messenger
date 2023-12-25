#ifndef CHATCONTROLLER_H
#define CHATCONTROLLER_H
#include <QObject>
#include "Headers/Chatwidget.h"
#include "Headers/Chatmodel.h"

class Chatcontroller : public QObject
{
    Q_OBJECT
    Chatwidget *_view;
    Chatmodel *_model;
public:
    Chatcontroller(Chatmodel *,Chatwidget *);
};

#endif // CHATCONTROLLER_H
