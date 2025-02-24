/*
** EPITECH PROJECT, 2024
** &test
** File description:
** Promise
*/

#include "Thread/Promise.hpp"
#include "Thread/Mutex.hpp"
#include <memory>
#include <iostream>

template <typename T>
thread::Promise<T>::Promise() :
    _value(std::make_shared<std::unique_ptr<T>>()),
    _mutex(std::make_shared<Mutex>())
{
    this->_mutex->lock();
}

template <typename T>
thread::Promise<T>::~Promise()
{}

template <typename T>
void thread::Promise<T>::set(T value)
{
    *this->_value = std::make_unique<T>(value);
    this->_mutex->unlock();
}

template <typename T>
T thread::Promise<T>::get()
{
    this->_mutex->lock();
    T value = **(this->_value);
    this->_mutex->unlock();
    return value;
}

template <typename T>
bool thread::Promise<T>::isResolved()
{
    return this->_mutex->isLocked();
}

#include "Matrix.hpp"

template class thread::Promise<Matrix>;
