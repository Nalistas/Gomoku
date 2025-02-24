/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** SafeQueue
*/


#ifndef SAFEQUEUE_HPP_
    #define SAFEQUEUE_HPP_

    #include "Mutex.hpp"
    #include "ScopeLock.hpp"

    #include <queue>
    #include <functional>

namespace thread {  

    template <typename T>
    class SafeQueue {
        public:
            SafeQueue();
            ~SafeQueue();

            void push(T value);
            bool tryPop(T &value);
            bool empty(void);
            size_t size(void);

        private:
            std::queue<T> _queue;
            Mutex _mutex;
    };
}

template class thread::SafeQueue<int>;
template class thread::SafeQueue<std::function<void()>>;


#endif /* !SAFEQUEUE_HPP_ */
