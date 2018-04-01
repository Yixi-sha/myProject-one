#ifndef CIRCLELIST_H
#define CIRCLELIST_H

#include "linklist.h"
namespace yixi
{
template <typename T>
class CircleList : public  LinkList<T>
{
protected:
    typedef typename LinkList<T>::Node Node;

    Node* last() const
    {
        return this->position(this->m_length -1)->next;
    }
    void last_to_first() const
    {
        last()->next = this->m_header.next;
    }

    int mod(int i) const
    {
        return (this->m_length == 0) ? 0 : (i % (this->m_length));

    }

public:
    bool insert(const T& e)
    {
        return this->insert(this->m_length,e);
    }

    bool insert(int i,const T& e)
    {
        bool ret = true;


        i = (this->m_length == 0) ? 0 : (i % (this->m_length + 1));


        ret = LinkList<T> :: insert(i,e);

        if(ret && (i == 0))
        {
            last_to_first();
        }

        return ret;
    }

    bool remove(int i)
    {
        bool ret = true;

        i = mod(i);



        if(i == 0)
        {
            Node* toDel = this->m_header.next;
            if( toDel != NULL)
            {
                this->m_header.next = toDel->next;
                this->m_length --;
                if( this->m_length >0)
                {
                    last_to_first();

                    if( this->m_current == toDel)
                    {
                        this->m_current = toDel->next;

                    }
                }
                else
                {
                    this->m_header.next = NULL;
                    this->m_current->next = NULL;

                }
                this->destroy(toDel);

            }
            else
            {
                ret =false;
            }

        }
        else
        {
            ret = LinkList<T>::remove(i);
        }

        return ret;
    }
    bool set(int i ,const T& e)
    {
        i = mod(i);

        bool ret = LinkList<T> :: set(i,e);
        return ret;
    }

    T get(int i )  const
    {

        return  LinkList<T> ::get(mod(i));
    }

    void clear()
    {
        int size = this->m_length;
        for(int i = 0;i<size -1 ;i++)
        {
            this->remove(1);
        }

        if( (this->m_length) == 1)
        {
            Node* toDel = this->m_header.next;

            this->m_header.next = NULL;
            this->m_current = NULL;
            this->m_length = this->m_length - 1;
            this->destroy(toDel);

        }

    }


    virtual bool move(int i,int step = 1)
    {
        return LinkList<T> :: move(mod(i),step);
    }

    virtual bool end()  //
    {
        return (this->m_current == NULL) || (this->m_length == 0);
    }



    ~CircleList()
    {
        this->clear();
    }




};
}



#endif // CIRCLELIST_H
