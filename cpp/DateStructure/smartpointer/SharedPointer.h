#ifndef SHAREDPOINTER_H
#define SHAREDPOINTER_H

#include "Pointer.h"
#include "DateStructure/Exception/Exception.h"
#include <cstdlib>

namespace yixi
{
template <typename T>
class SharedPointer : public pointer<T>
{
protected:
    int* m_ref;

    void assign(const SharedPointer<T>& obj)
    {
        this->m_ref = obj.m_ref;
        this->m_pointer = obj.m_pointer;
        if(this->m_ref)
        {
            *(this->m_ref) = *(this->m_ref) + 1;
        }
    }
public:
    SharedPointer(T* p = NULL): m_ref(NULL)
    {
        if( p )
        {
            this->m_ref = static_cast<int*>(std::malloc(sizeof(int)));

            if( this->m_ref)
            {
                *(this->m_ref) = 1;
                this->m_pointer = p;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException,"No Enough Memory to create m_ref");
            }
        }
        else
        {
           this->m_ref = NULL;
        }
    }

    SharedPointer(const SharedPointer<T>& obj ) : pointer<T>(NULL)
    {
        assign(obj);

    }

    SharedPointer<T>& operator = (const SharedPointer<T>& obj)
    {
        if(this != &obj)
        {
            this->clear();
            assign(obj);
        }
        return *this;
    }

    void clear()
    {
      T* toDel = this->m_pointer;
      int *ref = this->m_ref;

      this->m_pointer = NULL;
      this->m_ref = NULL;

      if(ref)
      {
          (*ref) --;
          if( (*ref) == 0)
          {
            delete toDel;
            free (ref);
          }
      }
    }

    ~SharedPointer()
    {
        this->clear();
    }

};

template <typename T>
bool operator == (const SharedPointer<T> p,const SharedPointer<T> r)
{
    return (p.get() == r.get());
}

template <typename T>
bool operator != (const SharedPointer<T> p,const SharedPointer<T> r)
{
    return (p.get() != r.get());
}



}

#endif // SHAREDPOINTER_H
