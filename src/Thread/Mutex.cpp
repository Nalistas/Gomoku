/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** Mutex
*/

#include "Thread/Mutex.hpp"

thread::Mutex::Mutex() :
    _state(false)
{
    pthread_mutex_init(&_mutex, nullptr);
}

thread::Mutex::~Mutex()
{
    pthread_mutex_unlock(&_mutex);
    pthread_mutex_destroy(&_mutex);
}

void thread::Mutex::lock()
{
    pthread_mutex_lock(&_mutex);
    _state = true;
}

void thread::Mutex::unlock()
{
    pthread_mutex_unlock(&_mutex); 
    _state = false;
}

void thread::Mutex::trylock()
{
    if (!_state) {
        pthread_mutex_trylock(&_mutex);
        _state = true;
    }
}

bool thread::Mutex::isLocked()
{
    return _state;
}
