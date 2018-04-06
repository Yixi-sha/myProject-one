#ifndef GRAPH_H
#define GRAPH_H

#include "DateStructure/Exception/Exception.h"
#include "DateStructure/smartpointer/SharedPointer.h"
#include "DateStructure/List/Array/dynamicarray.h"
#include "DateStructure/Queue/LinkQueue.h"
#include "DateStructure/Stack/LinkStack.h"
#include "DateStructure/Sort/Sort.h"



namespace yixi
{

template <typename E>
class Edge : public Object
{
public:
    int b;
    int e;
    E date;

    Edge(int i = -1,int j = -1)
    {
        b = i;
        e = j;
    }
    Edge(int i ,int j ,E value )
    {
        b = i;
        e = j;
        date = value;
    }

    bool operator ==(const Edge<E>& obj)
    {
        return (b == obj.b) && (e == obj.e);
    }
    bool operator !=(const Edge<E>& obj)
    {
        return !(this == obj);
    }


    bool operator >(const Edge<E>& obj)
    {
        return (date > obj.date);
    }
    bool operator <(const Edge<E>& obj)
    {
        return (date < obj.date);
    }
    bool operator >=(const Edge<E>& obj)
    {
        return (date >= obj.date);
    }
    bool operator <=(const Edge<E>& obj)
    {
        return (date <= obj.date);
    }

};

template <typename V,typename E>
class Graph : public Object
{
protected:
    template <typename T>
    DynamicArray<T>* toArray(LinkQueue<T>& queue)
    {
        DynamicArray<T>* ret = new DynamicArray<T>(queue.length());

        if(ret != NULL)
        {
            int i = 0;
            while(queue.length()>0)
            {
                ret->set(i,queue.remove());
                i++;
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"No Enough Memory in toArray");
        }
        return ret;
    }

    template <typename T>
    DynamicArray<T>* toArray(LinkStack<T>& stack)
    {
        DynamicArray<T>* ret = new DynamicArray<T>(stack.size());

        if(ret != NULL)
        {
            int i = 0;
            while(!stack.isEmtry())
            {
                ret->set(i,stack.pop());
                i++;
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"No Enough Memory in toArray");
        }
        return ret;
    }


    int find(Array<int>& array,int ret)
    {


        while (array[ret] != -1)
        {
            ret = array[ret];
        }
        return ret;
    }
    SharedPointer< Array< Edge<E> > > getUndirectedEdge()
    {
        DynamicArray< Edge<E> >* ret = NULL;
        if(asUndirected())
        {
            LinkQueue< Edge<E> > q;

            for(int i = 0;i<vCount();i++)
            {
                for(int j = 0;j<vCount();j++)
                {
                    if(isAdjcent(i,j))
                    {
                        q.add(Edge<E>(i,j,this->getEdge(i,j)));
                    }
                }
            }
            ret = toArray(q);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"InvalidOperationException");
        }



        return ret;
    }
public:
    virtual V getVertex(int i) = 0;
    virtual bool getVertex(int i , V& value) = 0;
    virtual bool setVertex(int i, const V& value) = 0;
    virtual SharedPointer< Array<int> > getAdjacent( int i) = 0;
    virtual E getEdge(int i,int j) = 0;
    virtual bool getEdge(int i,int j,E& value) = 0;
    virtual bool setEdge(int i,int j,E value) = 0;
    virtual bool removeEdge(int i ,int j) = 0;
    virtual int vCount() = 0;
    virtual int ecount() = 0;
    virtual int OD(int i) = 0;
    virtual int ID(int i) = 0;
    virtual bool isAdjcent(int i,int j)= 0 ;
    virtual int TD(int i)
    {
        return (this->OD(i)+this->ID(i));
    }

    virtual bool asUndirected()
    {
        bool ret = true;
        for(int i = 0;i < this->vCount();i++)
        {
            SharedPointer< Array<int> > aj = this->getAdjacent(i);

            for(int j = 0;j < aj->length();j++)
            {
                ret = this->isAdjcent((*aj)[j],i);
                if(ret)
                {
                    ret = (this->getEdge(i,(*aj)[j]) == this->getEdge((*aj)[j],i));
                }

                if(!ret)
                {
                    break;
                }
            }
            if(!ret)
            {
                break;
            }

        }



        return ret;
    }

