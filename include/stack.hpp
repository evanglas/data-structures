#pragma once

#include <cstddef>
#include <utility>
#include <stdexcept>

template <typename T>
class Stack
{
public:
    static constexpr size_t START_AMOUNT = 16;

    Stack() : size_(0), capacity_(START_AMOUNT), items_(new T[START_AMOUNT]) {}

    ~Stack()
    {
        delete[] items_;
    }

    Stack(const Stack &other) : size_(other.size_), capacity_(other.capacity_), items_(new T[other.capacity_])
    {
        for (size_t i = 0; i < other.size_; ++i)
        {
            items_[i] = other.items_[i];
        }
    }

    Stack(Stack &&other) noexcept : size_(other.size_), capacity_(other.capacity_), items_(other.items_)
    {
        other.size_ = 0;
        other.capacity_ = 0;
        other.items_ = nullptr;
    }

    Stack &operator=(const Stack &other)
    {
        if (this == &other)
            return *this;

        T *newItems = new T[other.capacity_];
        try
        {
            for (size_t i = 0; i < other.size_; ++i)
            {
                newItems[i] = other.items_[i];
            }
        }
        catch (...)
        {
            delete[] newItems;
            throw;
        }

        delete[] items_;
        items_ = newItems;
        size_ = other.size_;
        capacity_ = other.capacity_;
        return *this;
    }

    Stack &operator=(Stack &&other) noexcept
    {
        if (this == &other)
            return *this;

        delete[] items_;
        items_ = other.items_;
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.items_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;

        return *this;
    }

    // Uses perfect forwarding to avoid potential unnecessary copies into v.
    // Without this templating, the caller's v would always get copied into v.
    // Now, we simply used a generalized reference, U&&.
    template <typename U>
    void push(U &&v)
    {
        if (size_ == capacity_)
            grow();

        items_[size_++] = std::forward<U>(v);
    };

    T pop()
    {
        if (size_ == 0)
            throw std::out_of_range("Stack is empty!");

        return std::move(items_[--size_]);
    };

    size_t size() const
    {
        return size_;
    }

    bool empty() const
    {
        return size_ == 0;
    }

private:
    // TODO: can improve this by using uninitialized_copy/uninitialized_move
    // as well as ::operator new, ::operator delete.
    // Using new automatically calls the constructor of each element added.
    // Unintialized options do not do that.
    // https://chatgpt.com/c/69361347-b0d0-8325-afa0-4fb636e8ab35
    void grow()
    {
        size_t newCapacity = capacity_ * 2;
        T *moreItems = new T[capacity_];
        try
        {
            for (size_t i = 0; i < size_; i++)
            {
                moreItems[i] = std::move(items_[i]);
            }
        }
        catch (...)
        {
            delete[] moreItems;
            throw;
        }

        delete[] items_;
        items_ = moreItems;
    };
    size_t size_;
    size_t capacity_;
    T *items_;
};