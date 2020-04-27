//
// Created by trykr on 25.04.2020.
//

#include "VectorStack.h"

VectorStack::VectorStack(const ValueType* valueArray, const size_t arraySize)
{
    this->_data = new ValueType [arraySize];
    for (int i = 0; i < arraySize; i++)
    {
        this->_data[i] = valueArray[i];
    }
    this->_capacity = arraySize;
    this->_size = 0;
}
VectorStack::VectorStack()
{
    this->_data = new ValueType[0];
    this->_capacity = 0;
    this->_size = 0;
}
VectorStack::~VectorStack()
{
    delete [] this->_data;
}
void VectorStack::push(const ValueType &value)
{
    if (this->_size == this->_capacity)
    {
        ValueType* newData = new ValueType[this->_capacity + 1];
        for (int i = 0; i < this->_size; i++)
            newData[i] = this->_data[i];
        newData[this->_size] = value;
        delete[] this->_data;
        this->_data = newData;
        this->_size++;
        this->_capacity++;
    }
    else
    {
        this->_data[this->_size] = value;
        this->_size++;
    }
}
void VectorStack::pop()
{
    this->_size--;
    ValueType* newData = new ValueType[this->_capacity];
    for(int i = 0; i < this->_size; i++)
    {
        newData[i] = this->_data[i];
    }
    delete[] this->_data;
    this->_data = newData;
}
ValueType& VectorStack::top() const
{
    return this->_data[this->_size - 1];
}

size_t VectorStack::size() const {
    return this->_size;
}
bool VectorStack::isEmpty() const
{
    return this->_size == 0;
}
