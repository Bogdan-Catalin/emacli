#ifndef AUTHENTICATIONFAILEDEXCEPTION_H
#define AUTHENTICATIONFAILEDEXCEPTION_H

#include <QtConcurrent/QtConcurrent>

/**
 * @brief The AuthenticationFailedException class Thrown when authentication data is invalid.
 */
class AuthenticationFailedException : public QtConcurrent::Exception
{
public:
    AuthenticationFailedException();
    void raise() const {throw *this;}
};

#endif // AUTHENTICATIONFAILEDEXCEPTION_H
