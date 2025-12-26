#include "observer.hpp"
#include <thread>
#include <atomic>
#include <cassert>
#include <cstdint>

int main() {
    observer::Dispatcher d;
    const std::int64_t iterations = 100000;
    std::atomic<std::int64_t> counter{0};

    // Subscribe: increments counter by the value passed
    auto sub = d.subscribe("msg", [&](void* data){
        counter.fetch_add(*static_cast<std::int64_t*>(data), std::memory_order_relaxed);
    });

    // Producer thread publishes sequential integers
    std::thread producer([&]{
        for (std::int64_t i = 0; i < iterations; ++i) {
            d.publish("msg", (void*)&i);
        }
    });

    producer.join();
    d.unsubscribe(sub);

    // Expected sum of 0..iterations-1 (use 64‑bit arithmetic)
    std::int64_t expected = (iterations - 1) * iterations / 2;
    assert(counter.load(std::memory_order_relaxed) == expected && "Thread‑safety failure");
    return 0;
}
