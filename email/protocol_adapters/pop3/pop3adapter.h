#ifndef POP3ADAPTER_H
#define POP3ADAPTER_H

#include <QObject>
#include <QtNetwork/QTcpSocket>

/**
 * @brief The Pop3Adapter class provides an API over the POP3 protocol.
 */
class Pop3Adapter : public QObject
{
    Q_OBJECT
private:
    QTcpSocket *socket = new QTcpSocket();

public:

public slots:

};

#endif // POP3ADAPTER_H
