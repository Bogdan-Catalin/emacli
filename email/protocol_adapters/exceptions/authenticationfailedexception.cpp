#include "authenticationfailedexception.h"

#include <QDebug>

AuthenticationFailedException::AuthenticationFailedException(){qDebug() << "Authentication failed";}
