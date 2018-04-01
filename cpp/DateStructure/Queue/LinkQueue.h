#ifndef LINKQUEUE_H
#define LINKQUEUE_H

#include "Queue.h"
#include "DateStructure/List/ListChain/LinuxList.h"

namespace yixi
{
template <typename T>
class LinkQueue : public Queue<T>
{
protected:
    struct Node : public Object
    {
        list_head head;
        T value;
    };
    list_head m_header;
    int m_length;
public:
    LinkQueue()
    {
        INIT_LIST_HEAD(&m_header);
        m_length = 0;
    }

    virtual void add(const T& e)
    {

        Node* node = new Node();
        if(node != NULL)
        {
            node->value = e;
            list_add_tail(&node->head,&m_header);
            m_length ++;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"No Enough Memory to create new node");
        }

    }
    virtual T remove()
    {
        if(m_length > 0)
        {
            list_head* temp = m_header.next;
            T ret = list_entry(temp,Node,head)->value;
            list_del(m_header.next);
            m_length --;
            delete list_entry(temp,Node,head);
            return ret;
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

            list_head* temp = m_header.next;
            T ret = list_entry(temp,Node,head)->value;
            return ret;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"Queue  space don`t have element");
        }
    }
    virtual void clear()
    {
        int size = m_length;
        for(int i =0;i<size;i++)
        {
            remove();
        }
    }
    virtual int length() const
    {
        return m_length;
    }

    virtual bool isEmtry()
    {
        return (m_length == 0);
    }
    ~LinkQueue()
    {
        clear();
    }
};
}

#endif // LINKQUEUE_H
