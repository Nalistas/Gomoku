/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** Mutex
*/


#ifndef MUTEX_HPP_
    #define MUTEX_HPP_

    #include <pthread.h>

namespace thread {
    class Mutex {
        public:
            Mutex();
            ~Mutex();

            void lock();
            void unlock();
            void trylock();
            bool isLocked();

        private:
            pthread_mutex_t _mutex;
            bool _state;
    };
}

#endif /* !MUTEX_HPP_ */
