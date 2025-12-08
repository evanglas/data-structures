#pragma once

#include <utility>
#include <memory>
#include <stdexcept>

template <typename T>
class Queue;

template <typename T>
class Node
{
public:
    template <typename U>
    explicit Node(U &&val) : val_(std::move(val)), next_(nullptr), prev_(nullptr){};

private:
    T val_;

    std::unique_ptr<Node<T>> next_;
    Node<T> *prev_;

    friend class Queue<T>;
};

template <typename T>
class Queue
{
public:
    Queue() : front_(nullptr), back_(nullptr), size_(0) {};

    template <typename U>
    void push_back(U &&val)
    {
        auto newNode = std::make_unique<Node<T>>(std::forward<U>(val));
        if (!front_)
        {
            front_ = std::move(newNode);
            back_ = front_.get();
        }
        else
        {
            newNode->prev_ = back_;
            back_->next_ = std::move(newNode);
            back_ = back_->next_.get();
        }
        ++size_;
    };

    template <typename U>
    void push_front(U &&val)
    {
        auto newNode = std::make_unique<Node<T>>(std::forward<U>(val));
        if (!front_)
        {
            front_ = std::move(newNode);
            back_ = front_.get();
        }
        else
        {
            newNode->next_ = std::move(front_);
            newNode->next_->prev_ = newNode.get();
            front_ = std::move(newNode);
        }
        ++size_;
    };

    T pop_back()
    {
        if (!back_)
            throw std::out_of_range("Queue is empty.");

        auto val = std::move(back_->val_);

        if (back_->prev_)
        {
            auto *prev = back_->prev_;
            prev->next_.reset();
            back_ = prev;
        }
        else
        {
            front_.reset();
            back_ = nullptr;
        }
        --size_;
        return val;
    }

    T pop_front()
    {
        if (!front_)
            throw std::out_of_range("Queue is empty.");

        auto val = std::move(front_->val_);

        if (front_->next_)
        {
            front_->next_->prev_ = nullptr;
            front_ = std::move(front_->next_);
        }
        else
        {
            front_.reset();
            back_ = nullptr;
        }
        --size_;
        return val;
    }

    size_t size() const
    {
        return size_;
    }

private:
    std::unique_ptr<Node<T>> front_;
    Node<T> *back_;
    size_t size_;
};