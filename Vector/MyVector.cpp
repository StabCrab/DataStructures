#include <cstring>
#include "MyVector.h"
#include "iostream"

MyVector::MyVector(size_t size, ResizeStrategy resizeStrategy, float coef)
{
    if (size == 0)
    {
        this->_size = size;
        this->_capacity = 1;
        this->_data = new ValueType[this->_capacity];
        this->_strategy = resizeStrategy;
        this->_coef = coef;
    }
    else
    {
        if (resizeStrategy == ResizeStrategy::Additive)
        {
            this->_size = size;
            this->_capacity = size + round(coef);
            this->_data = new ValueType[this->_capacity];
            this->_strategy = ResizeStrategy::Additive;
            this->_coef = coef;
            for (int i = 0; i < size; i++)
            {
                this->_data[i] = 0.0;
            }
        }
        else
        {
            this->_size = size;
            this->_capacity = round(size * coef);
            this->_data = new ValueType[this->_capacity];
            this->_strategy = ResizeStrategy :: Multiplicative;
            this->_coef = coef;
            for (int i = 0; i < size; i++)
            {
                this->_data[i] = 0.0;
            }
        }
    }
}

MyVector::MyVector(size_t size, ValueType value, ResizeStrategy resizeStrategy, float coef)
{
    if (size == 0)
    {
        this->_size = size;
        this->_capacity = 1;
        this->_data = new ValueType[_capacity];
        this->_strategy = resizeStrategy;
        this->_coef = coef;
    }
    else
    {
        if (resizeStrategy == ResizeStrategy::Additive)
        {
            this->_size = size;
            this->_capacity = size + round(coef);
            this->_data = new ValueType[_capacity];
            this->_strategy = ResizeStrategy::Additive;
            this->_coef = coef;
            for (int i = 0; i < size; i++)
            {
                this->_data[i] = value;
            }
        }
        else
        {
            this->_size = size;
            this->_capacity = round(size * coef);
            this->_data = new ValueType[_capacity];
            this->_strategy = ResizeStrategy::Multiplicative;
            this->_coef = coef;
            for (int i = 0; i < size; i++)
            {
                this->_data[i] = value;
            }
        }
    }
}

MyVector::MyVector(const MyVector &copy)
{
    ValueType* newData = new ValueType(copy._size);
    for (int i = 0; i < copy._size; i++)
    {
        newData[i] = copy._data[i];
    }
    this->_data = newData;
    this->_strategy = copy._strategy;
    this->_capacity = copy._capacity;
    this->_size = copy._size;
}

MyVector &MyVector::operator = (const MyVector &copy){
    if (this == &copy)
        return *this;
    ValueType* newData = new ValueType[copy._capacity];
    for (int i = 0; i < copy._size; i++)
    {
        newData[i] = copy._data[i];
        std::cout << newData[i] << std::endl;
    }
    delete[] this->_data;
    this->_data = newData;
    this->_strategy = copy._strategy;
    this->_capacity = copy._capacity;
    this->_size = copy._size;
    this->_coef = copy._coef;
    return *this;
}

MyVector::~MyVector()
{
    delete[] _data;
}

size_t MyVector::capacity() const {
    return _capacity;
}

size_t MyVector::size() const {
    return _size;
}

float MyVector::loadFactor() {
    if (this->_capacity == 0)
        return 0;
    else
        return this->_size / this->_capacity;
}

ValueType &MyVector::operator[](const size_t i) const
{
    return this->_data[i];
}

void MyVector::pushBack(const ValueType &value)
{
    if(this->_capacity < this->_size + 1)
    {
        reserve(this->_capacity + 1);
    }
    this->_data[_size] = value;
    this->_size++;
}

