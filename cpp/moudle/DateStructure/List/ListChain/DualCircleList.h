#ifndef DUALCIRCLELIST_H
#define DUALCIRCLELIST_H

#include "DualLinkList.h"
#include "LinuxList.h"

namespace yixi
{
template <typename T>
class DualCircleList : public DualLinkList<T>
{
protected:
    struct Node : public Object
    {
        list_head head;
        T value;
    };

    list_head m_header;
    list_head* m_current;

    list_head* position(int i) const
    {
        list_head* ret =  const_cast<list_head*>(&m_header);
        for(int p= 0;p<i;p++)
        {
            ret = ret->next;
        }
        return ret;
    }

    int mod(int i) const
    {
        return (this->m_length == 0) ? 0 : (i % (this->m_length));

    }
public:
    DualCircleList()
    {
        m_header.next = NULL;
        this->m_length = 0;
        m_header.prev = NULL;
        m_current = NULL;

        this->m_step = 1;

        INIT_LIST_HEAD(&m_header);
    }

    virtual bool insert(const T& e)
    {
        return insert(this->m_length,e);
    }

    virtual bool insert(int i,const T& e)
    {
        bool ret = true;
        Node* node = new Node();
        if(node != NULL)
        {
            i = (i % (this->m_length +1 ));
            node->value = e;
            list_head* current = position(i);
            __list_add(&(node->head),current,current->next);
            this->m_length ++;

        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"No Enough Memory to create new node");
        }
        return ret;
    }
    virtual bool remove(int i)
    {
        bool ret = true;

        i = mod(i);

        ret = (0<= i) && (i< this->m_length);
        if(ret)
        {
            list_head* toDel = position(i)->next;

            if(m_current = toDel)
            {
                m_current = m_current->next;
            }
            list_del(toDel);
            this->m_length --;

            delete list_entry(toDel,Node,head);
        }
        return ret;
    }
    virtual bool set(int i,const T& e)
    {
        i = mod(i);
        bool ret = (i>=0) && (i<this->m_length);
        if(ret)
        {
           list_entry(position(i)->next,Node,head)->value = e;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException,"Index Out Of Bounds DualLinkList");
        }
        return ret;
    }

    virtual T get(int i) const
    {
        T ret;
        if(get(i,ret))
        {
            return ret;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException,"Index Out Of Bounds DualLinkList");
        }
    }

    virtual bool get(int i,T& e)const
    {
        i = mod(i);
        bool ret = (i>=0) && (i<this->m_length);
        if(ret)
        {
            e = list_entry(position(i)->next,Node,head)->value;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException,"Index Out Of Bounds DualLinkList");
        }
        return ret;
    }

    virtual int find(const T& e) const
    {
        int ret = -1;
        int i = 0;
        list_head* slider = NULL;


        list_for_each(slider,&this->m_header)
        {
            if(list_entry(slider,Node,head)->value == e)
            {
                ret = i;
                break;
            }
            i++;
        }
        return ret;

    }
    int length() const
    {
        return this->m_length;
    }
    virtual void clear()
    {
        int size = this->length();
        for(int i = 0;i<size;i++)
        {
            remove(0);

        }
    }

    bool move(int i, int step =1 )
    {
        bool ret = (step>0);
        i = mod(i);
        ret = (i>=0) && (i<this->m_length);
        if(ret)
        {
            m_current = position(i)->next;
            this->m_step = step;
        }
    }

    virtual bool end()  //
    {
        return (m_current == NULL) || (this->m_length == 0);
    }

    virtual T current()
    {
        if( m_current != NULL)
        {
            return list_entry(m_current,Node,head)->value;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException,"Index Out Of Bounds DualLinkList");
        }
    }
    virtual bool next()
    {
        int i = 0;
        while( (i < this->m_step) && !end())
        {

            m_current = m_current->next;
            if(m_current == &m_header)
            {
                m_current = m_current->next;
            }
            i++;
        }

        return (i == this->m_step);
    }

    virtual bool pre()
    {
        int i = 0;
        while( (i < this->m_step) && !end())
        {
            m_current = m_current->prev;
            if(m_current == &m_header)
            {
                m_current = m_current->prev;
            }
            i++;
        }

        return (i == this->m_step);
    }
    ~DualCircleList()
    {
        clear();
    }
};
}

#endif // DUALCIRCLELIST_H
