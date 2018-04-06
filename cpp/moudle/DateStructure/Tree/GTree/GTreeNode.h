#ifndef GTREENODE_H
#define GTREENODE_H

#include "DateStructure/List/ListChain/linklist.h"
#include "../TreeNode.h"

namespace yixi
{
template <typename T>
class GTreeNode : public TreeNode<T>
{

public:
    LinkList<GTreeNode<T>*> child;

    static GTreeNode<T>* NewNode()
    {
        GTreeNode<T>* ret = new GTreeNode<T>();
        if(ret != NULL)
        {
            ret->m_flag = true;
        }
        return ret;
    }

};
}
#endif // GTREENODE_H
