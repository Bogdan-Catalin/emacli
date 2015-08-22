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

bool Pop3Adapter::waitForSocketReadyRead(QString command)
{
    if (!socket->waitForReadyRead(secondsToWait * 1000))
    {
        // TODO: emit server not responding signal
        return false;
    }
    return true;
}

bool Pop3Adapter::login (QString host, QString port, QString user, QString password)
{
    // Connect to socket
    socket->connectToHostEncrypted(host,port.toInt());
    // Alternative: use stateChanged() signal
    if (!socket->waitForConnected(secondsToWait * 1000)) //5s should be enough to determine if server is responding
    {
        // TODO: emit server cannot be reached signal
        return false;
    }

    waitForSocketReadyRead("connect");

    QString serverMessage;
    while (!serverMessage.contains("\n")) // All POP3 messages are CRLF terminated
    {serverMessage.append(socket->readAll());}

    if (!serverMessage.startsWith("+OK")) // rarely ever will the server greet with -ERR. It is not even specified in RFC 1939
    {
        // TODO: emit server refused connection signal
        return false;
    }

    // Send auth data
    // USER
    socket->write( QString("USER "+user+"\n").toStdString().c_str());
    socket->flush();
    waitForSocketReadyRead("USER");

    serverMessage.clear();
    while (!serverMessage.contains("\n")) {serverMessage.append(socket->readAll());}

    if (!serverMessage.startsWith("+OK"))
    {
        // TODO: emit invalid authentication data signal
        return false;
    }

    // PASS
    socket->write(QString("PASS "+password+"\n").toStdString().c_str());
    waitForSocketReadyRead("PASS");

    serverMessage.clear();
    while (!serverMessage.contains("\n")) {serverMessage.append(socket->readAll());}

    if (!serverMessage.startsWith("+OK"))
    {
        // TODO: emit invalid authentication data signal
        return false;
    }

    authenticated = true;
}

void Pop3Adapter::logout()
{
    if (!authenticated) return;
    socket->write("QUIT\n");
    socket->flush();
    this->authenticated = false;
}

int Pop3Adapter::getNumberOfEmails()
{
    if (!authenticated)
    {
        // TODO: emit not logged in signal
        return -1;
    }
    socket->write("STAT\n");
    socket->flush();
    waitForSocketReadyRead("STAT");

    QString message;
    while (!message.contains("\n")) {message.append(socket->readAll());}

    if (!message.startsWith("+OK"))
    {
        // TODO: emit STAT failed esignal
        return -1;
    }
    return message.split(" ")[1].toInt();
}

void Pop3Adapter::onConnectionStateChanged (QAbstractSocket::SocketState state)
{
    if (state == QAbstractSocket::UnconnectedState) {authenticated = false;}
}
