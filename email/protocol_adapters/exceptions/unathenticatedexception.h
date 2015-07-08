#ifndef UNATHENTICATEDEXCEPTION_H
#define UNATHENTICATEDEXCEPTION_H

#include <QtConcurrent/QtConcurrent>
class UnathenticatedException : public QtConcurrent::Exception
{
public:
    UnathenticatedException(QString desc);
    void raise () const {throw *this;}
};

#endif // UNATHENTICATEDEXCEPTION_H
