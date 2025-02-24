/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** ConditionVariable
*/


#ifndef CONDITIONVARIABLE_HPP_
    #define CONDITIONVARIABLE_HPP_

    #include "ScopeLock.hpp"

namespace thread {
    class ConditionVariable {

        private:
            pthread_cond_t _cond;
            pthread_mutex_t _mutex;

        public:
            ConditionVariable();
            ~ConditionVariable();

            void wait();
            void notify();
            void notifyAll();

    };
}

#endif /* !CONDITIONVARIABLE_HPP_ */
