#ifndef POP3ADAPTER_H
#define POP3ADAPTER_H

#include <QObject>
#include <QSslSocket>

/**
 * @brief The Pop3Adapter class provides an API over the POP3 protocol.
 */
class Pop3Adapter : public QObject
{
    Q_OBJECT
private:
    QSslSocket *socket = new QSslSocket();
    int secondsToWait = 5; // decides how much to wait before deciding server does not answer
    bool authenticated = false;

public:
    Pop3Adapter();
    ~Pop3Adapter();

    /**
     * @brief login Logs user in to pop3 service with given details.
     */
    void login (QString host, QString port, QString user, QString password);

    /**
     * @brief logout Logs user out.
     */
    void logout ();

private slots:
    void onConnectionStateChanged(QAbstractSocket::SocketState state);
};

#endif // POP3ADAPTER_H
