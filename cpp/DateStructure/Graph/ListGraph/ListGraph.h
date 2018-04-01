#ifndef LISTGRAPH_H
#define LISTGRAPH_H
#include "../Graph.h"
#include "DateStructure/List/ListChain/linklist.h"
#include "DateStructure/List/Array/dynamicarray.h"

namespace yixi
{



template <typename V,typename E>
class ListGraph : public Graph <V,E>
{
protected:
    struct Vertex : public Object
    {
        V* value;
        Vertex(V* date = NULL)
        {
            value = date;
        }
        LinkList< Edge<E> > link;
    };

    LinkList<Vertex*> m_list;
public:
    ListGraph(unsigned int n = 0)
    {
        for(unsigned int i =0;i<n;i++)
        {
            addVertex();
        }
    }

    int addVertex()
    {
        int ret = -1;
        Vertex* node = new Vertex();
        if(node != NULL)
        {
            m_list.insert(node);
            ret = m_list.length() -1;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"No Enough Memory ");
        }
        return ret;
    }

    int addVertex(const V date)
    {
        int ret = addVertex();
        if(ret >= 0)
        {
            setVertex(ret,date);
        }


        return ret;
    }
    bool setVertex(int i, const V& value)
    {
        bool ret = (i>=0 && i<m_list.length());
        if(ret)
        {
            Vertex* node = m_list.get(i);
            V* date = node->value;
            if(date == NULL)
            {
                date = new V();
                if(date==NULL)
                {
                    THROW_EXCEPTION(NoEnoughMemoryException,"No Enough Memory in setVertex");
                }
            }
            *(date) = value;
            node->value = date;

        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"Invalid Operation Exception in setVertex ");
        }
        return ret;
    }
    bool getVertex(int i, V &value)
    {
        bool ret = (i>=0 && i<m_list.length());
        if(ret)
        {
            Vertex* node = m_list.get(i);
            if(node->value != NULL)
            {
                value = *(node->value);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException,"Invalid Operation Exception in getVertex ");
            }

        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"Invalid Operation Exception in getVertex ");
        }

        return ret;
    }

    V getVertex(int i )
    {
        V ret;
        if(! getVertex(i,ret))
        {
            THROW_EXCEPTION(InvalidOperationException,"Invalid Operation Exception in getVertex ");
        }
        return ret;
    }

    void removeVertex()
    {
        if(m_list.length() > 0)
        {
            int index = m_list.length() - 1;
            Vertex* node = m_list.get(index);
            if (m_list.remove(index))
            {
                int i = 0;
                for(m_list.move(0);!m_list.end();m_list.next())
                {
                    int pos = m_list.current()->link.find(Edge<E>(i,index));
                    if(pos >=0)
                    {
                        m_list.current()->link.remove(pos);
                    }
                    i++;
                }

            }
            delete node->value;
            delete node;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"Invalid Operation Exception in removeVertex ");
        }
    }
    virtual SharedPointer< Array<int> > getAdjacent( int i)
    {
        DynamicArray<int>* ret = NULL;
        if(i>=0 && i <vCount())
        {
            Vertex* node = m_list.get(i);
            ret = new DynamicArray<int>(node->link.length());
            if(ret != NULL)
            {
                for(int p = (node->link.move(0),0);!node->link.end();node->link.next(),p++)
                {
                    ret->set(p,node->link.current().e);
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException,"NoEnoughMemoryException");
            }

        }
        else
        {
           THROW_EXCEPTION(InvalidOperationException,"Invalid Operation Exception in getAdjacent ");
        }
        return ret;
    }
    virtual E getEdge(int i,int j)
    {
        E ret;
        getEdge(i,j,ret);
        return ret;

    }
    virtual bool getEdge(int i,int j,E& value)
    {
        bool ret = (i>=0) && (i < vCount()) && (j>=0) && (j < vCount());
        if(ret)
        {
            Vertex* node = m_list.get(i);
            int pos = node->link.find(Edge<E>(i,j));
            if(pos >=0)
            {
                value = node->link.get(pos).date;
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException,"InvalidOperationException");
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"InvalidOperationException");
        }
        return ret;
    }
    virtual bool setEdge(int i,int j,E value)
    {
        bool ret = (i>=0) && (i < vCount()) && (j>=0) && (j < vCount());
        if(ret)
        {
            Vertex* node = m_list.get(i);
            int pos = node->link.find(Edge<E>(i,j));
            if(pos >=0)
            {
                ret = node->link.set(pos,Edge<E>(i,j,value));
            }
            else
            {
                ret = node->link.insert(Edge<E>(i,j,value));
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"InvalidOperationException");
        }
        return ret;
    }
    virtual bool removeEdge(int i ,int j)
    {
        bool ret = (i>=0) && (i < vCount()) && (j>=0) && (j < vCount());
        if(ret)
        {
            Vertex* node = m_list.get(i);
            int pos = node->link.find(Edge<E>(i,j));
            if(pos >=0)
            {
                ret = node->link.remove(pos);
            }

        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"InvalidOperationException");
        }
        return ret;

    }
    virtual int vCount()
    {
        return m_list.length();
    }
    virtual int ecount()
    {
        int ret = 0;
        for(m_list.move(0);!m_list.end();m_list.next())
        {
            ret += m_list.current()->link.length();
        }
        return ret;
    }
    virtual int OD(int i)
    {
        int ret = 0;
        if((i>=0) && (i<vCount()))
        {

            Vertex* node = m_list.get(i);
            ret = node->link.length();

        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"Invalid Operation Exception in OD ");
        }
         return ret;
    }
    virtual int ID(int i)
    {
        int ret = 0;
        if((i>=0) && (i<vCount()))
        {

            for(int j = (m_list.move(0),0);!m_list.end();m_list.next(),j++)
            {
                LinkList< Edge<E> >& edge = m_list.current()->link;
                if(edge.find(Edge<E>(j,i)) >=0)
                {
                    ret++;
                }
            }


        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"Invalid Operation Exception in ID ");
        }
         return ret;
    }

    virtual bool isAdjcent(int i,int j)
    {
        bool ret =(i>=0) && (i< vCount()) && (j>=0) && (j< vCount());

        if(ret)
        {
            int pos = m_list.get(i)->link.find(Edge<E>(i,j));
            if(pos >=0)
            {
                ret = true;
            }
            else
            {
                ret = false;
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"Invalid Operation Exception in isAdjcent ");
        }


        return ret;

    }




    ~ListGraph()
    {
        while(m_list.length()>0)
        {
            Vertex* toDel = m_list.get(0);
            m_list.remove(0);

            delete toDel->value;
            delete toDel;

        }
    }

};
}


#endif // LISTGRAPH_H
