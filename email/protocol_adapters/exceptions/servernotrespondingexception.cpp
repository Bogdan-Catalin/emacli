#include "servernotrespondingexception.h"

#include <QDebug>

ServerNotRespondingException::ServerNotRespondingException(QString desc){qDebug() << desc;}
