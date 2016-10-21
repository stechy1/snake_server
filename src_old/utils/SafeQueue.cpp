#include "SafeQueue.h"

namespace SnakeServer {

    namespace Utils {
        template<typename T>
        node *SafeQueue<T>::getTail() {
            std::lock_guard<std::mutex> tail_lock(m_tailMutex);
            return m_tail;
        }

        template<typename T>
        std::unique_ptr<node> SafeQueue<T>::popHead() {
            std::unique_ptr<node> old_head = std::move(m_head);
            m_head = std::move(old_head->next);
            return old_head;
        }

        template<typename T>
        std::unique_lock<std::mutex> SafeQueue<T>::waitForData() {
            std::unique_lock<std::mutex> head_lock(m_headMutex);
            m_dataCond.wait(head_lock, [&] { return m_head.get() != getTail(); });
            return std::move(head_lock);
        }

        template<typename T>
        std::unique_ptr<node> SafeQueue<T>::waitPopHead() {
            std::unique_lock<std::mutex> head_lock(waitForData());
            return popHead();
        }

        template<typename T>
        std::unique_ptr<node> SafeQueue<T>::waitPopHead(T &t_value) {
            std::unique_lock<std::mutex> head_lock(waitForData());
            t_value = std::move(*m_head->data);
            return popHead();
        }

        template<typename T>
        std::unique_ptr<node> SafeQueue<T>::tryPopHead() {
            std::lock_guard<std::mutex> head_lock(m_headMutex);
            if (m_head.get() == getTail()) {
                return std::unique_ptr<node>();
            }
            return popHead();
        }

        template<typename T>
        std::unique_ptr<node> SafeQueue<T>::tryPopHead(T &t_value) {
            std::lock_guard<std::mutex> head_lock(m_headMutex);
            if (m_head.get() == getTail()) {
                return std::unique_ptr<node>();
            }
            t_value = std::move(*m_head->data);
            return popHead();
        }

        template<typename T>
        std::shared_ptr<T> SafeQueue<T>::waitAndPop() {
            std::unique_ptr<node> const old_head = waitPopHead();
            return old_head->data;
        }

        template<typename T>
        void SafeQueue<T>::waitAndPop(T &t_value) {
            std::unique_ptr<node> const old_head = waitPopHead(t_value);
        }

        template<typename T>
        std::shared_ptr<T> SafeQueue<T>::tryPop() {
            std::unique_ptr<node> old_head = tryPopHead();
            return old_head ? old_head->data : std::shared_ptr<T>();
        }

        template<typename T>
        bool SafeQueue<T>::tryPop(T &t_value) {
            std::unique_ptr<node>
            const old_head = tryPopHead(t_value);
            return old_head != nullptr;
        }

        template<typename T>
        bool SafeQueue<T>::empty() {
            std::lock_guard<std::mutex> head_lock(m_headMutex);
            return (m_head.get() == getTail());
        }

        template<typename T>
        void SafeQueue<T>::push(T t_newValue) {
            std::shared_ptr<T> new_data(
                    std::make_shared<T>(std::move(t_newValue)));
            std::unique_ptr<node> p(new node);
            {
                std::lock_guard<std::mutex> tail_lock(m_tailMutex);
                m_tail->data = new_data;
                node *const new_tail = p.get();
                m_tail->next = std::move(p);
                m_tail = new_tail;
            }
            m_dataCond.notify_one();
        }

    } // end namespace Utils

} // end namespace SnakeServer