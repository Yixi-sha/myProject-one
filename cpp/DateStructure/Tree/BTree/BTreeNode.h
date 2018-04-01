#ifndef BTREENODE_H
#define BTREENODE_H

#include "../TreeNode.h"

namespace yixi
{
enum BTNodePos
{
    BT_ANY,
    BT_LEFT,
    BT_RIGHT
};
template <typename T>
class BTreeNode : public TreeNode<T>
{

public:
    BTreeNode<T>* Left;
    BTreeNode<T>* Right;

    BTreeNode(BTreeNode<T>* m_Left = NULL,BTreeNode<T>* m_Right = NULL)
    {
        Left = m_Left;
        Right = m_Right;
    }


    static BTreeNode<T>* NewNode()
    {
        BTreeNode<T>* ret = new BTreeNode<T>();
        if(ret != NULL)
        {
            ret->m_flag = true;
        }
        return ret;
    }
};
}

#endif // BTREENODE_H
