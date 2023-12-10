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
#include "Headers/user.h"
#include <QListWidget>
#include "Headers/database.h"

class chatwidget : public QWidget {
    Q_OBJECT

public:
    chatwidget(const QString &user, QWidget *parent = nullptr);

private:
    QWidget *_status;
    QCheckBox *_check;
    QHBoxLayout *_l;
    QHBoxLayout *_group_lay_active;
    QListWidget *_users_list;
    QListWidget *_active_users_list;
    QLabel* _username;
    QGroupBox* _activ_users;
    QGroupBox* _communicate;
    QGroupBox* _logout_box;
    QComboBox* _list_users;
    QTextBrowser* _text;
    QLineEdit* _message;
    QString _mail;
    QString _to_mail=NULL;
    QPushButton* _send;
    QPushButton* _logout;
    Database& db;
    QVBoxLayout *_group_logout;
    QVBoxLayout *_group_lay_communicate;
    QVBoxLayout *_all;
    QPixmap *_image;
    QMap<QString,User> _map_active_users;
    QMap<QString,User> _map_all_users;
public slots:
    void _checkonlineusers();
    void _deactivate();
    void _showactiveusers();
    void _connectwithuser();
    void _connectwithuserfromonline();
    void _connect();
    void _designinterface();
    void _designinterfacefirsthbox();
    void _designinterfaceusersgroupbox();
    void _designinterfacecommunicategroupbox();
    void _setuser(const QString &user);
    void _sendmessage();
    void _updatelistmessages();
    QLabel* _getimagefromdb(QString user);
    void _getimagefromdbquery(QString user);
    void _getusersfromdb();
    void _checknewmessage();
protected:
    void closeEvent(QCloseEvent *event) override
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Close", "Do you really want to close the application?",QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            db._deactivateuser(_mail);
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
