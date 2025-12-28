#include "observer.hpp"
#include <cassert>
#include <iostream>

int main() {
    observer::Dispatcher d;

    // 1. Unsubscribe with an invalid ID (should be a no‑op and not crash)
    d.unsubscribe(9999);

    // 2. Publish to a topic that has no subscribers (should do nothing, no crash)
    d.publish("nonexistent_topic", nullptr);

    // 3. Subscribe and publish using an empty topic string
    bool empty_topic_called = false;
    auto empty_id = d.subscribe("", [&](const void*){ empty_topic_called = true; });
    d.publish("", nullptr);
    assert(empty_topic_called && "Callback for empty topic was not invoked");
    d.unsubscribe(empty_id);

    std::cout << "Edge‑case tests passed" << std::endl;
    return 0;
}
