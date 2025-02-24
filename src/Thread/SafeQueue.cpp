/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** SafeQueue
*/

#include "Thread/SafeQueue.hpp"

template <typename T>
thread::SafeQueue<T>::SafeQueue()
{}

template <typename T>
thread::SafeQueue<T>::~SafeQueue()
{}

template <typename T>
size_t thread::SafeQueue<T>::size(void)
{
    return _queue.size();
}

template <typename T>
void thread::SafeQueue<T>::push(T value)
{
    ScopeLock lock(_mutex);

    _queue.push(value);
}

template <typename T>
bool thread::SafeQueue<T>::tryPop(T &value)
{
    ScopeLock lock(_mutex);
    if (_queue.empty()) {
        return false;
    }
    value = _queue.front();
    _queue.pop();
    return true;
}

template <typename T>
bool thread::SafeQueue<T>::empty(void)
{
    ScopeLock lock(_mutex);
    return _queue.empty();
}

#include <functional>
#include "Thread/Promise.hpp"
#include "Matrix.hpp"
template class thread::SafeQueue<std::pair<std::function<Matrix (void)>, thread::Promise<Matrix>>>;
