#ifndef SERVERNOTRESPONDINGEXCEPTION_H
#define SERVERNOTRESPONDINGEXCEPTION_H

#include <QtConcurrent/QtConcurrent>

/**
 * @brief The ServerNotRespondingException class Thrown when host doesn't respond.
 */
class ServerNotRespondingException : public QtConcurrent::Exception
{
public:
    ServerNotRespondingException(QString desc);
    void raise () const {throw *this;}
};

#endif // SERVERNOTRESPONDINGEXCEPTION_H
