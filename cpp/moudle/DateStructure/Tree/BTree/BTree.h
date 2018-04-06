#ifndef BTREE_H
#define BTREE_H
#include "../Tree.h"
#include "BTreeNode.h"
#include "../../Queue/LinkQueue.h"
#include "DateStructure/List/Array/dynamicarray.h"

namespace yixi
{
enum BTTraversal
{
    PreOrder,
    Inorder,
    PostOrder,
    LevelOrder
};

template <typename T>
class BTree : public Tree<T>
{
protected:
    LinkQueue< BTreeNode<T>* > m_queue;


    virtual BTreeNode<T>* find(BTreeNode<T>* node,const T& value) const
    {
        BTreeNode<T>* ret = NULL;
        if(node != NULL)
        {
            if(node->value == value)
            {
                return node;
            }
            else
            {
                ret = find(node->Right,value);
                if(ret == NULL)
                {
                    ret = find(node->Left,value);
                }
            }
        }
        return ret;
    }

    virtual BTreeNode<T>* find(BTreeNode<T>* node, BTreeNode<T>* obj) const
    {
        BTreeNode<T>* ret = NULL;
        if(node != NULL)
        {
            if(node == obj)
            {
                return node;
            }
            else
            {

                ret = find(node->Right,obj);
                if(ret == NULL)
                {
                    ret = find(node->Left,obj);
                }
            }
        }
        return ret;
    }
    virtual bool insert(BTreeNode<T>* node,BTreeNode<T>* m_parent,BTNodePos pos)
    {
        bool ret = true;
        if(pos == BT_ANY)
        {
            if(m_parent->Left == NULL)
            {
                m_parent->Left = node;
            }
            else if(m_parent->Right == NULL)
            {
                m_parent->Right = node;
            }
            else
            {
                ret = false;
            }
        }
        else if(pos == BT_LEFT)
        {
            if(m_parent->Left == NULL)
            {
                m_parent->Left = node;
            }
            else
            {
                ret = false;
            }
        }
        else if(pos == BT_RIGHT)
        {
            if(m_parent->Right == NULL)
            {
                m_parent->Right = node;
            }
            else
            {
                ret = false;
            }
        }
        else
        {
            ret = false;
        }
        return ret;

    }

    void remove(BTreeNode<T>* node,BTree<T>*& ret)
    {

        ret = new BTree<T>();
        if(ret != NULL)
        {
            if(node == this->root())
            {
                this->m_root = NULL;
            }
            else
            {
                BTreeNode<T>* m_parent = dynamic_cast<BTreeNode<T>*> (node->parent);
                if(m_parent->Left == node )
                {
                    m_parent->Left  = NULL;
                }
                else if(m_parent->Right == node )
                {
                    m_parent->Right  = NULL;
                }
                node->parent = NULL;
            }
            ret->m_root = node;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"No Enough Memory to create new Gtree in remove");
        }
        m_queue.clear();
    }

    virtual void free(BTreeNode<T>* node)
    {
        if(node != NULL)
        {
            free(node->Left);
            free(node->Right);

            if(node->flag())
            {
                delete node;
            }

        }


    }

    virtual int count(BTreeNode<T>* root) const
    {
        int ret = 0;

        if(root != NULL)
        {
            ret = 1;
            if(root->Left != NULL)
            {
                ret += count(root->Left);
            }
            if(root->Right != NULL)
            {
                ret += count(root->Right);
            }
        }
        return ret;
    }


    virtual int height(BTreeNode<T>* root) const
    {
        int ret = 0;

        int left = 0;
        int right = 0;
        if(root != NULL)
        {

            if(root->Left != NULL)
            {
                left =  height(root->Left);

            }
            if(root->Right != NULL)
            {
                right =  height(root->Right);
            }
            ret = left > right? left : right;
            ret  += 1;
        }
        return ret;
    }

    virtual int degree(BTreeNode<T>* root) const
    {
        int ret = 0;
        int child = 0;
        int left = 0;
        int right = 0;

        if(root != NULL)
        {

            if(root->Left != NULL)
            {
                child += 1;
                left =  degree(root->Left);

            }
            if(root->Right != NULL)
            {
                child += 1;
                right =  degree(root->Right);

            }
            ret = left > right ? left : right;
            ret = ret > child ? ret : child;

        }
        return ret;
    }

