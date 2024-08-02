# Google-Test
Google Test (GTest) is a C++ testing framework by Google that simplifies writing and running tests with robust assertions and features.
- [Google-Test](#google-test)
  - [Installation](#installation)
  - [Run Tests](#run-tests)
    - [EXPECT\_EQ / EXPECT\_NE](#expect_eq--expect_ne)
    - [EXPECT\_TRUE / ASSERT\_TRUE](#expect_true--assert_true)
    - [EXPECT\_THROW](#expect_throw)
    - [EXPECT\_STREQ](#expect_streq)
  - [TEST\_F](#test_f)
  - [Running Commands](#running-commands)
## Installation
```sh
git clone https://github.com/google/googletest.git -b release-1.12.0
cd googletest
mkdir build
cd build
cmake ..
make
sudo make install
```
- Make sure the libraries inside **``build/lib/``** is copied or installed inside your **``/usr/lib/``**
- you will find four libraries **``libgtest.a libgtest_main.a libgmock.a libgmock_main.a``**

## Run Tests
### EXPECT_EQ / EXPECT_NE
```cpp
TEST(SumFunction, Test_1)
{
    EXPECT_EQ(5, sub(2, 3));
}
```
 - In the macro **``TEST(SumFunction, Test_1)``**, both **CalcTest** and **Addition** are identifiers used by Google Test to organize and name the test cases.
 - **``EXPECT_EQ``**: Compare between the two parameters and the test case will pass if they are equal.
```cpp
TEST(SubFunction, Test_2)
{
    EXPECT_NE(5, sum(7, 5));
}
```
- **``EXPECT_NE``**: Compare between the two parameters and the test case will pass if they are not equal.

### EXPECT_TRUE / ASSERT_TRUE
```cpp
bool func()
{
    return false;
}
TEST(FuncTest, Test1)
{
    ASSERT_TRUE(func());
    std::cout << "This is another Test case" << std::endl;
    EXPECT_TRUE(func());
}
```
 - **``ASEERT_TRUE``**: If test case failed, will not continue the test cases below inside the test case.
 - **``EXPECT_TRUE``**: The test case will pass if the parameter inside is True.

### EXPECT_THROW
```cpp
void func2()
{
    throw std::runtime_error("This is Runtime error\n");
}

TEST(ThrowTest, Test_1)
{
    EXPECT_THROW(func2(), std::runtime_error);
}
```
- **``EXPECT_THROW``**: To check if the function deliver the throw
```cpp
void func3()
{

    throw std::logic_error("This is Runtime error\n");
}

TEST(ThrowTest2, Test_1)
{
    EXPECT_THROW(func3(), std::runtime_error);
}
```
 - In this case Test fails because it expecting **Runtime error** but the throw is **Logical error**

### EXPECT_STREQ
```cpp
char* func4()
{
    return "Hello";
}

TEST(StringTest , Test_1)
{
    EXPECT_STREQ (func4() , "Hello");
}
```
 - Test case will pass because the **(array of char)** **``"Hello"``** is equal to the return of **``func4()``**

```cpp
TEST(StringTest , Test_2)
{
    std::string s = "Hello";
    EXPECT_STREQ (func4() , s.c_str()); //Should compare Const char with const char
}
```
*Can't Use The String **``s``** itself direct because it's a class object and the comparison in **``EXPECT_STREQ``** should be between constant chars so we us function of **``c_str``***

## TEST_F
If we have a class object and want to do test on, So the normal way
```cpp
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
```
>*but the **problem** here is that we Created the class object twice once in each function **,SO** we should find another way.*
- The alternative way is to make the class global and shared between test-cases **,BUT** this is not best sloution so the solution is to use **TEST_F**

```cpp
class StudentTest : public testing::Test
{
public:
    Student s1; //Should be public because TEST_F will run the Constructor SetUp as the first thing

    void SetUp() override
    {
        s1.score = 100;
        s1.name = "Ibrahim";
    }

    void TearDown() override
    {
    }
};
```
- **``SetUp()``**: Sets up the test fixture. This Function is Considered as a Constructor, This is vitrual function so must be overriden because we inherit
- **``TearDown()``**: Tears down the test fixture. This Function is Considered as a Destructor, This is vitrual function so must be overriden because we inherit

**Why we Created a class **``StudentTest``** and it inherit from **``testing::Test``**??**
- First parametet in **``TEST_F()``** must be inhertied from **``testing::Test``** , We pass the Class We created **``StudentTest``** which contain **``s1``** an object of a class **``Student``** which we want to make tests on.

>**``TEST_F``** Conisdered as a common factor between Test cases telling to execute the Constructor in the class Passed **``StudentTest``** and the constructor here is the **``SetUp``** Function

```cpp
TEST_F(StudentTest, Test_1)
{
    EXPECT_TRUE(s1.DisplayScore());
}

TEST_F(StudentTest, Test_2)
{
    s1.score = 20;
    EXPECT_FALSE(s1.DisplayScore());
}
```
## Running Commands
---
```bash
g++ calc.cpp calcTest.cpp -lgtest -lgtest_main -pthread -o main
./main
```
- **``-lgtest``**: This flag tells the compiler to link against the Google Test library.

- **``-lgtest_main``**: This flag tells the compiler to link against the gtest_main library, which provides a main function for Google Test. This is useful if you don't want to write your own main function for running tests.

- **``-pthread``**: This flag links the pthread library, which is necessary for Google Test because it uses multi-threading internally.











