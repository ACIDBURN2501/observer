#include "observer.hpp"
#include <cassert>
#include <iostream>

int main() {
    observer::Dispatcher d;
    bool called = false;
    auto id = d.subscribe("test_topic", [&](void* data){
        const char* msg = static_cast<const char*>(data);
        if (std::string(msg) == "ping") {
            called = true;
        }
    });
    const char* payload = "ping";
    d.publish("test_topic", (void*)payload);
    d.unsubscribe(id);
    assert(called && "Callback was not called with correct payload");
    std::cout << "Test passed" << std::endl;
    return 0;
}
