#ifndef MYSTRING_H
#define MYSTRING_H
#include <cstdlib>
#include <cstring>

#include "../Object/Object.h"
#include "../Exception/Exception.h"





namespace yixi
{
class MyString : public Object
{
protected:
    char* m_str;
    int m_length;

    void init(const char* s);
    bool equal(const char* l,const char* r,int len) const;
    int* make_pmt(const char* p) const;


public:  
    MyString();
    MyString(char c);
    MyString(const char* s);
    MyString(const MyString& s);
    int length() const;
    const char* str() const;

    bool operator ==(const MyString& s) const;
    bool operator ==(const char* s) const;

    bool operator !=(const MyString& s) const;
    bool operator !=(const char* s) const;

    bool operator <(const MyString& s) const;
    bool operator <(const char* s) const;

    bool operator >(const MyString& s) const;
    bool operator >(const char* s) const;

    bool operator >=(const MyString& s) const;
    bool operator >=(const char* s) const;

    bool operator <=(const MyString& s) const;
    bool operator <=(const char* s) const;

    MyString operator +(const MyString& s) const;
    MyString operator +(const char* s) const;

    MyString& operator +=(const MyString& s) ;
    MyString& operator +=(const char* s) ;

    MyString operator -(const MyString& s) const;
    MyString operator -(const char* s) const;
    MyString& operator -=(const MyString& s) ;
    MyString& operator -=(const char* s) ;

    MyString& operator =(const MyString& s) ;
    MyString& operator =(const char* s);
    MyString& operator =(char c);

    char& operator []( int i);
    char& operator [](int i) const ;

    bool startWith(const char* c) const;
    bool startWith(const MyString& s) const;
    bool endOf(const char* c) const;
    bool endOf(const MyString& s) const;

    MyString& insert(int i,const char* c);
    MyString& insert(int i,const MyString& s);

    int indexOf(const MyString& obj) const ;
    int indexOf(const char* s) const;

    MyString& trim();

    MyString& remove(int i ,int len);
    MyString& remove(const char* s);
    MyString& remove(const MyString& obj);


    MyString& replace(const char* t ,const char* s);
    MyString& replace(const MyString& t ,const char* s);
    MyString& replace(const char* t ,const MyString& s);
    MyString& replace(const MyString& t ,const MyString& s);

    MyString sub(int i,int len);





    ~MyString();
};

void MyString::init(const char* s)
{
    m_str = strdup(s);

    if(m_str != NULL)
    {
        m_length = strlen(m_str);
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException,"No Enough Memory to create mystring");
    }
}


MyString::MyString()
{
    init("");
}

MyString::MyString(char c)
{
    char s[] = {c,'\0'};
    init(s);
}

MyString::MyString(const char* s)
{
    init(s ? s : "");
}

MyString::MyString(const MyString& s)
{
    init(s.m_str ? s.m_str : "");
}

int MyString::length() const
{
    return m_length;
}
const char* MyString::str() const
{
    return m_str;
}
MyString::~MyString()
{
    free(m_str);
}

bool MyString::operator ==(const MyString& s) const
{
    return (strcmp(m_str,s.m_str) == 0);
}
bool MyString::operator ==(const char* s) const
{
    return (strcmp(m_str,s ? s : "") == 0);
}

bool MyString::operator !=(const MyString& s) const
{
    return !(*this == s);
}
bool MyString::operator !=(const char* s) const
{
    return !(*this == s);
}

bool MyString::operator >(const MyString& s) const
{
    return ( strcmp(m_str,s.m_str) > 0);
}
bool MyString::operator >(const char* s) const
{
    return ( strcmp(m_str,s ? s : "") > 0);
}

bool MyString::operator <(const MyString& s) const
{
    return ( strcmp(m_str,s.m_str) < 0);
}
bool MyString::operator <(const char* s) const
{
    return ( strcmp(m_str,s ? s : "") < 0);
}

