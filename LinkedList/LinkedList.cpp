//
// Created by trykr on 25.04.2020.
//

#include "LinkedList.h"

#include <cassert>

LinkedList::Node::Node(const ValueType& value, Node* next)
{
    this->value = value;
    this->next = next;
}

LinkedList::Node::~Node()
{
    // ничего не удаляем, т.к. агрегация
}

void LinkedList::Node::insertNext(const ValueType& value)
{
    Node* newNode = new Node(value, this->next);
    this->next = newNode;
}

void LinkedList::Node::removeNext()
{
    Node* removeNode = this->next;
    Node* newNext = removeNode->next;
    delete removeNode;
    this->next = newNext;
}

LinkedList::LinkedList() : _firstNode(nullptr), _size(0)
{

}

LinkedList::LinkedList(const LinkedList& copyList)
{
    this->_size = copyList._size;
    if (this->_size == 0) {
        this->_firstNode = nullptr;
        return;
    }

    this->_firstNode = new Node(copyList._firstNode->value);

    Node* currentNode = this->_firstNode;
    Node* currentCopyNode = copyList._firstNode;

    while (currentCopyNode->next) {
        currentNode->next = new Node(currentCopyNode->value);
        currentCopyNode = currentCopyNode->next;
        currentNode = currentNode->next;
    }
}

LinkedList& LinkedList::operator=(const LinkedList& copyList)
{
    if (this == &copyList) {
        return *this;
    }
    LinkedList bufList(copyList);
    this->_size = bufList._size;
    this->_firstNode = bufList._firstNode;

    return *this;
}

LinkedList::LinkedList(LinkedList&& moveList) noexcept
{
    this->_size = moveList._size;
    this->_firstNode = moveList._firstNode;

    moveList._size = 0;
    moveList._firstNode = nullptr;
}

LinkedList& LinkedList::operator=(LinkedList&& moveList) noexcept
{
    if (this == &moveList) {
        return *this;
    }
    forceNodeDelete(_firstNode);
    this->_size = moveList._size;
    this->_firstNode = moveList._firstNode;

    moveList._size = 0;
    moveList._firstNode = nullptr;

    return *this;
}

LinkedList::~LinkedList()
{
    forceNodeDelete(_firstNode);
}

ValueType& LinkedList::operator[](const size_t pos) const
{
    return getNode(pos)->value;
}

LinkedList::Node* LinkedList::getNode(const size_t pos) const
{
    if (pos < 0) {
        assert(pos < 0);
    }
    else if (pos >= this->_size) {
        assert(pos >= this->_size);
    }

    Node* bufNode = this->_firstNode;
    for (int i = 0; i < pos; ++i) {
        bufNode = bufNode->next;
    }

    return bufNode;
}

void LinkedList::insert(const size_t pos, const ValueType& value)
{
    if (pos < 0) {
        assert(pos < 0);
    }
    else if (pos > this->_size) {
        assert(pos > this->_size);
    }

    if (pos == 0) {
        pushFront(value);
    }
    else {
        Node* bufNode = this->_firstNode;
        for (size_t i = 0; i < pos-1; ++i) {
            bufNode = bufNode->next;
        }
        bufNode->insertNext(value);
        ++_size;
    }
}

void LinkedList::insertAfterNode(Node* node, const ValueType& value)
{
    node->insertNext(value);
}

void LinkedList::pushBack(const ValueType& value)
{
    if (_size == 0) {
        pushFront(value);
        return;
    }
    insert(_size, value);
}

void LinkedList::pushFront(const ValueType& value)
{
    _firstNode = new Node(value, _firstNode);
    ++_size;
}

void LinkedList::remove(const size_t pos)
{
    if (pos < 0)
        assert(pos< 0);

    if (pos > this->_size)
        assert(pos > this->_size);
    if (pos == 0) {
        removeFront();
    }
    else {
        Node* node = this->_firstNode;
        for (size_t i = 0; i < pos - 1; ++i) {
            node = node->next;
        }
        node->removeNext();
        this->_size--;
}
}
void LinkedList::removeNextNode(Node* node)
{
    Node *deletedNode = node->next;
    node->next = node->next->next;
    delete deletedNode;
}

long long int LinkedList::findIndex(const ValueType& value) const
{
    long long int i = 0;
    Node *currentNode = _firstNode;
    while (i < _size)
    {
        if (currentNode->value == value)
            return i;
    }
    std:: cout << "No Node" << std :: endl;
    return -1;
}

LinkedList::Node* LinkedList::findNode(const ValueType& value) const
{
    long long int i = 0;
    Node *currentNode = _firstNode;
    while (i < _size)
    {
        if (currentNode->value == value)
            return currentNode;
    }
    std:: cout << "No Node" << std :: endl;
    return nullptr;
}

void LinkedList::reverse()
{
    Node *previousNode= _firstNode;
    Node *currentNode = _firstNode->next;
    Node *nextNode = currentNode->next;
    _firstNode->next = nullptr;
    currentNode->next = previousNode;
    _lastNode = _firstNode;
    while (nextNode->next != nullptr)
    {
        previousNode = currentNode;
        currentNode = nextNode;
        nextNode = nextNode->next;
        currentNode->next = previousNode;
    }
    previousNode = currentNode;
    currentNode = nextNode;
    currentNode->next = previousNode;
    _firstNode = currentNode;
}

LinkedList LinkedList::reverse() const
{
    LinkedList reversedList = *this;
    reversedList.reverse();
    return reversedList;
}

LinkedList LinkedList::getReverseList() const
{
    LinkedList reversedList = *this;
    reversedList.reverse();
    return reversedList;
}

size_t LinkedList::size() const
{
    return _size;
}

void LinkedList::forceNodeDelete(Node* node)
{
    if (node == nullptr) {
        return;
    }

    Node* nextDeleteNode = node->next;
    delete node;
    forceNodeDelete(nextDeleteNode);
}

void LinkedList::print()
{
    Node node = *_firstNode;
    while(node.next != nullptr)
    {
        std:: cout << node.value << std::endl;
        node = *node.next;
    }
    std:: cout << node.value << std::endl;
}

void LinkedList::removeFront()
{
    Node *node = _firstNode;
    this->_firstNode = this->_firstNode->next;
    delete node;
    this->_size--;
}

void LinkedList::removeBack()
{
    Node* node = _firstNode;
    for (int i = 0; i < this->_size - 2; i++)
    {
        node = node->next;
    }
    delete this->_lastNode;
    this->_lastNode = node;
    this->_lastNode->next = nullptr;
    this->_size--;
}
