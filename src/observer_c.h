/**
 * @licence MIT
 *
 * @brief C API header for the Observer library.
 *
 * @file: observer_c.h
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct dispatcher_t dispatcher_t;

typedef unsigned long long subscription_id_t;

dispatcher_t* dispatcher_create(void);
void dispatcher_destroy(dispatcher_t* d);
subscription_id_t dispatcher_subscribe(dispatcher_t* d, const char* topic, void (*cb)(void*));
void dispatcher_unsubscribe(dispatcher_t* d, subscription_id_t id);
void dispatcher_publish(dispatcher_t* d, const char* topic, void* data);

#ifdef __cplusplus
}
#endif
