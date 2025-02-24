/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** ScopeLock
*/


#ifndef SCOPELOCK_HPP_
    #define SCOPELOCK_HPP_

    #include "Mutex.hpp"

namespace thread {
    class ScopeLock {
        public:
            ScopeLock(Mutex &mutex);
            ~ScopeLock();

            void lock();
            void unlock();
            void trylock();

        private:
            Mutex &_mutex;
    };
}

#endif /* !SCOPELOCK_HPP_ */