bool MyString::operator >=(const MyString& s) const
{
    return ( strcmp(m_str,s.m_str) >= 0);
}
bool MyString::operator >=(const char* s) const
{
    return ( strcmp(m_str,s ? s : "") >= 0);
}

bool MyString::operator <=(const MyString& s) const
{
    return ( strcmp(m_str,s.m_str) <= 0);
}
bool MyString::operator <=(const char* s) const
{
    return ( strcmp(m_str,s ? s : "") <= 0);
}


MyString MyString::operator +(const MyString& s) const
{
    return (*this+s.m_str);
}
MyString MyString::operator +(const char* s) const
{
    MyString ret;
    s = s ? s : "";
    int len = m_length + strlen(s);
    char* str = reinterpret_cast<char*>(malloc(len+1));

    if(str)
    {
        strcpy(str,m_str);
        strcat(str,s);
        free(ret.m_str);
        ret.m_str = str;
        ret.m_length = len;
    }
    else
    {
      THROW_EXCEPTION(NoEnoughMemoryException,"No Enough Memory to + mystring");
    }


    return ret;
}

MyString& MyString::operator +=(const MyString& s)
{
    return (*this = *this + s);
}
MyString& MyString::operator +=(const char* s)
{
    return (*this = *this + s);
}
MyString& MyString::operator =(const MyString& s)
{

    return (*this = s.m_str);
}
MyString& MyString::operator =(const char* s)
{
    if( m_str != s)
    {
        s= s? s: "";
        char* str = strdup(s);

        if(m_str != NULL)
        {
            char* del = m_str;
            m_length = strlen(str);
            m_str = str;
            free(del);
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"No Enough Memory to copy mystring");
        }


    }
    return *this;

}
MyString& MyString::operator =(char c)
{
    char s[] = {c,'\0'};

    return (*this = s);
}

char& MyString::operator [](int i)
{
    if( (i>=0) && (i<m_length))
    {
        return m_str[i];
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException,"Index Out Of Bounds in Mystring");
    }
}
char& MyString::operator [](int i) const
{
    return (const_cast<MyString&>(*this))[i];
}



bool MyString::equal(const char* l,const char* r,int len) const
{
    bool ret = true;

    for(int i = 0;i<len;i++)
    {
        if(l[i] != r[i])
        {
            ret= false;
            break;
        }
    }

    return ret;
}

bool MyString::startWith(const char* c) const
{
    bool ret =(c != NULL);
    if(ret)
    {
        int len = strlen(c);
        ret = (len <= m_length);
        if(ret)
        {
            ret = equal(c,m_str,len);
        }
    }
   return ret;
}

bool MyString::startWith(const MyString& s) const
{
    return startWith(s.m_str);
}
bool MyString::endOf(const char* c) const
{
    bool ret =(c != NULL);
    if(ret)
    {
        int len = strlen(c);
        ret = (len <= m_length);
        if(ret)
        {
            char* str = m_str + (m_length -len);
            ret = equal(c,str,len);
        }
    }
   return ret;
}
bool MyString::endOf(const MyString& s) const
{
    return endOf(s.m_str);
}


MyString&  MyString::insert(int i,const char* c)
{
    if ((i<= m_length) && (i>=0))
    {
        if((c != NULL) && (c[0] != '\0'))
        {
            int len = strlen(c);
            char* str = reinterpret_cast<char*>(malloc(m_length + len + 1));
            if(str != NULL)
            {
                strncpy(str,m_str,i);
                strncpy(str+i,c,len);
                strncpy(str+i+len,m_str+i,m_length - i);
                str[m_length + len] = '\0';
                char* toDel = m_str;
                m_str = str;
                m_length = m_length +len;
                free(toDel);
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException,"No Enough Memory to creat new mystring");
            }


        }

    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException,"Index Out Of Bounds in Mystring");
    }
    return *this;

}
MyString&  MyString::insert(int i,const MyString& s)
{
    return insert(i,s.m_str);
}

