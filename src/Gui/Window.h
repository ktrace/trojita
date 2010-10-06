/* Copyright (C) 2006 - 2010 Jan Kundrát <jkt@gentoo.org>

   This file is part of the Trojita Qt IMAP e-mail client,
   http://trojita.flaska.net/

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or the version 3 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef TROJITA_WINDOW_H
#define TROJITA_WINDOW_H

#include <QMainWindow>

#include "Imap/ConnectionState.h"
#include "Imap/Model/Cache.h"

class QAuthenticator;
class QItemSelection;
class QModelIndex;
class QProgressBar;
class QScrollArea;
class QToolButton;
class QTreeView;

namespace Imap {
namespace Mailbox {

class Model;
class MailboxModel;
class MsgListModel;
class PrettyMailboxModel;

}
}

namespace Gui {

class MessageView;
class MsgListView;
class ProtocolLoggerWidget;

class MainWindow: public QMainWindow {
    Q_OBJECT
    typedef QList<QPair<QString,QString> > _recipientsType;
public:
    MainWindow();
    void invokeComposeDialog( const QString& subject = QString(),
                              const QString& body = QString(),
                              const _recipientsType& recipients = _recipientsType() );

private slots:
    void showContextMenuMboxTree( const QPoint& position );
    void showContextMenuMsgListTree( const QPoint& position );
    void slotReloadMboxList();
    void slotResyncMbox();
    void slotResizeMsgListColumns();
    void alertReceived( const QString& message );
    void networkPolicyOffline();
    void networkPolicyExpensive();
    void networkPolicyOnline();
    void slotShowSettings();
    void slotExpunge();
    void connectionError( const QString& message );
    void cacheError( const QString& message );
    void authenticationRequested( QAuthenticator* auth );
    void slotComposeMailUrl( const QUrl& url );
    void slotComposeMail();
    void slotReplyTo();
    void slotReplyAll();
    void handleMarkAsRead( bool );
    void handleMarkAsDeleted( bool );
    void msgListActivated( const QModelIndex& );
    void msgListClicked( const QModelIndex& );
    void msgListDoubleClicked( const QModelIndex& );
    void msgListSelectionChanged( const QItemSelection& selected, const QItemSelection& deselected );
    void slotCreateMailboxBelowCurrent();
    void slotCreateTopMailbox();
    void slotDeleteCurrentMailbox();
    void updateMessageFlags();
    void updateMessageFlags( const QModelIndex& index );
    void scrollMessageUp();
    void showConnectionStatus( QObject* parser, Imap::ConnectionState state );
    void updateBusyParsers( bool busy );
    void slotShowAboutTrojita();
    void slotDonateToTrojita();

    void slotMailboxDeleteFailed( const QString& mailbox, const QString& msg );
    void slotMailboxCreateFailed( const QString& mailbox, const QString& msg );

private:
    void createMenus();
    void createActions();
    void createWidgets();
    void setupModels();

    void nukeModels();
    void connectModelActions();

    void createMailboxBelow( const QModelIndex& index );

    void updateActionsOnlineOffline( bool online );

    Imap::Mailbox::Model* model;
    Imap::Mailbox::MailboxModel* mboxModel;
    Imap::Mailbox::PrettyMailboxModel* prettyMboxModel;
    Imap::Mailbox::MsgListModel* msgListModel;

    QTreeView* mboxTree;
    MsgListView* msgListTree;
    QTreeView* allTree;
    MessageView* msgView;
    QDockWidget* allDock;

    QScrollArea* area;

    ProtocolLoggerWidget* imapLogger;
    QDockWidget* imapLoggerDock;

    QAction* reloadMboxList;
    QAction* reloadAllMailboxes;
    QAction* resyncMbox;
    QAction* netOffline;
    QAction* netExpensive;
    QAction* netOnline;
    QAction* exitAction;
    QAction* showFullView;
    QAction* showImapLogger;
    QAction* showMenuBar;
    QAction* configSettings;
    QAction* composeMail;
    QAction* replyTo;
    QAction* replyAll;
    QAction* expunge;
    QAction* createChildMailbox;
    QAction* createTopMailbox;
    QAction* deleteCurrentMailbox;
    QAction* aboutTrojita;
    QAction* donateToTrojita;

    QAction* markAsRead;
    QAction* markAsDeleted;

    QProgressBar* busyParsersIndicator;
    QToolButton* networkIndicator;

    MainWindow(const MainWindow&); // don't implement
    MainWindow& operator=(const MainWindow&); // don't implement
};

}

#endif
