//
// Created by trykr on 25.04.2020.
//

#include "Stack.h"
#include "ListStack.h"
#include "VectorStack.h"
#include "StackImplementation.h"

#include <stdexcept>

Stack::Stack(StackContainer container)
        : _containerType(container)
{
    switch (container)
    {
        case StackContainer::List: {
            _pimpl = new ListStack();	// конкретизируйте под ваши конструкторы, если надо
            break;
        }
        case StackContainer::Vector: {
            _pimpl = new VectorStack();	// конкретизируйте под ваши конструкторы, если надо
            break;
        }
        default:
            throw std::runtime_error("Неизвестный тип контейнера");
    }
}

Stack::Stack(const ValueType* valueArray, const size_t arraySize, StackContainer container)
{
    switch (container)
    {
        case StackContainer::List: {
            _pimpl = new ListStack();	// конкретизируйте под ваши конструкторы, если надо
            break;
        }
        case StackContainer::Vector: {
            _pimpl = new VectorStack(valueArray, arraySize);	// конкретизируйте под ваши конструкторы, если надо
            break;
        }
        default:
            throw std::runtime_error("Неизвестный тип контейнера");
    }// принцип тот же, что и в прошлом конструкторе
}

Stack::Stack(const Stack& copyStack)
{
   *_pimpl = *(copyStack._pimpl);
}

Stack& Stack::operator = (const Stack& copyStack)
{
    if (this == &copyStack)
        return *this;
    this->_containerType = copyStack._containerType;
    delete this->_pimpl;
    switch (this->_containerType)
    {
        case StackContainer::List: {
            _pimpl = new ListStack(
                    *(dynamic_cast<ListStack *>(copyStack._pimpl)));    // конкретизируйте под ваши конструкторы, если надо
            break;
        }
        case StackContainer::Vector: {
            _pimpl = new VectorStack(
                    *(dynamic_cast<VectorStack *>(copyStack._pimpl)));    // конкретизируйте под ваши конструкторы, если надо
            break;
        }
        default:
            throw std::runtime_error("Неизвестный тип контейнера");
    }
    return *this;
}

Stack::~Stack()
{
    delete _pimpl;		// композиция!
}

void Stack::push(const ValueType& value)
{
    // можно, т.к. push определен в интерфейсе
    _pimpl->push(value);
}

void Stack::pop()
{
    _pimpl->pop();
}

const ValueType& Stack::top() const
{
    return this->_pimpl->top();
}

bool Stack::isEmpty() const
{
    return _pimpl->isEmpty();
}

size_t Stack::size() const
{
    return _pimpl->size();
}
