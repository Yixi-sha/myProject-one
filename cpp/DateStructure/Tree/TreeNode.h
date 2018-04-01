#ifndef TREENODE_H
#define TREENODE_H
#include "DateStructure/Exception/Exception.h"

namespace yixi
{
template <typename T>
class TreeNode : public Object
{
protected:
    bool m_flag;
    void* operator new(unsigned int size) throw()
    {
        return Object::operator new(size);
    }

    TreeNode(const TreeNode& obj);
    TreeNode<T>& operator = (const TreeNode& obj);

public:
    T value;
    TreeNode<T>* parent;

    TreeNode(TreeNode<T>* m_parent = NULL)
    {
        this->m_flag = false;
        parent = m_parent;
    }
    bool flag()
    {
        return this->m_flag;
    }
    virtual ~TreeNode()
    {

    }

};




}

#endif // TREENODE_H
