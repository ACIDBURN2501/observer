# Observer Library

A lightweight, header‑only (with optional C API) library implementing the **Observer / Publisher‑Subscriber** pattern in modern C++.

## Features
- Subscribe callbacks (`std::function<void(void*)>`) to string‑identified topics.
- Publish an event; all callbacks for that topic are invoked.
- Automatic subscription identifiers for easy unsubscription.
- Thread‑safe via internal `std::mutex`.
- Optional C API (`dispatcher_create`, `dispatcher_subscribe`, …) for interoperability with C projects.

## Build & Run (CMake)
```bash
mkdir -p build && cd build
cmake ..
cmake --build .
# Run the example program (if you add your own example)
# ./example
```

## Run Unit Tests
```bash
./tests   # prints "Test passed"
./multi_topic_test   # runs additional tests
```

## Usage (C++)
```cpp
#include "observer.hpp"
#include <iostream>

int main() {
    observer::Dispatcher d;
    auto id = d.subscribe("my_topic", [](void* data){
        std::cout << "C++ received: " << static_cast<char*>(data) << "\n";
    });
    const char* msg = "Hello World";
    d.publish("my_topic", (void*)msg);
    d.unsubscribe(id);
}
```

## Usage (C)
```c
#include "observer_c.h"
#include <stdio.h>

void c_cb(void* data) {
    printf("C received: %s\n", (char*)data);
}

int main() {
    dispatcher_t* d = dispatcher_create();
    subscription_id_t sid = dispatcher_subscribe(d, "topic", c_cb);
    char* txt = "Hi C";
    dispatcher_publish(d, "topic", txt);
    dispatcher_unsubscribe(d, sid);
    dispatcher_destroy(d);
    return 0;
}
```

## License
MIT – see `LICENSE` file.
