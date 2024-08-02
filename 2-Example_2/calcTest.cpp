#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "calc.hpp"

/*==================================Normal test==================================*/

TEST(Parent_Test, Test_1)
{
    Student s1(100, "Ibrahim");
    EXPECT_TRUE(s1.DisplayScore());
}
TEST(Parent_Test, Test_2)
{
    Student s1(20, "Ibrahim");
    EXPECT_FALSE(s1.DisplayScore());
}

/*===================================TEST_F===========================================*/

/*We had to create the class twice , once in each function,, The alternative is to make a class
global and shared between testcases BUTT this is not best sloution so the solution is to use TEST_F*/

class StudentTest : public testing::Test
{
public:
    Student s1; //Should be public because TEST_F will run the Constructor SetUp as the first thing
    
    /*Sets up the test fixture. This Function is Considered as a Constructor
    This is vitrual func so must be overriden because we inherit*/
    void SetUp() override
    {
        s1.score = 100;
        s1.name = "Ibrahim";
    }

    /*Tears down the test fixture. This Function is Considered as a Destructor
    This is vitrual func so must be overriden because we inherit*/
    void TearDown() override
    {
    }
};

/*First parametet in TEST_F must be inhertied from testing::Test , We pass the Class We created (StudentTest)
which contain an object of class (Student) which we want to make tests on*/

/*TEST_F Conisdered as a common factor between Test cases telling to execute
the Constructor in the class Passed (StudentTest) and the constructor here is the SetUp Function*/
TEST_F(StudentTest, Test_1)
{
    EXPECT_TRUE(s1.DisplayScore());
}

TEST_F(StudentTest, Test_2)
{
    s1.score = 20;
    EXPECT_FALSE(s1.DisplayScore());
}

/*==================================Main Function=========================================*/

int main(int argc, char const *argv[])
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
