#ifndef CHATCONTROLLER_H
#define CHATCONTROLLER_H
#include <QObject>
#include "Headers/chatwidget.h"
#include "Headers/Chatmodel.h"

class Chatcontroller : public QObject
{
    Q_OBJECT
    chatwidget *_view;
    Chatmodel *_model;
public:
    Chatcontroller(Chatmodel *model,chatwidget *view);
};

#endif // CHATCONTROLLER_H
