#ifndef POP3ADAPTER_H
#define POP3ADAPTER_H

#include <QObject>
#include <QSslSocket>


// TODO: idea - POP3 is presented as a state machine, so the implementation could be one too
/**
 * @brief The Pop3Adapter class provides an API over the POP3 protocol.
 */
class Pop3Adapter : public QObject
{
    Q_OBJECT
private:
    QSslSocket *socket = new QSslSocket();

    /**
     * @brief secondsToWait States how much to wait before deciding server does not answer.
     */
    int secondsToWait = 5;

    /**
     * @brief authenticated Will switch to false if socket is closed or logged out.
     */
    bool authenticated = false;

    /**
     * @brief waitForSocketReadyRead Calls QsslSocket::waitForReadyRead and throws exception if it times out.
     * @param command POP3 command sent prior to wait.
     */
    bool waitForSocketReadyRead (QString command);

public:
    Pop3Adapter();
    ~Pop3Adapter();

    /**
     * @brief login Logs user in to pop3 service with given details.
     */
    bool login (QString host, QString port, QString user, QString password);

    /**
     * @brief logout Logs user out.
     */
    void logout ();

    /**
     * @brief getNumberOfEmails Uses the command STAT to get number of emails.
     */
    int getNumberOfEmails();

private slots:

    /**
     * @brief onConnectionStateChanged Triggered when state of connection changed.
     */
    void onConnectionStateChanged(QAbstractSocket::SocketState state);

signals:

};

#endif // POP3ADAPTER_H
