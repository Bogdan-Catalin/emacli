#ifndef POP3ADAPTER_H
#define POP3ADAPTER_H

#include <QObject>
#include <QSslSocket>

// Exceptions this class may throw
#include "../exceptions/servernotrespondingexception.h"
#include "../exceptions/servercannotbereachedexception.h"
#include "../exceptions/authenticationfailedexception.h"
#include "../exceptions/unathenticatedexception.h"

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
    void waitForSocketReadyRead (QString command);

    /**
     * @brief checkAuthentication Checks if user is authentified and throws exception if not.
     */
    void checkAuthentication ();

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

    /**
     * @brief getNumberOfEmails Uses the command STAT to get number of emails.
     */
    unsigned int getNumberOfEmails();

private slots:

    /**
     * @brief onConnectionStateChanged Triggered when state of connection changed.
     */
    void onConnectionStateChanged(QAbstractSocket::SocketState state);

signals:

};

#endif // POP3ADAPTER_H
