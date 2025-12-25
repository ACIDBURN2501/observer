/**
 * @licence MIT
 *
 * @brief C API header for the Observer library.
 *
 * @file: observer_c.cpp
 */

#include "observer_c.h"
#include "observer.hpp"
#include <new>

extern "C" {

struct dispatcher_t {
    observer::Dispatcher* impl;
};

dispatcher_t* dispatcher_create(void) {
    dispatcher_t* d = (dispatcher_t*)std::malloc(sizeof(dispatcher_t));
    if (!d) return nullptr;
    try {
        d->impl = new observer::Dispatcher();
    } catch (...) {
        std::free(d);
        return nullptr;
    }
    return d;
}

void dispatcher_destroy(dispatcher_t* d) {
    if (!d) return;
    delete d->impl;
    std::free(d);
}

subscription_id_t dispatcher_subscribe(dispatcher_t* d, const char* topic, void (*cb)(void*)) {
    if (!d || !topic || !cb) return 0;
    observer::callback_t f = [cb](void* data) { cb(data); };
    return d->impl->subscribe(std::string(topic), std::move(f));
}

void dispatcher_unsubscribe(dispatcher_t* d, subscription_id_t id) {
    if (!d) return;
    d->impl->unsubscribe(id);
}

void dispatcher_publish(dispatcher_t* d, const char* topic, void* data) {
    if (!d || !topic) return;
    d->impl->publish(std::string(topic), data);
}

} /* extern "C" */
