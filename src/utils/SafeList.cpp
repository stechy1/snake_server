#include "SafeList.h"

namespace SnakeServer {

    namespace Utils {

        template<typename T>
        void SafeList<T>::push_front(T const &t_value) {
            std::unique_ptr<node> new_node(new node(t_value));
            std::lock_guard<std::mutex> lk(m_head.m);
            new_node->next = std::move(m_head.next);
            m_head.next = std::move(new_node);
        }

        template<typename T, typename Function>
        void SafeList<T>::for_each(Function f) {
            node *current = &m_head;
            std::unique_lock<std::mutex> lk(m_head.m);
            while (node *const next = current->next.get()) {
                std::unique_lock<std::mutex> next_lk(next->m);
                lk.unlock();
                f(*next->data);
                current = next;
                lk = std::move(next_lk);
            }
        }

        template<typename T, typename Predicate>
        std::shared_ptr<T> SafeList<T>::find_first_if(Predicate p) {
            node *current = &m_head;
            std::unique_lock<std::mutex> lk(m_head.m);
            while (node *const next = current->next.get()) {
                std::unique_lock<std::mutex> next_lk(next->m);
                lk.unlock();
                if (p(*next->data)) {
                    return next->data;
                }
                current = next;
                lk = std::move(next_lk);
            }
            return std::shared_ptr<T>();
        }

        template<typename T, typename Predicate>
        void SafeList<T>::remove_if(Predicate p) {
            node *current = &m_head;
            std::unique_lock<std::mutex> lk(m_head.m);
            while (node *const next = current->next.get()) {
                std::unique_lock<std::mutex> next_lk(next->m);
                if (p(*next->data)) {
                    std::unique_ptr<node> old_next = std::move(current->next);
                    current->next = std::move(next->next);
                    next_lk.unlock();
                } else {
                    lk.unlock();
                    current = next;
                    lk = std::move(next_lk);
                }
            }
        }
    } // end namespace Utils

} // end namespace SnakeServer