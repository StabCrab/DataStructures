#include "LinkedList.h"
LinkedList::Node::Node(const ValueType &value, LinkedList::Node *next, LinkedList::Node *previous)
{
    this->next = next;
    this->previous = previous;
    this->value = value;
}

LinkedList::Node::~Node()
{

}

void LinkedList::Node::insertNext(const ValueType &value)
{
    Node* newNode = new Node(value, this->next);
    this->next = newNode;
    newNode->previous = this;
}
void LinkedList::Node::removeNext()
{
    Node* removeNode = this->next;
    Node* newNext = removeNode->next;
    delete removeNode;
    this->next = newNext;
}

LinkedList::LinkedList()
{
    _size = 0;
    _firstNode = nullptr;
    _lastNode = nullptr;
}

LinkedList::LinkedList(const LinkedList &copyList)
{
    this->_size = copyList._size;
    if (this->_size == 0)
    {
        this->_lastNode = nullptr;
        this->_firstNode = nullptr;
        return;
    }

    this->_lastNode = new Node(copyList._lastNode->value);
    this->_firstNode= new Node (copyList._firstNode->value);
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
    this->_lastNode = bufList._lastNode;
    this->_firstNode = bufList._firstNode;
    return *this;
}
LinkedList::LinkedList(LinkedList&& moveList) noexcept
{
    this->_size = moveList._size;
    this->_lastNode= moveList._lastNode;
    this->_firstNode = moveList._firstNode;

    moveList._size = 0;
    moveList._firstNode = nullptr;
    moveList._lastNode = nullptr;
}
LinkedList& LinkedList::operator=(LinkedList&& moveList) noexcept
{
    if (this == &moveList) {
        return *this;
    }
//    forceNodeDelete(_lastNode);
    this->_size = moveList._size;
    this->_lastNode = moveList._lastNode;
    this->_firstNode = moveList._firstNode;

    moveList._size = 0;
    moveList._lastNode= nullptr;
    moveList._firstNode = nullptr;

    return *this;
}
LinkedList::~LinkedList()
{
    //forceNodeDelete(_firstNode);
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

    if (pos == 0)
    {
        pushFront(value);
    }
    else
        {
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
    this->_size++;
    if (this->_size == 1)
    {
        _firstNode = new Node(value, _firstNode, nullptr);
        _lastNode = _firstNode;

    }
    else
    {
        _lastNode->insertNext(value);
        Node *newLastNode = _lastNode->next;
        newLastNode->previous = _lastNode;
        _lastNode = newLastNode;
    }
}
void LinkedList::pushFront(const ValueType& value)
{
    _firstNode = new Node(value, _firstNode, nullptr);
    ++_size;
}
void LinkedList::remove(const size_t pos)// Посмотреть
{
    if (pos < 0)
    {
        assert(pos < 0);
    }
    else if (pos > this->_size)
    {
        assert(pos > this->_size);
    }
    if (pos == 0)
    {
        this->removeFront();
    }
    else if (pos == this->size() - 1)
    {
        this->removeBack();
    }
    else
    {
        Node* currentNode = _firstNode;

        for (int i = 0; i < pos - 1; i++)
        {
            currentNode = currentNode->next;
        }

        Node* erasedNode = currentNode->next;
        currentNode->next = erasedNode->next;
        delete erasedNode;
        this->_size--;
    }

}

size_t LinkedList::size() const
{
    return this->_size;
}

void LinkedList::removeNextNode(LinkedList::Node *node)
{

}

void LinkedList::removeFront()
{
    this->_firstNode = this->_firstNode->next;
    delete _firstNode->previous;
    this->_firstNode->previous = nullptr;
    this->_size--;
}

void LinkedList::removeBack()
{
    this->_lastNode = this->_lastNode->previous;
    delete _lastNode->next;
    this->_lastNode->next = nullptr;
    this->_size--;
}

long long int LinkedList::findIndex(const ValueType &value) const {
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
    Node *nextNode;
    Node *currentNode;
    Node *previousNode;
    previousNode = _firstNode;
    currentNode = _firstNode->next;
    nextNode = currentNode->next;
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
    nextNode = nextNode->next;
    currentNode->next = previousNode;
    _firstNode = currentNode;
}

LinkedList LinkedList::reverse() const
{
    LinkedList reversedList = *this;
    Node *nextNode;
    Node *currentNode;
    Node *previousNode;
    previousNode =reversedList. _firstNode;
    currentNode = reversedList._firstNode->next;
    nextNode = currentNode->next;
    reversedList._firstNode->next = nullptr;
    currentNode->next = previousNode;
    reversedList._lastNode = reversedList._firstNode;
    while (nextNode->next != nullptr)
    {
        previousNode = currentNode;
        currentNode = nextNode;
        nextNode = nextNode->next;
        currentNode->next = previousNode;
    }
    previousNode = currentNode;
    currentNode = nextNode;
    nextNode = nextNode->next;
    currentNode->next = previousNode;
    reversedList._firstNode = currentNode;
    return reversedList;
}

LinkedList LinkedList::getReverseList() const
{
    LinkedList reversedList = *this;
    Node *nextNode;
    Node *currentNode;
    Node *previousNode;
    previousNode =reversedList. _firstNode;
    currentNode = reversedList._firstNode->next;
    nextNode = currentNode->next;
    reversedList._firstNode->next = nullptr;
    currentNode->next = previousNode;
    reversedList._lastNode = reversedList._firstNode;
    while (nextNode->next != nullptr)
    {
        previousNode = currentNode;
        currentNode = nextNode;
        nextNode = nextNode->next;
        currentNode->next = previousNode;
    }
    previousNode = currentNode;
    currentNode = nextNode;
    nextNode = nextNode->next;
    currentNode->next = previousNode;
    reversedList._firstNode = currentNode;
    return reversedList;
}

void LinkedList::forceNodeDelete(LinkedList::Node *node)
{

    if (node == nullptr)
    {
        return;
    }

    Node* nextDeleteNode = node->next;
    delete node;
    forceNodeDelete(nextDeleteNode);
}
