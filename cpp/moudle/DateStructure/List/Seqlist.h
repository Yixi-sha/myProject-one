#ifndef SEQLIST
#define SEQLIST
#include "DateStructure/List/List.h"
#include "DateStructure/Exception/Exception.h"

namespace yixi
{

template<typename T>
class SeqList:public List<T>
{
protected:
    T* m_array;  //顺序存储结构
    int m_length;  //当前线性表长度
public:
    bool insert(int i,const T& e)
    {
        bool ret=((0<=i)&&(i<=m_length));

        ret=ret&&(m_length<capacity());

        if(ret)
        {
            for(int p=m_length-1;p>=i;p--)
            {
                m_array[p+1]=m_array[p];
            }
            m_array[i]=e;
            m_length++;
        }
        return ret;
    }

    bool insert(const T& e)
    {
        return insert(m_length,e);
    }

    bool remove(int i)
    {
        bool ret=((0<=i)&&(i<m_length));

        if(ret)
        {
            for(int p=i;p<m_length-1;p++)
            {
                m_array[p]=m_array[p+1];
            }
            m_length--;
        }
        return ret;
    }

    bool set(int i,const T& e)
    {
        bool ret=((0<=i)&&(i<m_length));

        if(ret)
        {
            m_array[i]=e;
        }
        return ret;
    }

    bool get(int i,T& e) const
    {
        bool ret=((0<=i)&&(i<m_length));

        if(ret)
        {
            e=m_array[i];
        }
        return ret;
    }

    int length() const
    {
        return m_length;
    }

    void clear()
    {
        m_length=0;
    }

    //顺序存储线性表的数组访问方式
    T& operator[] (int i)
    {
        if((0<=i)&&(i<m_length))
        {
            return m_array[i];
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException,"Parameter i is invalid...");
        }
    }

    T operator[] (int i) const
    {
        return (const_cast<SeqList<T>&>(*this))[i];  //相当于调用上面的函数
        /*
        if((0<=i)&&(i<m_length))
        {
            return m_array[i];
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException,"Parameter i is invalid...");
        }
        */
    }
    //顺序存储空间的容量

    int find(const T& e) const
    {
        int ret = -1;
        for(int i = 0 ; i<this->length();i++)
        {
            if( this->m_array[i] == e)
            {
                ret = i;
                break;
            }
        }
        return ret;
    }
    virtual int capacity() const=0;
};

}

#endif // SEQLIST