void MyVector::insert(const size_t i, const ValueType &value)
{
    if (loadFactor() < 1)
    {
        ValueType* newData = new ValueType[this->_capacity];
        for (int j = 0; j < i; j++)
        {
            newData[j] = this->_data[j];
        }
        newData[i] = value;
        for(int j = i + 1; j < this->_size + 1; j++)
        {
            newData[j] = this->_data[j - 1];
        }
        delete[] this->_data;
        this->_data = newData;
        this->_size++;
    }
    else
    {
        ValueType* newData = new ValueType[this->_capacity + 1];
        for (int j = 0; j < i; j++)
        {
            newData[j] = this->_data[j];
        }
        newData[i] = value;
        for(int j = i + 1; j < this->_size + 1; j++)
        {
            newData[j] = this->_data[j - 1];
        }
        delete[] this->_data;
        this->_data = newData;
        this->_size++;
        this->_capacity++;
    }
}

void MyVector::insert(const size_t i, const MyVector &value)
{
    if (this->_capacity - (this->_size + value._size) <= 0)
    {
        ValueType* newData = new ValueType[this->_capacity];
        for (int j = 0; j < i; j++)
        {
            newData[j] = this->_data[j];
        }
        for (int j = i; j < i + value._size; j++)
        {
            newData[j] = value[j - i];
        }
        for (int j = i + value._size; j < this->_size + value._size; j++)
        {
            newData[j] = this->_data[j - value._size];
        }
        delete[] this->_data;
        this->_data = newData;
        this->_size += value._size;
    }
    else
    {
        ValueType* newData = new ValueType[this->_size + value._size];
        for (int j = 0; j < i; j++)
        {
            newData[j] = this->_data[j];
        }
        for (int j = i; j < i + value._size; j++)
        {
            newData[j] = value[j - i];
        }
        for (int j = i + value._size; j < this->_size + value._size; j++)
        {
            newData[j] = this->_data[j - value._size];
        }
        delete[] this->_data;
        this->_capacity += value._size;
        this->_size += value._size;
        this->_data = newData;
    }
}

void MyVector::popBack()
{
    this->_size--;
    ValueType* newData = new ValueType();
    for(int i = 0; i < this->_size; i++)
    {
        newData[i] = this->_data[i];
    }
    delete[] this->_data;
    this->_data = newData;
}

void MyVector::erase(const size_t i)
{
    ValueType* newData = new ValueType[this->_capacity];
    for (int j = 0; j < i; j++)
    {
        newData[j] = this->_data[j];
    }
    for (int j = i; j < this->_size - 1; j++)
    {
        newData[j] = this->_data[j + 1];
    }
    delete[] this->_data;
    this->_data = newData;
    this->_size--;
}

void MyVector::erase(const size_t i, const size_t len)
{
    ValueType* newData = new ValueType[this->_capacity];
    for (int j = 0; j < i; j++)
    {
        newData[j] = this->_data[j];
    }
    for (int j = i; j < this->_size - len; j++)
    {
        newData[j] = this->_data[j+ len];
    }
    delete[] this->_data;
    this->_data = newData;
    this->_size-= len;
}

long long int MyVector::find(const ValueType &value, bool isBegin) const
{
    if (isBegin)
    {
        for (size_t i = 0; i < this->_size; i++)
        {
            if (this->_data[i] == value)
                return i;
        }
        return -1;
    }
    else
    {
        for (size_t i = this->_size - 1; i > -1; i--)
        {
            if (this->_data[i] == value)
                return i;
        }
        return -1;
    }
}


void MyVector::reserve(const size_t capacity)
{
    if (capacity < this->_size)
    {
        this->_size = capacity;
        this->_capacity = capacity;
    }
    else
        this->_capacity = capacity;
    ValueType* newData = new ValueType[capacity];
    for (int i = 0; i < this->_size; i++)
    {
        newData[i] = this->_data[i];
    }
    delete[] this->_data;
    this->_data = newData;
}

void MyVector::resize(const size_t size, const ValueType value)
{
    if (this->_size == size)
        return;
    if (this->_size < size)
    {
        ValueType* newData = new ValueType[size];
        for (int i = 0; i < this->_size; i++)
        {
            newData[i] = this->_data[i];
        }
        for (int i = this->_size; i < size; i++)
        {
            newData[i] = value;
        }
        delete[] this->_data;
        this->_data = newData;
        this->_size = size;
    }
    if (this->_size > size)
    {
        ValueType* newData = new ValueType[size];
        for (int i = 0; i < size; i++)
        {
            newData[i] = this->_data[i];
        }
        delete[] this->_data;
        this->_data = newData;
        this->_size = size;
        this->_capacity = size;
    }
}

