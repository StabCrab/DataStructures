#include "LinkedList.h"
LinkedList::Node::Node(const ValueType &value, LinkedList::Node *next, LinkedList::Node *previous)
{
    this->value = value;
    this->next = next;
    this->previous = previous;
}

LinkedList::Node::~Node()
{

}

void LinkedList::Node::insertNext(const ValueType &value)
{
    Node* newNode = new Node(value, this->next, this);
    this->next->previous = newNode;
    this->next = newNode;
}
void LinkedList::Node::removeNext()
{
    Node* newNext = this->next->next;
    newNext->previous = this;
    delete this->next;
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
    if (this->_size == 0) {
        this->_lastNode = nullptr;
        this->_firstNode = nullptr;
        return;
    }

    this->_firstNode = new Node(copyList._firstNode->value);

    Node* currentNode = this->_firstNode;
    Node* currentCopyNode = copyList._firstNode;

    while (currentCopyNode->next) {
        currentNode->next = new Node(currentCopyNode->next->value);
        currentNode->next->previous = currentNode;
        currentCopyNode = currentCopyNode->next;
        currentNode = currentNode->next;
    }
    this->_lastNode = currentNode;
}
LinkedList& LinkedList::operator=(const LinkedList& copyList)
{
    if (this == &copyList)
    {
        return *this;
    }
    this->_size = copyList._size;
    this->_lastNode = copyList._lastNode;
    this->_firstNode = copyList._firstNode;
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
    this->_size++;
}
void LinkedList::pushBack(const ValueType& value)
{
    this->_size++;
    if (this->_size == 1)
    {
        _firstNode = new Node(value, nullptr, nullptr);
        _lastNode = _firstNode;

    }
    else
    {
        Node* newLastNode = new Node(value, nullptr, _lastNode);
        _lastNode->next = newLastNode;
        _lastNode = newLastNode;
    }
}
void LinkedList::pushFront(const ValueType& value)
{
    ++_size;
    if (this->_size == 1)
    {
        _firstNode = new Node(value, _firstNode, nullptr);
    }
    else
    {
        Node* newFirst = new Node(value, _firstNode, nullptr);
        _firstNode->previous = newFirst;
        _firstNode = newFirst;
    }
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
        erasedNode->next->previous = currentNode;
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
    Node* erasedNode = node->next;
    erasedNode->next->previous = node;
    node->next = erasedNode->next;
    delete erasedNode;
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
    Node* currentNode = this->_firstNode;
    Node* buf = nullptr;
    for (int i = 0; i < this->_size; i++)
    {
        currentNode->previous = currentNode->next;
        currentNode->next = buf;
        buf = currentNode;
        currentNode = currentNode->previous;
    }
    buf = _firstNode;
    _firstNode = _lastNode;
    _lastNode = buf;
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

void LinkedList::print() {
    Node node = *_firstNode;
    while(node.next != nullptr)
    {
        std:: cout << node.value << std::endl;
        node = *node.next;
    }
    std:: cout << node.value << std::endl;
}
void LinkedList::printBackwards()
{
    Node node = *_lastNode;
    while(node.previous != nullptr)
    {
        std:: cout << node.value << std:: endl;
        node = *node.previous;
    }
    std:: cout << node.value << std:: endl;
}

void LinkedList::Swap(LinkedList::Node *a, LinkedList::Node *b)
{
    if (!a || !b || a == b)
        exit;
    Node* bufnode = a;
    b = bufnode;
    a = b;

}
