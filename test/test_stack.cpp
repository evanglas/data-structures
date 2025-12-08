#include <gtest/gtest.h>
#include <stack.hpp>
#include <string>

TEST(Sample, Temp)
{
    ASSERT_TRUE(true);
}

TEST(StacktTests, AddInts)
{
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    ASSERT_EQ(3, s.size());
}

TEST(StackTests, AddStrings)
{
    Stack<std::string> s;
    s.push("hi");
    ASSERT_EQ(1, s.size());
}

TEST(StackTests, PopOnEmptyStackThrows)
{
    Stack<std::string> s;
    ASSERT_THROW(s.pop(), std::out_of_range);
}

TEST(StackTests, GrowOnce)
{
    Stack<int> s;
    for (size_t i = 0; i < s.START_AMOUNT; ++i)
    {
        s.push(i);
    }
    ASSERT_EQ(s.START_AMOUNT, s.size());
    ASSERT_EQ(s.START_AMOUNT, s.capacity());
    s.push(1);
    ASSERT_EQ(s.START_AMOUNT * 2, s.capacity());
    ASSERT_EQ(s.START_AMOUNT + 1, s.size());
}

TEST(StackTests, PushPopEquality)
{
    Stack<int> s;
    int push1 = 1;
    int push2 = 2;
    s.push(push1);
    s.push(push2);
    ASSERT_EQ(push2, s.pop());
    ASSERT_EQ(push1, s.pop());
}