    void PreOrderTraversal(BTreeNode<T>* node,LinkQueue< BTreeNode<T>*>& m_traversal)
    {
        if(node != NULL)
        {
            m_traversal.add(node);
            PreOrderTraversal(node->Left,m_traversal);
            PreOrderTraversal(node->Right,m_traversal);
        }
    }

    void InOrderTraversal(BTreeNode<T>* node,LinkQueue< BTreeNode<T>* >& m_traversal)
    {
        if(node != NULL)
        {
            InOrderTraversal(node->Left,m_traversal);
            m_traversal.add(node);
            InOrderTraversal(node->Right,m_traversal);
        }
    }

    void PostOrderTraversal(BTreeNode<T>* node,LinkQueue< BTreeNode<T>* >& m_traversal)
    {
        if(node != NULL)
        {
            PostOrderTraversal(node->Left,m_traversal);
            PostOrderTraversal(node->Right,m_traversal);
            m_traversal.add(node);
        }
    }
    void LevelOrderTraversal(BTreeNode<T>* node,LinkQueue< BTreeNode<T>* >& m_traversal)
    {
        if(node != NULL)
        {
            LinkQueue< BTreeNode<T>* > temp;
            temp.add(node);
            while(temp.length() > 0)
            {
                BTreeNode<T>* n = temp.remove();

                if(n->Left != NULL)
                {
                    temp.add(n->Left);
                }
                if(n->Right != NULL)
                {
                    temp.add(n->Right);
                }
                m_traversal.add(n);
            }
        }
    }

    void traversal(BTTraversal order,LinkQueue< BTreeNode<T>* >& q_traversal)
    {
        switch(order)
        {
        case PreOrder:
            PreOrderTraversal(root(),q_traversal);
            break;
        case Inorder:
            InOrderTraversal(root(),q_traversal);
            break;
        case PostOrder:
            PostOrderTraversal(root(),q_traversal);
            break;
        case LevelOrder:
            LevelOrderTraversal(root(),q_traversal);
            break;
        default:
            THROW_EXCEPTION(InvalidParameterException,"Invalid Parameter in traversal");
            break;
        }
    }

    BTreeNode<T>* connect(LinkQueue< BTreeNode<T>* >& queue)
    {
        BTreeNode<T>* ret = NULL;
        BTreeNode<T>* slider = NULL;

        if(queue.length() >0)
        {
            ret = queue.remove();
            slider = ret;
            slider->Left = NULL;
        }
        while(queue.length() >0)
        {
            slider->Right = queue.remove();
            slider->Right->Left = slider;
            slider = slider->Right;
        }
        slider->Right = NULL;
        return ret;

    }

    BTreeNode<T>* clone(BTreeNode<T>* root) const
    {
        BTreeNode<T>* ret = NULL;
        if(root != NULL)
        {
            ret = BTreeNode<T>::NewNode();
            if(ret != NULL)
            {
                 ret->value = root->value;
                 ret->Left = clone(root->Left);
                 ret->Right = clone(root->Right);

                 if(ret->Left != NULL)
                 {
                     ret->Left->parent = root;
                 }
                 if(ret->Right != NULL)
                 {
                     ret->Right->parent = root;
                 }
             }
             else
             {
                 THROW_EXCEPTION(NoEnoughMemoryException,"No Enough Memory in clone");
             }
         }
         else
         {
             return NULL;
         }
         return ret;
     }

     bool equal(BTreeNode<T>* lh,BTreeNode<T>* rh)
     {
         bool ret = true;
         if(lh == rh)
         {
             return ret;
         }
         if(((lh != NULL) && ( rh == NULL)) || ((lh == NULL) && ( rh != NULL)))
         {
             return false;
         }
         else
         {
             ret = (lh->value == rh->value) && equal(lh->Left,rh->Left) && equal(lh->Right,rh->Right);

         }
         return ret;
     }

