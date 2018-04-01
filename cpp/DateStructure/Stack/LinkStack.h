#ifndef LINKSTACK_H
#define LINKSTACK_H

#include "Stack.h"
#include "DateStructure/List/ListChain/linklist.h"

namespace yixi
{
template <typename T>
class LinkStack : public Stack<T>
{
protected:
    LinkList<T> m_list;
public:
    virtual void push(const T& e)
    {
        m_list.insert(0,e);
    }
    virtual T pop()
    {
        if(m_list.length() > 0)
        {
            T temp = m_list.get(0);  //lack exception protecting
            m_list.remove(0);
            return temp;

        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"Stack  space don`t have element");
        }
    }
    virtual T top()
    {
        if(m_list.length() > 0)
        {

            return  m_list.get(0);

        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"Stack  space don`t have element");
        }
    }
    virtual void clear()
    {
        m_list.clear();
    }
    virtual int size()
    {
        return m_list.length();
    }
    virtual bool isEmtry()
    {
        return (m_list.length() == 0);
    }
};
}

#endif // LINKSTACK_H