    SharedPointer < Array<int> > BSP(int i )
    {
        DynamicArray<int>* ret = NULL;

        if((i>=0) && (i<vCount()))
        {
            LinkQueue<int> q;
            LinkQueue<int> r;
            DynamicArray<bool> visted(vCount());


            for(int p = 0;p<visted.length();p++)
            {
                visted[p] = false;
            }
            q.add(i);

            while(q.length()>0)
            {
                int v= q.remove();

                if(visted[v] == false)
                {
                    SharedPointer< Array<int> > aj = this->getAdjacent(v);

                    for(int j = 0;j<aj->length();j++)
                    {
                        q.add((*aj)[j]);
                    }
                    r.add(v);
                    visted[v] = true;
                }
            }

            ret = toArray<int>(r);

        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"Invalid Operation in BSP");
        }

        return ret;

    }

    SharedPointer < Array<int> > DFS(int i )
    {

        DynamicArray<int>* ret = NULL;

        if((i>=0) && (i<vCount()))
        {
            LinkStack<int> q;
            LinkQueue<int> r;
            DynamicArray<bool> visted(vCount());


            for(int p = 0;p<visted.length();p++)
            {
                visted[p] = false;
            }

            q.push(i);

            while(!q.isEmtry())
            {
                int v = q.pop();

                if(visted[v] == false)
                {
                    SharedPointer< Array<int> > aj = this->getAdjacent(v);

                    int size = aj->length();
                    for(int j = 0;j<size;j++)
                    {
                        q.push((*aj)[size - j - 1]);
                    }
                    r.add(v);
                    visted[v] = true;
                }

            }SharedPointer< Array< Edge<E> > >

            ret = toArray<int>(r);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"Invalid Operation in DFS");
        }
        return ret;
    }

    SharedPointer< Array< Edge<E> > > prim(const E& MAX,bool min = true)
    {
        LinkQueue<  Edge<E> > ret;

        if(this->asUndirected())
        {
            DynamicArray<int> adjVex(vCount());
            DynamicArray<E> cost(vCount());
            DynamicArray<bool> mark(vCount());

            SharedPointer< Array<int> > aj = NULL;
            bool end = false;

            int v= 0;

            for(int i = 0;i<vCount();i++)
            {
                adjVex[i] = -1;
                mark[i] = false;
                cost[i] = MAX;
            }

            mark[v] = true;
            aj = getAdjacent(v);

            for(int i = 0;i<aj->length();i++)
            {
                cost[(*aj)[i]] = getEdge(v,(*aj)[i]);
                adjVex[(*aj)[i]] = v;
            }

            for(int i = 0; (i<vCount()) && !end;i++)
            {
                E m = MAX;
                int k = -1;

                for(int j = 0 ;j < vCount();j++)
                {
                    if(!mark[j] && (min ?cost[j] < m :cost[j] > m))
                    {
                        m = cost[j];
                        k = j;
                    }
                }

                end = (k == -1);

                if(!end)
                {
                    ret.add(Edge<E>(adjVex[k],k,getEdge(adjVex[k],k)));

                    mark[k] = true;

                    aj = getAdjacent(k);
                    for(int i = 0;i<aj->length();i++)
                    {
                        if((!mark[(*aj)[i]]) && (min ?(getEdge(k,(*aj)[i]) < cost[(*aj)[i]]) : (getEdge(k,(*aj)[i]) >cost[(*aj)[i]])    ) )
                        {
                            cost[(*aj)[i]] = getEdge(k,(*aj)[i]);
                            adjVex[(*aj)[i]] = k;
                        }

                    }

                }
            }

        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"Invalid Operation in prim");
        }
        if(ret.length() != vCount() - 1)
        {
            THROW_EXCEPTION(InvalidOperationException,"don`t prim");
        }


        return this->toArray(ret);
    }


    SharedPointer< Array< Edge<E> > > kruskal(bool min = true)
    {
        LinkQueue< Edge<E> > ret;
        DynamicArray<int> p(vCount());
        SharedPointer< Array< Edge<E> > > edge = getUndirectedEdge();

        for(int i = 0;i<vCount();i++)
        {
            p[i] = -1;
        }
        Sort::Shell_Selcet(*edge,min);

        for(int i = 0;i<edge->length() && ret.length() < (vCount() - 1);i++)
        {
            int b = find(p,(*edge)[i].b);
            int e = find(p,(*edge)[i].e);
            if(b != e)
            {

                p[e] = b;
                ret.add((*edge)[i]);
            }
        }

        if(ret.length() != (vCount() -1))
        {
            THROW_EXCEPTION(InvalidOperationException,"Invalid Operation Exception in kruskal");

        }

        return toArray(ret);

    }

    SharedPointer< Array< int > > dijkstra(int b ,int e,const E& MAX)
    {
        LinkQueue< int > ret;


        if((b>=0) && (b<vCount()) && (e>=0) && (e<vCount()))
        {
            DynamicArray<bool> mark(vCount());
            DynamicArray<E> dist(vCount());
            DynamicArray<int> path(vCount());

            for(int i = 0;i<vCount();i++)
            {
                mark[i] = false;
                path[i] = -1;
                dist[i] = isAdjcent(b,i) ? ( path[i] = b,getEdge(b,i)): MAX;

            }


            mark[b] = true;

            for(int i = 0;i<vCount();i++)
            {
                E m = MAX;
                int u = -1;
                for(int j = 0;j<vCount();j++)
                {
                    if(!mark[j] && dist[j] < m)
                    {
                        m = dist[j];
                        u = j;
                    }
                }
                if(u == -1)
                {
                    break;
                }

                mark[u] = true;
                for(int j = 0;j<vCount();j++)
                {
                    if(!mark[j] && isAdjcent(u,j))
                    {
                        if((getEdge(u,j) + dist[u]) < dist[j] )
                        {
                            dist[j] = (getEdge(u,j) + dist[u]);
                            path[j] = u;
                        }
                    }
                }
            }

            LinkStack<int> stack;
            stack.push(e);

            while(stack.top() != b)
            {
                stack.push(path[stack.top()]);
            }

            while(!stack.isEmtry())
            {
                ret.add(stack.pop());
            }

            if(ret.length() < 2)
            {
                THROW_EXCEPTION(InvalidOperationException,"Invalid Operation dijkstra");
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"Invalid Operation dijkstra");
        }



        return toArray(ret);
    }


    SharedPointer< Array< int > > floyd(int x,int y,const E& MAX)
    {
        LinkQueue<int> ret ;
        int path[vCount()][vCount()];
        if((x>=0) && (x<vCount()) && (y>=0) && (y<vCount()))
        {
            E dist[vCount()][vCount()];


            for(int i = 0;i<vCount();i++)
            {
               for(int j = 0;j<vCount();j++)
               {
                   if(isAdjcent(i,j))
                   {
                       path[i][j] = j;
                       dist[i][j] = getEdge(i,j);
                   }
                   else
                   {
                       dist[i][j] = MAX;
                       path[i][j] = -1;
                   }
               }
            }

            for(int i = 0 ;i<vCount();i++)
            {
                for(int j = 0;j < vCount();j++)
                {
                    for(int k = 0;k < vCount();k++)
                    {
                        if((dist[i][k] != MAX) && (dist[k][j] != MAX))
                        {
                            if( (dist[i][k] + dist[k][j]) < dist[i][j] )
                            {
                                dist[i][j] = dist[i][k] + dist[k][j];
                                path[i][j] = path[i][k];
                            }
                        }
                    }
                }
            }
            while((x != -1) && ( x != y) )
            {
                ret.add(x);
                x = path[x][y];
            }
            if(x != -1)
            {
                ret.add(x);
            }
            if(ret.length() < 2)
            {
                THROW_EXCEPTION(InvalidOperationException,"Invalid Operation dijkstra");
            }


        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"Invalid Operation floyd");
        }




        return toArray(ret);
    }

};
}



#endif // GRAPH_H