     BTreeNode<T>* add(BTreeNode<T>* lh,BTreeNode<T>* rh) const
     {
         if(lh == NULL && rh != NULL)
         {
             return clone(rh);
         }
         else if(lh != NULL && rh == NULL)
         {
             return clone(lh);
         }
         else if(lh == NULL && rh == NULL)
         {
             return NULL;
         }
         else
         {
             BTreeNode<T>* node = BTreeNode<T>::NewNode();
             if(node != NULL)
             {
                 node->value = lh->value + rh->value;
                 node->Left = add(lh->Left,rh->Left);
                 node->Right = add(lh->Right,rh->Right);
                 if(node->Left != NULL)
                 {
                     node->Left->parent = node;
                 }
                 if(node->Right != NULL)
                 {
                     node->Right->parent = node;
                 }
                 return node;
             }
             else
             {
                 THROW_EXCEPTION(NoEnoughMemoryException,"No Enough Memory in add");
             }

         }

     }



public:
    bool operator == (BTree<T>& obj)
    {
        return equal(root(),obj.root());
    }
    bool operator != (BTree<T>& obj)
    {
        return !equal(root(),obj.root());
    }

    SharedPointer< BTree<T> > add(const BTree<T>& obj) const
    {
        BTree<T>* ret = new BTree();
        if(ret != NULL)
        {
            ret->m_root = add(root(),obj.root());
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"No Enough Memory in add");
        }
        return ret;
    }

    BTreeNode<T>* thread(BTTraversal order)
    {
       BTreeNode<T>* ret = NULL;
       LinkQueue< BTreeNode<T>* > queue;
       traversal(order,queue);
       ret = connect(queue);
       this->m_root = NULL;
       queue.clear();
       m_queue.clear();
       return ret;

    }

    virtual bool insert(TreeNode<T>* node)
    {
        return insert(node,BT_ANY);
    }
    virtual bool insert(TreeNode<T>* node,BTNodePos pos)
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
                BTreeNode<T>* np = this->find(node->parent);
                if( np != NULL)
                {
                    ret = insert(dynamic_cast<BTreeNode<T>*>(node),np,pos);

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
        return insert(value,parent,BT_ANY);
    }

    virtual bool insert(const T& value,TreeNode<T>* parent,BTNodePos pos)
    {
        bool ret = true;
        BTreeNode<T>* node = BTreeNode<T>::NewNode();
        if(node != NULL)
        {
            node->value = value;
            node->parent = parent;
            ret = insert(node,pos);

            if(ret == false)
            {
                delete node;
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"No Enough Memory to create new node");
        }

        return ret;
    }

    virtual SharedPointer< Tree<T> >remove(const T& value)
    {
        BTree<T>* ret = NULL;
        BTreeNode<T>* node = this->find(value);
        if(node != NULL)
        {
            remove(node,ret);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException,"Invalid Parameter in remove");
        }

        return ret;


    }

    virtual SharedPointer< Tree<T> >remove(TreeNode<T>* node)
    {
         BTree<T>* ret = NULL;
         node = this->find(node);
         if(node != NULL)
         {

             remove(dynamic_cast<BTreeNode<T>*>(node),ret);
         }
         else
         {
             THROW_EXCEPTION(InvalidParameterException,"Invalid Parameter in remove");
         }

         return ret;
    }

    virtual BTreeNode<T>* find(const T& value) const
    {
        return find(root(),value);
    }

    virtual BTreeNode<T>* find(TreeNode<T>* node) const
    {
        return find(root(),dynamic_cast<BTreeNode<T>*>(node));
    }

    virtual BTreeNode<T>* root() const
    {
        return dynamic_cast<BTreeNode<T>*>(this->m_root);
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
        m_queue.clear();
        free(root());
        this->m_root = NULL;
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
            BTreeNode<T>* node = m_queue.remove();
            if(node->Left != NULL)
            {
                m_queue.add(node->Left);
            }
            if(node->Right != NULL)
            {
                m_queue.add(node->Right);
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

    SharedPointer< Array<T> > traversal(BTTraversal order)
    {
        DynamicArray<T> * ret = NULL;

        LinkQueue< BTreeNode<T>* > q_traversal;

        traversal(order,q_traversal);

        ret = new DynamicArray<T>(q_traversal.length());
        if(ret != NULL)
        {
            for(int i = 0; i<ret->length();i++)
            {
                ret->set(i,q_traversal.remove()->value);
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"No Enough Memory in traversal");
        }

        return ret;
    }

    SharedPointer< BTree<T> > clone() const
    {
        BTree<T>* ret = new BTree<T>();
        if(ret != NULL)
        {
            ret->m_root = clone(root());
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"No Enough Memory in clone");
        }
        return ret;
    }




    ~BTree()
    {
        clear();
    }
};
}

#endif // BTREE_H
