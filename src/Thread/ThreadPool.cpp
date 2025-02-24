/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** ThreadPool
*/

#include "Thread/ThreadPool.hpp"

template <typename Task, typename Result>
thread::ThreadPool<Task, Result>::ThreadPool(size_t maxThreads) :
    _run(false), _maxThreads(maxThreads), _busyThreads(0)
{}

template <typename Task, typename Result>
thread::ThreadPool<Task, Result>::~ThreadPool()
{
    stop();
}

template <typename Task, typename Result>
size_t thread::ThreadPool<Task, Result>::getWaitingTasks()
{
    return _queue.size();
}

template <typename Task, typename Result>
size_t thread::ThreadPool<Task, Result>::getBusyThreads()
{
    return _busyThreads;
}

template <typename Task, typename Result>
template <typename... Args>
thread::Promise<Result> thread::ThreadPool<Task, Result>::addTask(Args... args)
{
    Promise<Result> promise;
    _queue.push(std::make_pair(Task(std::forward<Args>(args)...), promise));
    _cv.notify();
    return promise;
}


template <typename Task, typename Result>
void thread::ThreadPool<Task, Result>::run()
{
    _run = true;

    for (size_t i = 0; i < _maxThreads; i++) {
        _threads.emplace_back(thread::ThreadPool<Task, Result>::Worker(*this));
    }
}

template <typename Task, typename Result>
void thread::ThreadPool<Task, Result>::stop()
{
    _run = false;
    _cv.notifyAll();
    for (auto &thread : _threads) {
        if (thread.joinable())
            thread.join();
    }
}

template <typename Task, typename Result>
void thread::ThreadPool<Task, Result>::waitUntilComplete()
{
    while (!empty()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    stop();
}

template <typename Task, typename Result>
bool thread::ThreadPool<Task, Result>::isRunning()
{
    return _run;
}


template <typename Task, typename Result>
bool thread::ThreadPool<Task, Result>::empty()
{
    return _queue.empty();
}


template <typename Task, typename Result>
size_t thread::ThreadPool<Task, Result>::nbWaitingTasks()
{
    return _queue.size();
}

template <typename Task, typename Result>
bool thread::ThreadPool<Task, Result>::tryPop(std::pair<Task, Promise<Result>> &func)
{
    return _queue.tryPop(func);
}

template <typename Task, typename Result>
void thread::ThreadPool<Task, Result>::waitForTask()
{
    _cv.wait();
}

template <typename Task, typename Result>
void thread::ThreadPool<Task, Result>::addThreadIsBusy()
{
    _busyThreads++;
}

template <typename Task, typename Result>
void thread::ThreadPool<Task, Result>::addThreadIsFree()
{
    _busyThreads--;
}



////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//
// Class Worker
//
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

template <typename Task, typename Result>
thread::ThreadPool<Task, Result>::Worker::Worker(ThreadPool<Task, Result> &pool) : _pool(pool) {}

template <typename Task, typename Result>
void thread::ThreadPool<Task, Result>::Worker::operator()()
{
    while (_pool.isRunning()) {
        std::pair<Task, Promise<Result>> task;
        Result result;

        if (_pool.tryPop(task)) {
            _pool.addThreadIsBusy();
            result = task.first();
            task.second.set(result);
            _pool.addThreadIsFree();
        } else {
            _pool.waitForTask();
        }
    }
}

#include <functional>
#include "Matrix.hpp"
template class thread::ThreadPool<std::function<Matrix(void)>, Matrix>;
template thread::Promise<Matrix> thread::ThreadPool<std::function<Matrix(void)>, Matrix>::addTask<std::function<Matrix()>>(std::function<Matrix()>);
template thread::Promise<Matrix> thread::ThreadPool<std::function<Matrix(void)>, Matrix>::addTask<Matrix (*)()>(Matrix (*)());
