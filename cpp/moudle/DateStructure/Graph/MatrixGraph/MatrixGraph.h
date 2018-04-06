#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H
#include "DateStructure/Graph/Graph.h"
#include "DateStructure/List/Array/dynamicarray.h"

namespace yixi
{
template <int N,typename V,typename E>
class MatrixGraph : public Graph<V,E>
{
protected:
    V* m_vertexes[N];
    E* m_edges[N][N];
    int m_ecount;
public:
    MatrixGraph()
    {
        for(int i =0 ;i<N ; i++)
        {
            for(int j = 0 ;j < N ; j++)
            {
                m_edges[i][j] = NULL;
            }
            m_vertexes[i] = NULL;
        }
        m_ecount = 0;
    }
    virtual V getVertex(int i)
    {
       V ret;

       if(!getVertex(i,ret))
       {
           THROW_EXCEPTION(InvalidOperationException,"Invalid Operation in getVertex");
       }
       return ret;
    }

    virtual bool getVertex(int i , V& value)
    {
        bool ret = (i>=0 && i<vCount());
        if(ret)
        {
            if(m_vertexes[i] != NULL)
            {
                value = *(m_vertexes[i]);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException,"Invalid Operation in getVertex");
            }

        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"Invalid Operation in getVertex");
        }
        return ret;

    }

    virtual bool setVertex(int i, const V& value)
    {
        bool ret = (i>=0 && i<vCount());
        if(ret)
        {
            if(m_vertexes[i] == NULL)
            {
                V* m_value = new V(value);
                if(m_value != NULL)
                {
                    m_vertexes[i] = m_value;
                }
                else
                {
                    THROW_EXCEPTION(NoEnoughMemoryException,"No Enough Memory to create new node in MatrixGraph");
                }
            }
            else
            {
                V* date = m_vertexes[i];
                *date = value;
                m_vertexes[i] = date;
            }


        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"Invalid Operation in getVertex");
        }
        return ret;
    }

    virtual SharedPointer< Array<int> > getAdjacent(int i)
    {
        DynamicArray<int>* ret = NULL;

        if(i>=0 && i< N)
        {
            int n = 0;
            for(int p =0;p<N; p++)
            {
                if(m_edges[i][p] != NULL)
                {
                    n++;
                }
            }
            ret = new DynamicArray<int>(n);
            if(ret !=NULL)
            {
                for(int p =0,k=0;p<N; p++)
                {
                    if(m_edges[i][p] != NULL)
                    {
                        ret->set(k++,p);
                    }
                }

            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException,"No Enough Memory to create DynamicArray");
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"Invalid Operation in getAdjacent");
        }
        return ret;
    }

    virtual E getEdge(int i,int j)
    {
        E ret;
        if(!getEdge(i,j,ret))
        {
            THROW_EXCEPTION(InvalidOperationException,"Invalid Operation in getEdge");
        }
        return ret;


        return ret;
    }
    virtual bool getEdge(int i,int j,E& value)
    {
        bool ret = (i>= 0 && i< N) && (j>= 0 && j< N);
        if(ret)
        {
            if(m_edges[i][j] != NULL)
            {
                value = *(m_edges[i][j]);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException,"Invalid Operation in getEdge");
            }

        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"Invalid Operation in getEdge");
        }
        return ret;
    }

    virtual bool setEdge(int i,int j,E value)
    {
        bool ret = (i>= 0 && i< N) && (j>= 0 && j< N);
        if(ret)
        {
            E* ne = m_edges[i][j];
            if(ne == NULL)
            {
                ne = new E();
            }
            if(ne != NULL)
            {
                E* toDel = m_edges[i][j];
                *ne = value;
                m_edges[i][j] = ne;
                m_ecount++;
                if(toDel != NULL)
                {
                    delete toDel;
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException,"No Enough Memory to create edge");
            }
        }
        else
        {
             THROW_EXCEPTION(InvalidOperationException,"Invalid Operation in setEdge");
        }


        return ret;
    }
    virtual bool removeEdge(int i ,int j)
    {
        bool ret = (i>= 0 && i< vCount()) && (j>= 0 && j< vCount());
        if(ret)
        {
            E* toDel = m_edges[i][j];
            m_edges[i][j] = NULL;
            if(toDel != NULL)
            {
                m_ecount--;
                delete toDel;
            }


        }
        return ret;
    }
    virtual int vCount()
    {
        return N;
    }
    virtual int ecount()
    {
        return m_ecount;
    }
    virtual int OD(int i )
    {
        int ret = -1;
        if((i>= 0 && i< N))
        {
            ret = 0;
            for(int p =0 ;p<N;p++)
            {
                if(m_edges[i][p] != NULL)
                    ret++;
            }

        }
        return ret;
    }
    virtual int ID(int i)
    {
        int ret = -1;
        if((i>= 0 && i< N))
        {
            ret = 0;
            for(int p =0 ;p<N;p++)
            {
                if(m_edges[p][i] != NULL)
                    ret++;
            }

        }
        return ret;
    }

    virtual bool isAdjcent(int i,int j)
    {
        bool ret =(i>=0) && (i< vCount()) && (j>=0) && (j< vCount());
        if(ret)
        {
            ret = (m_edges[i][j] != NULL);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"Invalid Operation Exception in isAdjcent ");
        }

        return ret;
    }

    ~MatrixGraph()
    {
        for(int i =0 ;i<N ; i++)
        {
            for(int j = 0 ;j < N ; j++)
            {
                if(m_edges[i][j] != NULL)
                    delete m_edges[i][j];
            }
            if(m_vertexes[i] != NULL)
                delete m_vertexes[i];
        }
        m_ecount = 0;
    }
};
}

#endif // MATRIXGRAPH_H
