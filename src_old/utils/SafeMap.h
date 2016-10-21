#ifndef SNAKE_SERVER_THREADSAFE_LOOKUP_TABLE_H
#define SNAKE_SERVER_THREADSAFE_LOOKUP_TABLE_H

#include <mutex>
#include <functional>
#include <list>
#include <shared_mutex>
#include <vector>
#include <algorithm>

namespace SnakeServer {

    namespace Utils {

        template<typename Key, typename Value, typename Hash = std::hash<Key>>
        class SafeMap {
        private:
            class bucket_type {
            private:
                typedef std::pair<Key, Value> bucket_value;
                typedef std::list<bucket_value> bucket_data;
                typedef typename bucket_data::const_iterator bucket_iterator;
                bucket_data m_data;
                mutable std::shared_timed_mutex m_mutex;

                bucket_iterator findEntryFor(Key const &t_key) const {
                    return std::find_if(m_data.begin(), m_data.end(), [&](bucket_value &item) {
                        return item.first == t_key;
                    });
                }

            public:
                Value valueFor(Key const &t_key, Value const &t_defaultValue) const {
                    std::shared_lock<std::shared_timed_mutex> lock(m_mutex);
                    bucket_iterator const found_entry = findEntryFor(t_key);
                    return (found_entry == m_data.end()) ?
                           t_defaultValue : found_entry->second;
                }

                void addOrUpdateMapping(Key const &t_key, Value const &t_value) {
                    std::unique_lock<std::shared_timed_mutex> lock(m_mutex);
                    bucket_iterator const found_entry = findEntryFor(t_key);
                    if (found_entry == m_data.end()) {
                        m_data.push_back(bucket_value(t_key, t_value));
                    } else {
                        found_entry->second = t_value;
                    }
                }

                void removeMapping(Key const &t_key) {
                    std::unique_lock<std::shared_timed_mutex> lock(m_mutex);
                    bucket_iterator const found_entry = findEntryFor(t_key);
                    if (found_entry != m_data.end()) {
                        m_data.erase(found_entry);
                    }
                }
            };

            std::vector<std::unique_ptr<bucket_type>> m_buckets;
            Hash m_hasher;

            bucket_type &getBucket(Key const &t_key) const {
                std::size_t const bucket_index = m_hasher(t_key) % m_buckets.size();
                return *m_buckets[bucket_index];
            }

        public:
            typedef Key key_type;
            typedef Value mapped_type;
            typedef Hash hash_type;

            SafeMap(unsigned t_numBuckets = 19, Hash const &t_hasher = Hash());

            SafeMap(SafeMap const &t_other) = delete;

            SafeMap &operator=(SafeMap const &t_other) = delete;

            Value valueFor(Key const &t_key, Value const &t_defaultValue = Value()) const;

            void addOrUpdateMapping(Key const &t_key, Value const &t_value);

            void removeMapping(Key const &t_key);
        }; // end class

    } // end namespace Utils

} // end namespace SnakeServer

#endif //SNAKE_SERVER_THREADSAFE_LOOKUP_TABLE_H
