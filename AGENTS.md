# AGENTS.md

## Project Overview
The **Observer** library provides a lightweight, modern C++ implementation of the classic **Observer / Publisher‑Subscriber** design pattern. It enables decoupled communication between components by allowing code to subscribe callbacks to named *topics* and publish data to those topics.

## Features
- **C++ API** – Header‑only `observer.hpp` with a `observer::Dispatcher` class.
- **Thread‑safe** – Internally protects subscription containers with a `std::mutex`.
- **Subscription IDs** – Unique identifiers returned on subscription for easy unsubscription.
- **C API** – `observer_c.h` / `observer_c.cpp` expose the same functionality to C programs, useful for mixed‑language projects or embedded environments.

## Intended Learning Outcomes
- Master modern C++ features: `std::function`, lambdas, `std::unordered_map`, and RAII.
- Understand and implement the Observer design pattern.
- Work with thread‑safety primitives.
- Create a clean C API wrapper around C++ code.
- Use CMake for building multi‑language projects.

## Usage
See the **README.md** for detailed usage examples in both C++ and C.

## License
MIT – see `LICENSE`.
