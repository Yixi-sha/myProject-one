#ifndef GTREE_H
#define GTREE_H
#include "../Tree.h"
#include "GTreeNode.h"
#include "../../Queue/LinkQueue.h"

namespace yixi
{
template <typename T>
class GTree : public Tree<T>
{
protected:
    LinkQueue< GTreeNode<T>* > m_queue;




    GTreeNode<T>* find(GTreeNode<T>* node,const T& value) const
    {
        GTreeNode<T>* ret = NULL;
        if(node != NULL)
        {
            if(node->value == value)
            {
                return node;
            }
            else
            {
                for(node->child.move(0);(!node->child.end()) && (ret == NULL);node->child.next())
                {
                    ret = find(node->child.current(),value);
                }
            }
        }
        return ret;
    }

    GTreeNode<T>* find(GTreeNode<T>* node, GTreeNode<T>* obj) const
    {
        GTreeNode<T>* ret = NULL;
        if(node != NULL)
        {
            if(node == obj)
            {
                return node;
            }
            else
            {

                for(node->child.move(0);(!node->child.end()) && (ret == NULL);node->child.next())
                {
                    ret = find(node->child.current(),obj);
                }
            }
        }
        return ret;
    }
    void free(GTreeNode<T>* node)
    {
        if(node != NULL)
        {
            for(node->child.move(0);(!node->child.end());node->child.next())
            {
                free(node->child.current());
            }

            if(node->flag())
            {
                delete node;
            }

        }

    }
    void remove(GTreeNode<T>* node,GTree*& ret)
    {
        ret = new GTree<T>();
        if(ret != NULL)
        {
            if(node == this->root())
            {
                this->m_root = NULL;
            }
            else
            {
                LinkList<GTreeNode<T>*>& child = dynamic_cast<GTreeNode<T>*> (node->parent)->child;
                child.remove(child.find(node));
                node->parent = NULL;
            }
            ret->m_root = node;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"No Enough Memory to create new Gtree in remove");
        }
    }

    int count(GTreeNode<T>* root) const
    {
        int ret = 0;

        if(root != NULL)
        {
            ret = 1;
            for(root->child.move(0);!root->child.end();root->child.next())
            {
                ret += count(root->child.current());
            }
        }
        return ret;
    }


    int height(GTreeNode<T>* root) const
    {
        int ret = 0;
        int child = 0;
        if(root != NULL)
        {
            for(root->child.move(0);!root->child.end();root->child.next())
            {
                int hei = height(root->child.current());
                child = child > hei ? child : hei;
            }
            ret  = child + 1;
        }
        return ret;
    }

    int degree(GTreeNode<T>* root) const
    {
        int ret = 0;
        int child = 0;
        if(root != NULL)
        {
            ret = root->child.length();
            for(root->child.move(0);!root->child.end();root->child.next())
            {
                int deg = degree(root->child.current());
                child = child > deg ? child : deg;
            }
            ret = ret > child ? ret : child;
        }
        return ret;
    }
public:
    GTree(GTreeNode<T>* obj = NULL)
    {
        this->m_root =  obj;
    }

    virtual bool insert(TreeNode<T>* node)
    {
        bool ret = true;
        if(node !=  NULL)
        {
            if(this->root() == NULL)
            {
                node->parent = NULL;
                this->m_root =node;
            }
            else
            {
                GTreeNode<T>* np = find(node->parent);
                if( np != NULL)
                {
                    GTreeNode<T>* n = dynamic_cast<GTreeNode<T>*>(node);
                    if( np->child.find(n) < 0)
                    {
                        np->child.insert(n);
                    }

                }
                else
                {
                    THROW_EXCEPTION(InvalidParameterException," Invalid Parameter node->parent== Invalid");
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException," Invalid Parameter node == NULL");
        }

        return ret;
    }

    virtual bool insert(const T& value,TreeNode<T>* parent = NULL)
    {
        bool ret = true;
        GTreeNode<T>* node = GTreeNode<T>::NewNode();
        if(node != NULL)
        {
            node->value = value;
            node->parent = parent;
            insert(node);
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"No Enough Memory to create new node");
        }

        return ret;
    }

    virtual SharedPointer< Tree<T> >remove(const T& value)
    {    
        GTree<T>* ret = NULL;
        GTreeNode<T>* del = find(value);
        if(del != NULL)
        {
            remove(del,ret);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException,"Invalid Parameter in remove");
        }
        return ret;
    }

    virtual SharedPointer< Tree<T> >remove(TreeNode<T>* node)
    {
        GTree<T>* ret = NULL;
        GTreeNode<T>* del = find(node);
        if(del != NULL)
        {
            remove(del,ret);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException,"Invalid Parameter in remove");
        }
        m_queue.clear();
        return ret;
    }

    virtual GTreeNode<T>* find(const T& value) const
    {
        return find(this->root(),value);
    }

    virtual GTreeNode<T>* find(TreeNode<T>* node) const
    {
        return find(this->root(), dynamic_cast<GTreeNode<T>*>(node));
    }

    virtual GTreeNode<T>* root() const
    {
        return dynamic_cast<GTreeNode<T>*>(this->m_root);
    }

    virtual int degree() const
    {
        return degree(root());
    }

    virtual int count() const
    {
        return count(root());
    }

    virtual int height() const
    {
        return height(root());
    }

    virtual void clear()
    {
        free(root());
        this->m_root = NULL ;
        m_queue.clear();
    }

    bool begin()
    {
        bool ret = (root() != NULL);
        if(ret)
        {
            m_queue.clear();
            m_queue.add(root());
        }
        return ret;
    }

    bool end()
    {
        return (m_queue.length() == 0);
    }

    bool next()
    {
        bool ret = (m_queue.length() > 0);
        if(ret)
        {
            GTreeNode<T>* node = m_queue.remove();
            for(node->child.move(0);!node->child.end();node->child.next())
            {
                m_queue.add(node->child.current());
            }
        }
        return ret;
    }
    T current()
    {
        if(m_queue.length() > 0)
        {
            return m_queue.front()->value;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException,"Index Out Of Bounds Queue");
        }
    }

    ~GTree()
    {
        clear();
    }
};
}

#endif // GTREE_H
