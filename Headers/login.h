#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QSqlDatabase>
#include <QGridLayout>
#include <QGroupBox>
#include <QTextEdit>
#include <QMap>
#include "Headers/registration.h"
#include <QEvent>
#include <QKeyEvent>
#include "Headers/database.h"

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent=nullptr );
    ~MainWidget();
    QPushButton* _buttonlogin;
    QPushButton* _buttonnew;
private:
    QWidget* _widgeth;
    QLineEdit* _linelog;
    QLineEdit* _linepass;
    QLabel* _labelpngm;
    QLabel* _labellog;
    QLabel* _labelpass;
    QPixmap* _pixmapm;
    Database& db;
    SecondWidget* _secondWidget;
protected:
public slots:
    void Designinterface();
    void Definedesign();
    QString Get(QString);
    void Showsomething(QString);
};

#endif // LOGIN_H
