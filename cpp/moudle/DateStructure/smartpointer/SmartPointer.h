#ifndef SMARTPOINTER
#define SMARTPOINTER
#include "DateStructure/smartpointer/Pointer.h"
namespace yixi
{
template<typename T>
class SmartPointer:public pointer<T>
{
public:
    SmartPointer(T *p=NULL) : pointer<T>(NULL)
    {

    }
    SmartPointer(const SmartPointer<T>& obj) : pointer<T>(NULL)
    {
        this->m_pointer=obj.m_pointer;
        const_cast<SmartPointer<T>&>(obj).m_pointer=NULL;
    }
    SmartPointer<T>& operator=(const SmartPointer<T>& obj)
    {
        if(this!=&obj)
        {
            T* p = this->m_pointer;

            this-> m_pointer=obj.m_pointer;
            const_cast<SmartPointer<T>&>(obj).m_pointer=NULL;
            delete p ;
        }
        return *this;
    }
    ~SmartPointer()
    {
        delete this->m_pointer;
    }
};
}

#endif // SMARTPOINTER

