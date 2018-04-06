#ifndef ARRAY_H
#define ARRAY_H
#include "DateStructure/Object/Object.h"
#include "DateStructure/Exception/Exception.h"

namespace yixi
{

template<typename T>
class Array:public Object
{
protected:
    T *m_array;
public:
    virtual bool set(int i,const T& e)  //O(1)
    {
        bool ret=((0<=i)&&(i<length()));
        if(ret)
        {
            m_array[i]=e;
        }
        return ret;
    }

    virtual bool get(int i,T& e) const  //O(1)
    {
        bool ret=((0<=i)&&(i<length()));
        if(ret)
        {
            e=m_array[i];
        }
        return ret;
    }

    //数组访问操作符
    T& operator [] (int i)  //O(1)
    {
        if((0<=i) && ( i < (this->length()) ) )
        {
            return this->m_array[i];
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException,"Parameter i is invalid...");
        }
    }

    T operator [] (int i) const  //O(1)
    {
        return this->m_array[i];
    }

    T* array() const
    {
        return m_array;
    }

    virtual int length() const=0;
};

}

#endif // ARRAY_H

