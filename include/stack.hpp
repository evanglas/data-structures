#pragma once

#include <cstddef>

template <typename T>
class Stack
{
public:
    void add(T v);
    T pop();

private:
    size_t size_;
};