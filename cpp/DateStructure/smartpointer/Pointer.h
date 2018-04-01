#ifndef POINTER_H
#define POINTER_H

#include "DateStructure/Object/Object.h"
namespace yixi
{
template <typename T>
class pointer : public Object
{
protected:
    T* m_pointer;
public:
    pointer(const pointer<T>& obj)
    {
        (void)obj;
    }
    pointer(T* p = NULL)
    {
        m_pointer = p;
    }

    T *operator->()
    {
        return m_pointer;
    }

    T& operator*()
    {
        return *m_pointer;
    }

    T *operator->() const
    {
        return m_pointer;
    }

    T& operator*() const
    {
        return *m_pointer;
    }

    bool isNull() const
    {
        return (m_pointer==NULL);
    }
    T *get() const
    {
        return m_pointer;
    }
};
}

#endif // POINTER_H
