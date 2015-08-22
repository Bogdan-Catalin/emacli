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

bool Pop3Adapter::waitForSocketReadyRead()
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

    if (!waitForSocketReadyRead()) return false;

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
    if (!waitForSocketReadyRead()) return false;

    serverMessage.clear();
    while (!serverMessage.contains("\n")) {serverMessage.append(socket->readAll());}

    if (!serverMessage.startsWith("+OK"))
    {
        // TODO: emit invalid authentication data signal
        return false;
    }

    // PASS
    socket->write(QString("PASS "+password+"\n").toStdString().c_str());
    if (!waitForSocketReadyRead()) return false;

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
        // TODO: emit unauthenticated signal
        return -1;
    }
    socket->write("STAT\n");
    socket->flush();
    if (!waitForSocketReadyRead()) return -1;

    QString message;
    while (!message.contains("\n")) {message.append(socket->readAll());}

    if (!message.startsWith("+OK"))
    {
        // TODO: emit STAT failed esignal
        return -1;
    }
    return message.split(" ")[1].toInt();
}


QString Pop3Adapter::getEmail (unsigned int index)
{
    if (!authenticated)
    {
        // TODO: emit unauthenticated signal
        return "";
    }
    int emailNo = getNumberOfEmails();
    if (emailNo <= 0 || index > emailNo) return "";

    QString command = "RETR " + QString::number(index) + "\n";
    socket->write(command.toStdString().c_str());
    socket->flush();

    if (!waitForSocketReadyRead())
    {
        // TODO: emit server not responding signal
        return "";
    }

    // Get byte by byte until we get size of mail
    QString message;
    char *byt = new char[2];
    while (!message.contains("\n"))
    {
        socket->read(byt,1);
        byt[1] = 0;
        message.append(byt);
    }
    delete[] byt;

    if (!message.startsWith("+OK"))
    {
        // TODO: emit retrieve email failed signal
        return "";
    }

    // Get message octets
    int messageSize = message.split(" ")[1].toInt();
    // And read remaining message
    message.clear();
    while (messageSize >= message.size())
    {
        waitForSocketReadyRead();
        message.append(socket->readAll());
    }

    return message;
}

void Pop3Adapter::onConnectionStateChanged (QAbstractSocket::SocketState state)
{
    if (state == QAbstractSocket::UnconnectedState) {authenticated = false;}
}
