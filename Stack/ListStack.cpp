//
// Created by trykr on 25.04.2020.
//
#include "ListStack.h"
ListStack::Node::Node(const ValueType &value, ListStack::Node *next)
{
    this->value = value;
    this->next = next;
}
ListStack::Node::~Node()
{

}
ListStack::ListStack(const ValueType *valueArray, size_t arraySize)
{
    this->_size = arraySize;
    Node* currentNode;
    this->_firstNode = currentNode;
    for (int i = 0; i < arraySize; i++)
    {
        currentNode->value = valueArray[i];
    }
    this->_lastNode = currentNode;
}

ListStack::ListStack()
{
    _size = 0;
    _lastNode = nullptr;
    _firstNode = nullptr;
}

ListStack::~ListStack()
{

}

void ListStack::push(const ValueType &value)
{
    if (this->_size == 0)
        _firstNode = new Node(value, _firstNode);
    ++_size;
}

void ListStack::pop()
{
    Node* node = _firstNode;
    for (int i = 0; i < this->_size - 1; i++)
    {
        node = node->next;
    }
    node->next = nullptr;
    delete _lastNode;
    _lastNode = node;
}

ValueType &ListStack::top() const {
    return this->_lastNode->value;
}

size_t ListStack::size() const
{
    return this->_size;
}

bool ListStack::isEmpty() const {
    return this->_size == 0;
}

