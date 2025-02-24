/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** ScopeLock
*/

#include "Thread/ScopeLock.hpp"

thread::ScopeLock::ScopeLock(Mutex &mutex) :
    _mutex(mutex)
{
    _mutex.lock();
}

thread::ScopeLock::~ScopeLock()
{
    _mutex.unlock();
}

void thread::ScopeLock::lock()
{
    _mutex.lock();
}

void thread::ScopeLock::unlock()
{
    _mutex.unlock();
}

void thread::ScopeLock::trylock()
{
    _mutex.trylock();
}
