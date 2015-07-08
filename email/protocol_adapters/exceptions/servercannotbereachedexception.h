#ifndef SERVERCANNOTBEREACHEDEXCEPTION_H
#define SERVERCANNOTBEREACHEDEXCEPTION_H

#include <QtConcurrent/QtConcurrent>

/**
 * @brief The ServerCannotBeReachedException class Thrown when cannot establish connection to host
 */
class ServerCannotBeReachedException : public QtConcurrent::Exception
{
public:
    ServerCannotBeReachedException(QString desc);
    void raise () const {throw *this;}
};

#endif // SERVERCANNOTBEREACHEDEXCEPTION_H
