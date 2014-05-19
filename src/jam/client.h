#ifndef JAMCLIENT_H
#define JAMCLIENT_H

#include <QObject>
#include <QString>

#include <gloox/client.h>
#include <gloox/jid.h>
#include <gloox/presencehandler.h>
#include <gloox/connectionlistener.h>
#include <gloox/message.h>

#include <thread>

#include "src/jam/roster.h"

namespace Jam {
    class Client;
}

class Jam::Client :
        public QObject,
        gloox::ConnectionListener, gloox::PresenceHandler
{
    Q_OBJECT
    Q_PROPERTY(bool connected READ isConnected NOTIFY connectedChanged)
    Q_PROPERTY(Jam::Roster* roster READ getRoster)

public:
    Client(QObject *parent=0);
    ~Client();

    virtual void handlePresence( const gloox::Presence& );
    virtual void onConnect();
    virtual bool onTLSConnect(const gloox::CertInfo& );
    virtual void onDisconnect( gloox::ConnectionError  );

    bool isConnected() const { return connected; }
    Jam::Roster *getRoster() { return roster; }

public slots:
    void connect(QString, QString);
    void ping();

signals:
    void connectedChanged();

private:
    bool connected;
    void setConnected(bool);

    gloox::JID j_jid;
    gloox::Client *j_clientp = 0;

    std::thread connection_thread;
    bool connection_thread_started = false;

    Jam::Roster *roster = 0;
};

#endif // JAMCLIENT_H
