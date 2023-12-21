#include "Headers/Chatmodel.h"

Chatmodel::Chatmodel(chatwidget *view,QString user):db(Database::instance()),_view(view)
{
    Getusersfromdb();
    Showactiveusers();
    _mail=user;
}

void Chatmodel::Logout()
{
    _view->close();
}

void Chatmodel::Connectwithuser()
{
    _view->_l->addWidget(_view->_communicate);
    _to_mail=_view->_userslist->currentItem()->text();
    Updatelistmessages();
    _view->_userslist->currentItem()->setBackground(Qt::color0);
    db._markmessagestatuseread(_to_mail,_view->_mail);
}

void Chatmodel::Connectwithuserfromonline()
{
    _view->_l->addWidget(_view->_communicate);
    _to_mail=_view->_activeuserslist->currentItem()->text();
    Updatelistmessages();
    db._markmessagestatuseread(_to_mail,_view->_mail);

}

void Chatmodel::Updatelistmessages()
{
     if(_to_mail != ""){
        _view->_text->clear();
        db._updatelistmessages(_view->_text,_view->_mail,_to_mail);
    }

}

void Chatmodel::Showactiveusers()
{
    db._checkonlineusers(_mapactiveusers,_view->_mail);
    QMapIterator<QString,User> i(_mapactiveusers);
    _view->_activeuserslist->clear();
    while(i.hasNext()){
        i.next();
        QString labelText = i.key();
        _view->_activeuserslist->addItem(labelText);
    }

}

void Chatmodel::Getusersfromdb()
{
    db._getusersfromdb(_mapallusers,_view->_userslist,_view->_mail);

}

void Chatmodel::Checknewmessage()
{
    db._checknewmessage(_view->_userslist,_mapallusers,_view->_mail);

}

void Chatmodel::Sendmessage()
{
     if(!_view->_message->text().isEmpty() and _to_mail != ""){
        QString textuser=QString("%1 : %2 \n").arg(_mail).arg(_view->_message->text());
        _view->_text->insertPlainText(textuser);
        _view->_text->moveCursor(QTextCursor::End);
        db._sendmessage(_mail,_to_mail,_view->_message->text());
        _view->_message->clear();
    }

}
