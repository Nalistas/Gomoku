/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** ConditionVariable
*/

#include "Thread/ConditionVariable.hpp"

thread::ConditionVariable::ConditionVariable()
{
    pthread_cond_init(&_cond, NULL);
    pthread_mutex_init(&_mutex, NULL);
}

thread::ConditionVariable::~ConditionVariable()
{
    pthread_cond_destroy(&_cond);
    pthread_mutex_destroy(&_mutex);
}

void thread::ConditionVariable::wait()
{
    pthread_mutex_lock(&_mutex);
    pthread_cond_wait(&_cond, &_mutex);
    pthread_mutex_unlock(&_mutex);
}

void thread::ConditionVariable::notify()
{
    pthread_mutex_lock(&_mutex);
    pthread_cond_signal(&_cond);
    pthread_mutex_unlock(&_mutex);
}

void thread::ConditionVariable::notifyAll()
{
    pthread_mutex_lock(&_mutex);
    pthread_cond_broadcast(&_cond);
    pthread_mutex_unlock(&_mutex);
}
