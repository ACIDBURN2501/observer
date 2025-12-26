/**
 * @licence MIT
 *
 * @brief C++ implementation for the Observer library.
 *
 * @file: observer.cpp
 */

#include "observer.hpp"
#include <algorithm>

namespace observer {

// Defaulted constructors/destructor are defined inline in the header.
// No need to define them here.

subscription_id_t Dispatcher::subscribe(const std::string& topic, callback_t cb) noexcept {
    std::lock_guard<std::mutex> lock(mutex_);
    subscription_id_t id = next_id_++;
    Subscription sub{id, std::move(cb)};
    topics_[topic].push_back(std::move(sub));
    id_to_topic_[id] = topic;
    return id;
}

void Dispatcher::unsubscribe(subscription_id_t id) noexcept {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = id_to_topic_.find(id);
    if (it == id_to_topic_.end()) return;
    const std::string& topic = it->second;
    auto& vec = topics_[topic];
    vec.erase(std::remove_if(vec.begin(), vec.end(), [id](const Subscription& s){ return s.id == id; }), vec.end());
    if (vec.empty()) topics_.erase(topic);
    id_to_topic_.erase(it);
}

void Dispatcher::publish(const std::string& topic, void* data) const noexcept {
    std::vector<callback_t> callbacks;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = topics_.find(topic);
        if (it == topics_.end()) return;
        for (const auto& sub : it->second) {
            callbacks.push_back(sub.cb);
        }
    }
    for (auto& cb : callbacks) {
        cb(data);
    }
}


} /* namespace observer */
