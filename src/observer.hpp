/**
 * @licence MIT
 *
 * @brief C++ API header for the Observer library.
 *
 * @file: observer.hpp
 */

#pragma once

#include <functional>
#include <unordered_map>
#include <vector>
#include <string>
#include <mutex>
#include <atomic>

namespace observer {

/**
 * @brief Dispatcher implements the Observer pattern.
 *
 * It allows subscription of callbacks to string-identified topics and publishing
 * data to those topics.
 */

using callback_t = std::function<void(void*)>;
using subscription_id_t = std::size_t;

class Dispatcher {
public:
    Dispatcher();
    ~Dispatcher();

    /**
     * @brief Subscribe a callback to a topic.
     * @param topic The name of the topic to subscribe to.
     * @return A unique subscription identifier.
     */
    subscription_id_t subscribe(const std::string& topic, callback_t cb);

    /**
     * @brief Unsubscribe using the subscription id returned by subscribe.
     * @param id Identifier of the subscription to remove.
     */
    void unsubscribe(subscription_id_t id);

    /**
     * @brief Publish data to a topic.
     * @param topic The name of the topic to publish.
     * @param data Pointer to data passed to callbacks.
     */
    void publish(const std::string& topic, void* data) const;

private:
    struct Subscription {
        subscription_id_t id;
        callback_t cb;
    };

    /**
     * @brief Map topic to list of subscriptions.
     */
    std::unordered_map<std::string, std::vector<Subscription>> topics_;
    /**
     * @brief Map subscription id to topic for fast unsubscribe.
     */
    std::unordered_map<subscription_id_t, std::string> id_to_topic_;

    mutable std::mutex mutex_;
    std::atomic<subscription_id_t> next_id_{1}; /**< start at 1, 0 reserved */
};

} /* End of observer namespace */
