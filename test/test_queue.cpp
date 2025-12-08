#include <gtest/gtest.h>
#include <queue.hpp>

TEST(QueueTest, PushBack)
{
    Queue<int> q;
    q.push_back(1);
    ASSERT_EQ(q.size(), 1);
}

TEST(QueueTest, PushFront)
{
    Queue<int> q;
    q.push_front(1);
    ASSERT_EQ(q.size(), 1);
}

TEST(QueueTest, PushBackPop)
{
    Queue<int> q;
    int n = 1;
    q.push_back(n);
    ASSERT_EQ(q.pop_back(), n);
    ASSERT_EQ(q.size(), 0);
}

TEST(QueueTest, PushFrontPop)
{
    Queue<int> q;
    int n = 1;
    q.push_front(n);
    ASSERT_EQ(q.pop_front(), n);
    ASSERT_EQ(q.size(), 0);
}