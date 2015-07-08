#include "unathenticatedexception.h"

#include <QDebug>
UnathenticatedException::UnathenticatedException(QString desc){qDebug() << desc;}
