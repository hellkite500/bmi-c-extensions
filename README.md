![platform tests](https://github.com/hellkite500/bmi-c-extensions/actions/workflows/cmake-multi-platform.yml/badge.svg)

# BMI Extensions

A library for BMI extensions in C (and C++). Also includes an example 
extension, `BMI_Extra`.

The test suite contains a standard BMI model with the extension feature added, and the extension is tested using 5 different methods for creating, managing, and interacting with the extension.  These methods are currently documented in the test code and some comments in the library code.

> **TODO**
> Add disscussion of methods to readme

> **TODO**
> Add some usage examples to readme

> **TODO**
> Add design/architecture description to readme

# Building

```sh
cmake -B cmake_build -S .
cmake --build cmake_build
```

# Testing

> **Note**
> The unit tests use [Unity](https://github.com/ThrowTheSwitch/Unity)
> This is included as a git submodule, and the cmake build will attempt
> to automatically initialize the module for building the tests.

## Build and test

```sh
cmake --build cmake_build --target test
```

## Verbose testing

```sh
ctest --verbose --test-dir cmake_build
```