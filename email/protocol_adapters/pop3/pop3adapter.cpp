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

void Pop3Adapter::waitForSocketReadyRead(QString command)
{
    if (!socket->waitForReadyRead(secondsToWait * 1000))
    {
        throw ServerNotRespondingException ("Host not responding after "+command+" command.");
    }
}

void Pop3Adapter::checkAuthentication()
{
        if (authenticated==false)
        {
            throw UnathenticatedException ("User not authenticated.");
        }
}

void Pop3Adapter::login (QString host, QString port, QString user, QString password)
{
    // Connect to socket
    socket->connectToHostEncrypted(host,port.toInt());
    // Alternative: use stateChanged() signal
    if (!socket->waitForConnected(secondsToWait * 1000)) //5s should be enough to determine if server is responding
    {
        throw ServerCannotBeReachedException("Connection to host timed out");
    }

    waitForSocketReadyRead("connect");

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
    waitForSocketReadyRead("USER");

    serverMessage.clear();
    while (!serverMessage.contains("\n")) {serverMessage.append(socket->readAll());}

    if (!serverMessage.startsWith("+OK")) {throw QString("Authentification data not recognized");}

    // PASS
    socket->write(QString("PASS "+password+"\n").toStdString().c_str());
    waitForSocketReadyRead("PASS");

    serverMessage.clear();
    while (!serverMessage.contains("\n")) {serverMessage.append(socket->readAll());}

    if (!serverMessage.startsWith("+OK")) {throw AuthenticationFailedException();}

    authenticated = true;
}

void Pop3Adapter::logout()
{
    if (!authenticated) return;
    socket->write("QUIT\n");
    socket->flush();
    this->authenticated = false;
}

unsigned int Pop3Adapter::getNumberOfEmails()
{
    checkAuthentication();
    socket->write("STAT\n");
    socket->flush();
    waitForSocketReadyRead();

    QString message;
    while (!message.contains("\n")) {message.append(socket->readAll());}

    if (!message.startsWith("+OK")) {throw QString ("Server sent -ERR after STAT");}
    return message.split(" ")[1].toInt();
}

void Pop3Adapter::onConnectionStateChanged (QAbstractSocket::SocketState state)
{
    if (state == QAbstractSocket::UnconnectedState) {authenticated = false;}
}