MyString& MyString::trim()
{
    int b =0;
    int e= m_length - 1;
    while( m_str[b] == ' ')b++;
    while( m_str[e] == ' ')e--;

    if( b == 0)
    {
        m_str[e + 1] = '\0';
        m_length = e+1;
    }
    else
    {
        for( int i = 0, j = b; j<=e;i++,j++)
        {
            m_str[i] = m_str[j];
        }
        m_str[e - b + 1] = '\0';
        m_length = e - b + 1;
    }

    return *this;
}


int* MyString::make_pmt(const char* p) const
{
    int len = strlen(p);
    int* ret = static_cast<int*>(malloc(sizeof(int) * len));

    if(ret != NULL)
    {
        int ll = 0;
        ret[0] = 0;

        for(int i = 1;i<len;i++)
        {
            while((ll > 0) && (p[ll] != p[i]))
            {
                ll = ret[ll -1];
            }

            if(p[ll] == p[i])
            {
                ll ++;
            }
            ret[i] = ll;
        }
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException,"No Enough Memory to create pmt");
    }

    return ret;
}

int MyString::indexOf(const MyString& obj) const
{
    return indexOf(obj.m_str);
}


int MyString::indexOf(const char* s) const
{
    s = s? s: "";
    int ret = -1;
    int s1 = m_length;
    int p1 = strlen(s);
    int* pmt = make_pmt(s);

    if((0< p1) && (p1 <= s1))
    {
        for(int i = 0,j= 0 ; i<s1;i++)
        {
            while ((j >0) && (m_str[i] != s[j]))
            {
                j = pmt[j -1];
            }

            if(m_str[i] == s[j])
            {
                j++;
            }
            if( j == p1)
            {
                ret = i + 1 - p1;
            }
        }
    }
    free(pmt);
    return ret;
}

MyString& MyString::remove(int i ,int len)
{
    if( (i>=0) && (i<=m_length)  && (len > 0) )
    {
        int n = i;
        int m = i+len;

        while((n<m) && (m < m_length))
        {
            m_str[n++] = m_str[m++];
        }
        m_str[n] = '\0';
        m_length = n;

    }
    return *this;
}

MyString& MyString::remove(const char* s)
{
    int ret = indexOf(s);
    if(ret >= 0)
    {
        remove(ret,strlen(s));
    }
    return *this;

}
MyString& MyString::remove(const MyString& obj)
{
    return remove(obj.m_str);
}


MyString MyString::operator -(const MyString& s) const
{
    return MyString(*this).remove(s);
}
MyString MyString::operator -(const char* s) const
{

    return MyString(*this).remove(s);

}

MyString& MyString::operator -=(const MyString& s)
{
    remove(s);
    return *this;
}
MyString& MyString::operator -=(const char* s)
{
    remove(s);
    return *this;
}

MyString& MyString::replace(const char* t ,const char* s)
{
    int index = indexOf(t);
    if(index >=0)
    {
        remove(t);
        insert(index,s);
    }
    return *this;
}
MyString& MyString::replace(const MyString& t ,const char* s)
{
    return replace(t.m_str,s);
}
MyString& MyString::replace(const char* t ,const MyString& s)
{
    return replace(t,s.m_str);
}
MyString& MyString::replace(const MyString& t ,const MyString& s)
{
    return replace(t.m_str,s.m_str);
}

MyString MyString::sub(int i,int len)
{
    MyString ret;
    if((i>=0) && (i< m_length ))
    {
        if( len < 0) len = 0;
        if((len + i) > m_length) len = m_length -i;

        char* str = reinterpret_cast<char*>(malloc(sizeof(char) * len + 1));
        if(str != NULL)
        {

            for(int p = 0;p<len;p++)
            {
                str[p] = m_str[p + i];
            }
            str[len] = '\0';
            ret.m_str = str;
            ret.m_length = len;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"No Enough Memory create sub");
        }

    }

    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException,"Index Out Of Bounds sub");
    }

    return ret;
}

}
#endif // MYSTRING_H
