#ifndef SNAKE_SERVER_SAFELIST_H
#define SNAKE_SERVER_SAFELIST_H

#include <mutex>
#include <memory>

namespace SnakeServer {

    namespace Utils {

        template<typename T>
        class SafeList {
        private:
            struct node {
                std::mutex m;
                std::shared_ptr<T> data;
                std::unique_ptr<node> next;

                node() : next() {}

                node(T const &value) : data(std::make_shared<T>(value)) {}
            };

            node m_head;
        public:
            SafeList() {}

            ~SafeList() {
                remove_if([](node const &) {
                    return true;
                });
            }

            SafeList(SafeList const &t_other) = delete;

            SafeList &operator=(SafeList const &t_other) = delete;

            void push_front(T const &t_value);

            template<typename Function>
            void for_each(Function f);

            template<typename Predicate>
            std::shared_ptr<T> find_first_if(Predicate p);

            template<typename Predicate>
            void remove_if(Predicate p);

        }; // end class

    } // end namespace Utils

} // end namespace SnakeServer

#endif //SNAKE_SERVER_SAFELIST_H
