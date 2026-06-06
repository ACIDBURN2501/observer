# Contributing to observer

observer is a small C++ observer / publisher-subscriber library with optional C API bindings. It is intentionally CMake-based and provides topic-based callbacks, subscription identifiers, and thread-safe dispatch.

## Getting started

The same basic commands CI or local validation should run:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
ctest --test-dir build --output-on-failure
```

To install into a staging prefix for consumer testing:

```sh
cmake --install build --prefix /tmp/observer-install
```

## Source style

- `.clang-format` is mandatory. Run `clang-format -i` on every modified `.hpp` / `.h` / `.cpp` file before submitting.
- Match the existing style; do not reformat unrelated code.
- CMake is the build system for this project. Update `CMakeLists.txt`, install rules, and tests when adding or removing public API files.

## C++ / C API rules

- C++17 and C11 are the current language baselines.
- Preserve thread-safety for dispatcher subscription, unsubscription, and publish operations.
- Keep C API ownership explicit: objects created by `dispatcher_create` must be released with `dispatcher_destroy`.
- Validate pointer arguments at public C API boundaries.

## Tests

- Add a test for every bug fix.
- Add a test for every new feature.
- Tests are run via CTest.
- Keep tests deterministic and avoid timing-dependent behaviour.

## Commits

Use Conventional Commits:

- `feat: ...` new feature
- `fix: ...` bug fix
- `doc: ...` documentation only
- `test: ...` test-only changes
- `chore: ...` build, CI, release work
- `refactor: ...` code change that neither fixes a bug nor adds a feature

Keep the subject under ~70 characters. Use the body to explain _why_ the change is needed, not _what_ the diff already shows.

## Pull requests

- Open an issue first for non-trivial changes so the design can be agreed before implementation.
- Keep PRs focused. One feature or one fix per PR.
- All local build and CTest checks should pass before review.

## When in doubt

Open an issue and discuss before writing code. The library is small enough that even modest design changes have outsized implications.
