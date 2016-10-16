#ifndef SNAKE_SERVER_THREADSAFE_QUEUE_H
#define SNAKE_SERVER_THREADSAFE_QUEUE_H

#include <mutex>
#include <memory>
#include <condition_variable>

namespace SnakeServer {

    namespace Utils {

        template<typename T>
        class SafeQueue {
        private:
            struct node {
                std::shared_ptr<T> data;
                std::unique_ptr<node> next;
            };
            std::mutex m_headMutex;
            std::unique_ptr<node> m_head;
            std::mutex m_tailMutex;
            node *m_tail;
            std::condition_variable m_dataCond;

            std::unique_ptr<node> tryPopHead();

            std::unique_ptr<node> tryPopHead(T &t_value);

            node *getTail();

            std::unique_ptr<node> popHead();

            std::unique_lock<std::mutex> waitForData();

            std::unique_ptr<node> waitPopHead();

            std::unique_ptr<node> waitPopHead(T &t_value);

        public:
            SafeQueue()
                    : m_head(new node), m_tail(m_head.get()) {}

            SafeQueue(const SafeQueue &t_other) = delete;

            SafeQueue &operator=(const SafeQueue &t_other)= delete;

            std::shared_ptr<T> tryPop();

            bool tryPop(T &t_value);

            bool empty();

            void push(T t_newValue);

            std::shared_ptr<T> waitAndPop();

            void waitAndPop(T &t_value);
        }; // end class

    } // end namespace Utils

} // end namespace SnakeServer

#endif //SNAKE_SERVER_THREADSAFE_QUEUE_H
