#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include "../Object/Object.h"
namespace yixi
{

#define THROW_EXCEPTION(e,m)(throw e(m,__FILE__,__LINE__))

class Exception:public Object
{
protected:
    char *m_message;
    char *m_location;

    void init(const char *message,const char *file,int line);

public:
    Exception(const char *message);
    Exception(const char *file,int line);
    Exception(const char *message,const char *file,int line);

    Exception(const Exception& e);
    Exception& operator=(const Exception &e);

    virtual const char* message() const;
    virtual const char* location() const;

    virtual ~Exception()=0;
};

class ArithmeticException:public Exception
{
public:
    ArithmeticException():Exception(0){}
    ArithmeticException(const char *message):Exception(message){}
    ArithmeticException(const char *file,int line):Exception(file,line){}
    ArithmeticException(const char* message,const char *file,int line):Exception(message,file,line){}

    ArithmeticException(const ArithmeticException& e):Exception(e){}

    ArithmeticException& operator =(const ArithmeticException& e)
    {
        Exception::operator =(e);
        return *this;
    }
};

class NullPointerException:public Exception
{
public:
    NullPointerException():Exception(0){}
    NullPointerException(const char *message):Exception(message){}
    NullPointerException(const char *file,int line):Exception(file,line){}
    NullPointerException(const char* message,const char *file,int line):Exception(message,file,line){}

    NullPointerException(const NullPointerException& e):Exception(e){}

    NullPointerException& operator =(const NullPointerException& e)
    {
        Exception::operator =(e);
        return *this;
    }
};

class IndexOutOfBoundsException:public Exception
{
public:
    IndexOutOfBoundsException():Exception(0){}
    IndexOutOfBoundsException(const char *message):Exception(message){}
    IndexOutOfBoundsException(const char *file,int line):Exception(file,line){}
    IndexOutOfBoundsException(const char* message,const char *file,int line):Exception(message,file,line){}

    IndexOutOfBoundsException(const IndexOutOfBoundsException& e):Exception(e){}

    IndexOutOfBoundsException& operator =(const IndexOutOfBoundsException& e)
    {
        Exception::operator =(e);
        return *this;
    }
};

class NoEnoughMemoryException:public Exception
{
public:
    NoEnoughMemoryException():Exception(0){}
    NoEnoughMemoryException(const char *message):Exception(message){}
    NoEnoughMemoryException(const char *file,int line):Exception(file,line){}
    NoEnoughMemoryException(const char* message,const char *file,int line):Exception(message,file,line){}

    NoEnoughMemoryException(const NoEnoughMemoryException& e):Exception(e){}

    NoEnoughMemoryException& operator =(const NoEnoughMemoryException& e)
    {
        Exception::operator =(e);
        return *this;
    }
};

class InvalidParameterException:public Exception
{
public:
    InvalidParameterException():Exception(0){}
    InvalidParameterException(const char *message):Exception(message){}
    InvalidParameterException(const char *file,int line):Exception(file,line){}
    InvalidParameterException(const char* message,const char *file,int line):Exception(message,file,line){}

    InvalidParameterException(const InvalidParameterException& e):Exception(e){}

    InvalidParameterException& operator =(const InvalidParameterException& e)
    {
        Exception::operator =(e);
        return *this;
    }
};

class InvalidOperationException:public Exception
{
public:
    InvalidOperationException():Exception(0){}
    InvalidOperationException(const char *message):Exception(message){}
    InvalidOperationException(const char *file,int line):Exception(file,line){}
    InvalidOperationException(const char* message,const char *file,int line):Exception(message,file,line){}

    InvalidOperationException(const InvalidOperationException& e):Exception(e){}

    InvalidOperationException& operator =(const InvalidOperationException& e)
    {
        Exception::operator =(e);
        return *this;
    }
};

void Exception::init(const char *message,const char *file,int line)
{
    m_message=(message ? strdup(message) : NULL);

    if(file!=NULL)
    {
        char sl[16]={0};

        snprintf(sl,strlen(sl),"%d",line);

        m_location=static_cast<char *>(malloc(strlen(file)+strlen(sl)+2));

        if(m_location!=NULL)
        {
            m_location=strcpy(m_location,file);
            m_location=strcat(m_location,":");
            m_location=strcat(m_location,sl);
        }
    }
    else
    {
        m_location=NULL;
    }
}

Exception::Exception(const char *message)
{
    init(message,NULL,0);
}

Exception::Exception(const char *file,int line)
{
    init(NULL,file,line);
}

Exception::Exception(const char *message,const char *file,int line)
{
    init(message,file,line);
}

Exception::Exception(const Exception& e)
{
    m_message=strdup(e.m_message);
    m_location=strdup(e.m_location);
}

Exception& Exception::operator=(const Exception &e)
{
    if(this!=&e)
    {
        free(m_message);
        free(m_location);

        m_message=strdup(e.m_message);
        m_location=strdup(e.m_location);
    }
    return *this;
}

const char* Exception::message() const
{
    return m_message;
}
const char* Exception::location() const
{
    return m_location;
}

Exception::~Exception()
{
    free(m_message);
    free(m_location);
}

}

#endif // EXCEPTION_H
