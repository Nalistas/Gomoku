/*
** EPITECH PROJECT, 2024
** gomoku
** File description:
** Promise
*/

#include "Thread/Mutex.hpp"
#include <memory>

#ifndef PROMISE_HPP_
    #define PROMISE_HPP_

namespace thread {
    template <typename T>
    class Promise {
        public:
            Promise();
            ~Promise();

            void set(T value);
            T get();

            bool isResolved();

        private:
            std::shared_ptr<std::unique_ptr<T>> _value;
            std::shared_ptr<Mutex> _mutex;
    };
}

#endif /* !PROMISE_HPP_ */
