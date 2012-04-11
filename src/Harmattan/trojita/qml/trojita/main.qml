import QtQuick 1.1
import com.nokia.meego 1.0

PageStackWindow {
    id: appWindow

    //initialPage: imapSettingsPage
    initialPage: mailboxListPage

    /*ImapSettingsPage {
        id: imapSettingsPage
    }*/

    MailboxListPage {
        id: mailboxListPage
        model: mailboxModel

        onMailboxSelected: {
            msgListModel.setMailbox(mailbox)
            pageStack.push(messageListPage)
        }
    }

    MessageListPage {
        id: messageListPage
        model: msgListModel
    }

    /*Menu {
        id: myMenu
        visualParent: pageStack
        MenuLayout {
            MenuItem { text: qsTr("Sample menu item") }
        }
    }*/
}
