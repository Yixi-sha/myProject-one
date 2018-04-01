#ifndef STACK_H
#define STACK_H
#include "DateStructure/Object/Object.h"
#include "DateStructure/Exception/Exception.h"

namespace yixi
{
template <typename T>
class Stack : public Object
{
public:
    virtual void push(const T& e) = 0;
    virtual T pop() = 0;
    virtual T top() = 0;
    virtual void clear() = 0;
    virtual int size() = 0;
    virtual bool isEmtry() = 0;
};
}

#endif // STACK_H
