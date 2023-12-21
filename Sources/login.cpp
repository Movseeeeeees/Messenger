#include <QtWidgets>
#include "Headers/login.h"
#include "Headers/chatwidget.h"
#include "Headers/database.h"
#include <QtSql/QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QLabel>
#include <QMessageBox>
#include <QCryptographicHash>
#include <QFileDialog>
#include <QPixmap>
#include <QBuffer>
#include <QFileInfo>
#include <QCloseEvent>
#include <QMap>
#include <QObject>

MainWidget::MainWidget(QWidget *parent) :QWidget(parent),db(Database::instance())
{
    Definedesign();
    Designinterface();
}

void MainWidget::Definedesign()
{
    _buttonnew = new QPushButton(tr("Create new account"));
    _buttonlogin = new QPushButton(tr("Log In"));
    _buttonlogin->setDefault(true);
    _linelog = new QLineEdit;
    _linepass = new QLineEdit;
    _labellog = new QLabel("Login");
    _labelpass = new QLabel("Password");
    _linepass->setEchoMode(QLineEdit::Password);
    _pixmapm = new QPixmap("/home/movses/Desktop/Messenger/Messenger/Resources/chat.png");
    _labelpngm = new QLabel;
    _labelpngm->setPixmap(*_pixmapm);
    _labelpngm->setFixedSize(250,250);
    _widgeth = new QWidget;
    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(_buttonnew);
    horizontalLayout->addWidget(_buttonlogin);
    _widgeth->setLayout(horizontalLayout);
}

void MainWidget::Designinterface()
{
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(_labelpngm,1,0);
    mainLayout->addWidget(_labellog,2,0);
    mainLayout->addWidget(_linelog,3,0);
    mainLayout->addWidget(_labelpass,4,0);
    mainLayout->addWidget(_linepass,5,0);
    mainLayout->addWidget(_widgeth,6,0);
    this->setLayout(mainLayout);
    this->setWindowTitle(tr("Messenger"));
}

void MainWidget::Showsomething(QString thing)
{
    QMessageBox::information(this, "Info", thing);
}

QString MainWidget::Get(QString text)
{
    if(text=="log")
        return _linelog->text();
    else
        if(text=="pass")
            return _linepass->text();
    return " ";
}

MainWidget::~MainWidget()
{
    delete _buttonnew;
    delete _buttonlogin;
    delete _linelog;
    delete _linepass;
    delete _labellog;
    delete _labelpass;
    delete _pixmapm;
}
