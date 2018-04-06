#ifndef STATICSTACK_H
#define STATICSTACK_H
#include "Stack.h"

namespace yixi
{
template <typename T,int N>
class StaticStack : public Stack<T>
{
protected:
    char m_space[sizeof(T)*N];
    int m_top;
    int m_size;
public:
    StaticStack()
    {
        m_size = 0;
        m_top = -1;
    }
    int capacity() const
    {
        return N;
    }
    virtual void push(const T& e)
    {

        if(m_size<N)
        {
            reinterpret_cast<T*>(m_space)[m_top+1] = e;
            m_top++;
            m_size++;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"No Enough  space to push new element");
        }
    }
    virtual T pop()
    {
        if(m_size > 0)
        {
            m_top--;
            m_size--;
            return (reinterpret_cast<T*>(m_space)[m_top+1]);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"Stack  space don`t have element");
        }
    }
    virtual T top()
    {
        if(m_size > 0)
        {
            return (reinterpret_cast<T*>(m_space)[m_top]);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"Stack  space don`t have element");
        }
    }
    virtual void clear()
    {
        m_size = 0;
        m_top = -1;
    }
    virtual int size()
    {
        return m_size;
    }
    virtual bool isEmtry()
    {
        return (m_size == 0);
    }
};
}

#endif // STATICSTACK_H
