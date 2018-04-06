#ifndef STATICQUEUE_H
#define STATICQUEUE_H

#include "Queue.h"
namespace yixi
{
template <typename T,int N>
class StaticQueue : public Queue<T>
{
protected:
    mutable char m_space[sizeof(T) * N];
    int m_front;
    int m_rear;
    int m_length;
public:
    StaticQueue()
    {
        m_front = 0;
        m_rear = 0;
        m_length = 0;
    }
    int capacity() const
    {
        return N;
    }
    virtual void add(const T& e)
    {
        if(m_length < N)
        {
            reinterpret_cast<T*>(m_space)[m_rear] = e;
            m_rear = m_rear+1;
            m_rear = m_rear % N;
            m_length ++;
        }
        else
        {
             THROW_EXCEPTION(InvalidOperationException,"No Enough  space to add new element in Queue");
        }

    }
    virtual T remove()
    {
        if(m_length > 0)
        {
            int front = m_front;
            m_front = m_front + 1;
            m_front = m_front % N;
            m_length --;

            return (reinterpret_cast<T*>(m_space)[front]);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"Queue  space don`t have element");
        }
    }
    virtual T front() const
    {
        if(m_length > 0)
        {

            return reinterpret_cast<T*>(m_space)[m_front];
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"Queue  space don`t have element");
        }
    }
    virtual void clear()
    {
        m_front = 0;
        m_rear = 0;
        m_length = 0;
    }
    virtual int length() const
    {
        return m_length;
    }

    virtual bool isEmtry()
    {
        return (m_length == 0);
    }
    ~StaticQueue()
    {
        clear();
    }
};
}

#endif // STATICQUEUE_H
