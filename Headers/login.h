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
    MainWidget(QWidget *parent = 0); //Constructor
    ~MainWidget(); // Destructor
private:
    QWidget* _main;
    QWidget* _widget_h;
    QPushButton* _button_login;
    QPushButton* _button_new;
    QLineEdit* _line_log;
    QLineEdit* _line_pass;
    QLabel* _label_png_m;
    QLabel* _label_log;
    QLabel* _label_pass;

    QPixmap* _pixmap_m;
    //QSqlDatabase _db;
    database db;
    SecondWidget* _secondWidget;
protected:
public slots:
    void _designinterface();
    void _definedesign();
    void _connect();
    void _performLogin();
    QString _hashpassword(const QString &password);
    void _deactivateuser();

    void _opensecondwidget();
    void _openchatwidget();
    void _openmainwidget();
};

#endif // LOGIN_H
