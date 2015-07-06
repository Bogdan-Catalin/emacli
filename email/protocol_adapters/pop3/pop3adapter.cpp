#include "pop3adapter.h"

Pop3Adapter::Pop3Adapter()
{
    QObject::connect(socket,SIGNAL(stateChanged(QAbstractSocket::SocketState)),
                     this,SLOT(onConnectionStateChanged(QAbstractSocket::SocketState)));
}

Pop3Adapter::~Pop3Adapter()
{
    socket->close();
}

// TODO: replace throw QString with custom exceptions
void Pop3Adapter::login (QString host, QString port, QString user, QString password)
{
    // Connect to socket
    socket->connectToHostEncrypted(host,port.toInt());
    // Alternative: use stateChanged() signal
    if (!socket->waitForConnected(secondsToWait * 1000)) //5s should be enough to determine if server is responding
    {
        throw QString("Connection to host timed out");
    }

    if (!socket->waitForReadyRead(secondsToWait * 1000))
    {
        throw QString ("Host not responding");
    }

    QString serverMessage;
    while (!serverMessage.contains("\n"))       // Messages sent will be CRLF terminated
    {serverMessage.append(socket->readAll());}

    if (!serverMessage.startsWith("+OK")) // rarely ever will the server greet with -ERR... it should have a good reason to
    {
        throw QString ("Server " + host + " does not like you.");
    }

    // Send auth data
    // USER
    socket->write( QString("USER "+user+"\n").toStdString().c_str());
    socket->flush();
    if (!socket->waitForReadyRead(secondsToWait*1000))
    {
        throw QString("Host not responding after sending USER command");
    }

    serverMessage.clear();
    while (!serverMessage.contains("\n")) {serverMessage.append(socket->readAll());}

    if (!serverMessage.startsWith("+OK")) {throw QString("Authentification data not recognized");}

    // PASS
    socket->write(QString("PASS "+password+"\n").toStdString().c_str());
    socket->flush();
    if (!socket->waitForReadyRead(secondsToWait*1000))
    {
        throw QString("Host not responding after sending PASS command");
    }

    serverMessage.clear();
    while (!serverMessage.contains("\n")) {serverMessage.append(socket->readAll());}

    if (!serverMessage.startsWith("+OK")) {throw QString("Authentification data not recognized");}

    authenticated = true;
}

void Pop3Adapter::logout()
{
    if (!authenticated) return;
    socket->write("QUIT\n");
    socket->flush();
}

#include <iostream>
void Pop3Adapter::onConnectionStateChanged (QAbstractSocket::SocketState state)
{
    if (state == QAbstractSocket::UnconnectedState) {authenticated = false;}
}
