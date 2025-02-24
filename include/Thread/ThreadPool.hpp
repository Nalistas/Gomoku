/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** ThreadPool
*/


#ifndef THREADPOOL_HPP_
    #define THREADPOOL_HPP_

    #include "Mutex.hpp"
    #include "SafeQueue.hpp"
    #include "ConditionVariable.hpp"
    #include "Thread/ScopeLock.hpp"
    #include "Thread/Promise.hpp"

    #include <thread>
    #include <functional>
    #include <vector>

namespace thread {
    template <typename Task, typename Result>
    class ThreadPool {


        public:
            ThreadPool(size_t maxThreads = 4);
            ~ThreadPool();


            ////////////////////////////////////////////////////////
            // Functions for the user
            ////////////////////////////////////////////////////////
            void run();
            void stop();
            void waitUntilComplete();
            bool isRunning();
            template <typename... Args>
            Promise<Result> addTask(Args...);

            ////////////////////////////////////////////////////////
            // Statistics
            ////////////////////////////////////////////////////////
            size_t getBusyThreads();
            size_t getWaitingTasks();


        private:
            ////////////////////////////////////////////////////////
            // Attributes
            ////////////////////////////////////////////////////////
            SafeQueue<std::pair<Task, Promise<Result>>> _queue;
            std::vector<std::thread> _threads;
            ConditionVariable _cv;
            Mutex _mutex;

            bool _run;
            size_t _maxThreads;
            size_t _busyThreads;


            ////////////////////////////////////////////////////////
            // Functions for the thread
            ////////////////////////////////////////////////////////
            bool tryPop(std::pair<Task, Promise<Result>> &task);
            bool empty();
            size_t nbWaitingTasks();
            void waitForTask();
            void addThreadIsBusy();
            void addThreadIsFree();



            class Worker {
                public:
                    Worker(ThreadPool<Task, Result> &pool);
                    ~Worker() = default;
                    void operator()();
                private:
                    ThreadPool<Task, Result> &_pool;
            };
    };
}

#endif /* !THREADPOOL_HPP_ */
