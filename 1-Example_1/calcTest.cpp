#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>
#include "calc.hpp"

/*====================================EXPECT_EQ/EXPECT_NE=================================*/
TEST(SumFunction, Test_1)
{
    // Arrange
    /*Our function is small so we do call direct*/

    // Call
    EXPECT_EQ(5, sub(2, 3));

    // Action
}
TEST(SubFunction, Test_2)
{
    EXPECT_NE(5, sum(7, 5));
}

/*==================================EXPECT/ASSERT_TRUE=========================================*/
bool func()
{
    return false;
}

TEST(FuncTest, Test1)
{
    ASSERT_TRUE(func()); // If failed will not continue the test cases below inside the test case
    std::cout << "This is another Test case" << std::endl;
    EXPECT_TRUE(func());
}

/*======================================EXPECT_THROW========================================*/
void func2()
{
    // int a = 5 , b = 0 , c = a/b;
    // if (b ==0)
    // {
    //     throw std::runtime_error("This is Runtime error\n");
    // }
    throw std::runtime_error("This is Runtime error\n");
}

TEST(ThrowTest, Test_1)
{
    EXPECT_THROW(func2(), std::runtime_error); // To check if the function deliver the throw
}

void func3()
{

    throw std::logic_error("This is Runtime error\n");
}

TEST(ThrowTest2, Test_1)
{
    /*Test fails because it expecting Runtime error but the throw is Logical error*/
    EXPECT_THROW(func3(), std::runtime_error);
}
/*==================================EXPECT_STREQ=========================================*/
char* func4()
{
    return "Hello";
}

TEST(StringTest , Test_1)
{
    EXPECT_STREQ (func4() , "Hello");
}

TEST(StringTest , Test_2)
{
    std::string s = "Hello";
    /*Can't Use The String itself direct because it's a class and the comparison 
    should be between constant char-s so we us function of c_str*/
    EXPECT_STREQ (func4() , s.c_str()); //Should compare Const char with const char
}



/*==================================Main Function=========================================*/

int main(int argc, char const *argv[])
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
