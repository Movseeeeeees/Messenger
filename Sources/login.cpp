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
    _designinterface();
    _connect();
}

void MainWidget::_definedesign()
{
    //_main= new QWidget;
    _button_new = new QPushButton(tr("Create new account"));
    _button_login = new QPushButton(tr("Log In"));
    _button_login->setDefault(true);
    _line_log = new QLineEdit;
    _line_pass = new QLineEdit;
    _label_log = new QLabel("Login");
    _label_pass = new QLabel("Password");
    _line_pass->setEchoMode(QLineEdit::Password);
    _pixmap_m = new QPixmap("/home/movses/Desktop/Messenger/Messenger/Resources/chat.png");
    _label_png_m = new QLabel;
    _label_png_m->setPixmap(*_pixmap_m);
    _label_png_m->setFixedSize(250,250);
    _widget_h = new QWidget;
    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(_button_new);
    horizontalLayout->addWidget(_button_login);
    _widget_h->setLayout(horizontalLayout);
}

void MainWidget::_designinterface()
{
    _definedesign();
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(_label_png_m,1,0);
    mainLayout->addWidget(_label_log,2,0);
    mainLayout->addWidget(_line_log,3,0);
    mainLayout->addWidget(_label_pass,4,0);
    mainLayout->addWidget(_line_pass,5,0);
    mainLayout->addWidget(_widget_h,6,0);
    this->setLayout(mainLayout);
    this->setWindowTitle(tr("Messenger"));
    //this->show();
}

void MainWidget::_connect()
{
    connect(_button_new, &QPushButton::clicked, this,&MainWidget::_opensecondwidget);
    connect(_button_login,&QPushButton::clicked,this,&MainWidget::_performLogin);

}

void MainWidget::_performLogin()
{
    if(_line_log->text().isEmpty() or _line_pass->text().isEmpty()){
        QMessageBox::information(this, "Info", "wrong");
    }
    else{
        if(db._performlogin(_line_log->text(),_hashpassword(_line_pass->text()))){
            qDebug() << "Login successful";
            db._activeateuser(_line_log->text());
            _openchatwidget();
            this->hide();
            this->setVisible(false);
        }
        else{
             QMessageBox::information(this, "Info", "Login failed. Incorrect username or password.");
        }
    }
}

QString MainWidget::_hashpassword(const QString &password)
{
    QByteArray passwordBytes = password.toUtf8();
    QByteArray hashBytes = QCryptographicHash::hash(passwordBytes, QCryptographicHash::Sha256);
    return QString(hashBytes.toHex());
}

void MainWidget::_opensecondwidget()
{
    _secondWidget = new SecondWidget;
    this->hide();
    _secondWidget->show();
    connect(_secondWidget,SIGNAL(mysignal()),this,SLOT(_openmainwidget()));
}

void MainWidget::_openchatwidget()
{
    chatwidget *chat=new chatwidget(_line_log->text(),nullptr);
    chat->resize(600,700);
    chat->show();
}

void MainWidget::_openmainwidget()
{
    this->show();
}

MainWidget::~MainWidget()
{
    delete _button_new;
    delete _button_login;
    delete _line_log;
    delete _line_pass;
    delete _label_log;
    delete _label_pass;
    delete _pixmap_m;
}