void MyVector::clear()
{
    this->_size = 0;
    delete[] this->_data;
    this->_data = new ValueType [this->_capacity];
}

MyVector::Iterator::~Iterator()
{

}
bool MyVector::Iterator::operator==(const Iterator &i)
{
    return this->ptr == i.ptr;
}
bool MyVector::Iterator::operator!=(const Iterator &i)
{
    return this->ptr != i.ptr;
}
MyVector::Iterator & MyVector:: Iterator::operator++()
{
    this->ptr++;
    return *this;
}
MyVector::Iterator & MyVector:: Iterator::operator--()
{
    this->ptr--;
    return *this;
}

MyVector::Iterator::Iterator(ValueType *ptr)
{
    this->ptr = ptr;
}

ValueType MyVector::Iterator::operator*() {
    return *this->ptr;
}

ValueType *MyVector::Iterator::operator->() {
    return this->ptr;
}


MyVector::Iterator MyVector::begin()
{
    return Iterator(&this->_data[0]);
}

const MyVector::Iterator MyVector::cbegin() {
    return Iterator(&this->_data[0]);
}
const MyVector::Iterator MyVector::cend()
{
    return Iterator(&this->_data[_size - 1]);
}
MyVector::Iterator MyVector::end()
{
    return Iterator(&this->_data[this->_size - 1]);
}

ValueType MyVector::getValue(Iterator i)
{
    return *i.ptr;
}

void MyVector::setValue(MyVector::Iterator i, ValueType value)
{
    *i.ptr = value;
}

void MyVector::sortedSquares( SortedStrategy strategy) {
    ValueType* vec  = new ValueType[this->_size];
    if (strategy == SortedStrategy::Descending)
    {
        int i = 0;
        int j = this->size() - 1;
        int k = 0;
        while(this->_data[i] < 0 && this->_data[j] >= 0)
        {
            if (abs(this->_data[i]) >= abs(this->_data[j]))
            {
                vec[k] = this->_data[i] * this->_data[i];
                //std:: cout << vector._data[k] << std::endl;
                i++;
                k++;
            }
            else
            {
                vec[k] = this->_data[j] * this->_data[j];
                //std:: cout << vector._data[k] << std:: endl;
                j--;
                k++;
            }
        }
        while(this->_data[i] < 0)
        {
            vec[k] = this->_data[i] * this->_data[i];
            i++;
            k++;
        }
        while(this->_data[j] >= 0)
        {
            vec[k] = this->_data[j] * this->_data[j];
            j--;
            k++;
        }
    }
    else
    {

        int i = 0;
        int j = this->size() - 1;
        int k = this->size() - 1;
        while(this->_data[i] < 0 && this->_data[j] >= 0)
        {
            if (abs(this->_data[i]) >= abs(this->_data[j]))
            {
                vec[k] = this->_data[i] * this->_data[i];
                //std:: cout << vector._data[k] << std::endl;
                i++;
                k--;
            }
            else
            {
                vec[k] = this->_data[j] * this->_data[j];
                //std:: cout << vector._data[k] << std:: endl;
                j--;
                k--;
            }
        }
        while(this->_data[i] < 0)
        {
            vec[k] = this->_data[i] * this->_data[i];
            i++;
            k--;
        }
        while(this->_data[j] >= 0)
        {
            vec[k] = this->_data[j] * this->_data[j];
            j--;
            k--;
        }
    }
    delete[] this->_data;
    this->_data = vec;
}

MyVector::MyVector(MyVector &&moveVec) noexcept
{
    _data = moveVec._data;
    _size = moveVec._size;
    _capacity = moveVec._capacity;
    moveVec._data = nullptr;
    moveVec._capacity = 0;
    moveVec._size = 0;
}
