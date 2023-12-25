#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QHBoxLayout>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QTextBrowser>
#include <QSqlDatabase>
#include <QComboBox>
#include <QMessageBox>
#include <QCloseEvent>
#include "Headers/User.h"
#include <QListWidget>
#include "Headers/Database.h"

class Chatwidget : public QWidget {
    friend class Chatcontroller;
    friend class Chatmodel;
    Q_OBJECT

public:
    Chatwidget(const QString &, QWidget *parent = nullptr);

private:
    QWidget *_status;
    QCheckBox *_check;
    QHBoxLayout *_l;
    QHBoxLayout *_grouplayactive;
    QListWidget *_userslist;
    QListWidget *_activeuserslist;
    QLabel* _username;
    QGroupBox* _activusers;
    QGroupBox* _communicate;
    QGroupBox* _logoutbox;
    QComboBox* _listusers;
    QTextBrowser* _text;
    QLineEdit* _message;
    QString _mail;
    QPushButton* _send;
    QPushButton* _logout;
    Database& db;
    QVBoxLayout *_grouplogout;
    QVBoxLayout *_grouplaycommunicate;
    QVBoxLayout *_all;
    QPixmap *_image;
public slots:
    void Designinterface();
    void Designinterfacefirsthbox();
    void Designinterfaceusersgroupbox();
    void Designinterfacecommunicategroupbox();
    void Setuser(const QString &user);
    QLabel* Getimagefromdb(QString user);
protected:
    void closeEvent(QCloseEvent *event) override
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Close", "Do you really want to close the application?",QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            db.Deactivateuser(_mail);
            event->accept();
        }
        else {
            event->ignore();
        }
    }
signals:

private slots:
};

#endif // MYWIDGET_H
