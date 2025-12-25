#include "observer.hpp"
#include <cassert>
#include <iostream>

int main() {
    observer::Dispatcher d;
    bool called_topic1 = false;
    bool called_topic2 = false;

    // Subscribe to topic1
    auto id1 = d.subscribe("topic1", [&](void* data){
        const char* msg = static_cast<const char*>(data);
        if (std::string(msg) == "msg1") called_topic1 = true;
    });

    // Subscribe to topic2
    auto id2 = d.subscribe("topic2", [&](void* data){
        const char* msg = static_cast<const char*>(data);
        if (std::string(msg) == "msg2") called_topic2 = true;
    });

    // Publish messages
    d.publish("topic1", (void*)"msg1");
    d.publish("topic2", (void*)"msg2");

    // Verify both callbacks were called
    assert(called_topic1 && "Callback for topic1 not invoked");
    assert(called_topic2 && "Callback for topic2 not invoked");

    // Test unsubscribe: remove topic1 subscription and ensure it no longer receives messages
    d.unsubscribe(id1);
    called_topic1 = false; // reset
    d.publish("topic1", (void*)"msg1");
    assert(!called_topic1 && "Callback for topic1 should not be invoked after unsubscribe");

    std::cout << "Multi-topic test passed" << std::endl;
    return 0;
}
