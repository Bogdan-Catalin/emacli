#include "servercannotbereachedexception.h"

#include <QDebug>

ServerCannotBeReachedException::ServerCannotBeReachedException(QString desc){qDebug() << desc;}
