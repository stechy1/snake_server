#include "SafeMap.h"

namespace SnakeServer {

    namespace Utils {
        template<typename Key, typename Value, typename Hash = std::hash<Key>>
        SafeMap::SafeMap(unsigned t_numBuckets = 19, Hash const &t_hasher = Hash())
                : m_buckets(t_numBuckets), m_hasher(t_hasher) {
            for (unsigned i = 0; i < t_numBuckets; ++i) {
                m_buckets[i].reset(new bucket_type);
            }
        }

        template<typename Key, typename Value, typename Hash = std::hash<Key>>
        Value SafeMap::valueFor(Key const &t_key, Value const &t_defaultValue = Value()) const {
            return getBucket(t_key).valueFor(t_key, t_defaultValue);
        }

        template<typename Key, typename Value, typename Hash = std::hash<Key>>
        void SafeMap::addOrUpdateMapping(Key const &t_key, Value const &t_value) {
            getBucket(t_key).addOrUpdateMapping(t_key, t_value);
        }

        template<typename Key, typename Value, typename Hash = std::hash<Key>>
        void SafeMap::removeMapping(Key const &t_key) {
            getBucket(t_key).removeMapping(t_key);
        }
    } // end namespace Utils

} // end namespace SnakeServer