# HOW TO START USING GTEST

## Executing tests
First, compile the project by executing `cmake -B build` at the root of the
project.
Then run `ctest` in the `build/` directory or execute the `./unit_tests` binary
that is created during compilation

## Adding a tests

Assuming you are on vscode and have the `C/C++` extension

1. Go to the tests/ directory and create `[FILENAME].cpp`.
Then edit this part of the `CMakeLists.txt` file
```cmake
# add your test files here
set(SOURCES
    [...]
    [FILENAME].cpp
)
```
to add your file to the list test files

2. Add the line `#include <gtest/gtest.h>` at the top of the file.

> If it is underlined in red, make your mouse hover on it and click on
`Quick fix...` then on `Edit "includePath" settings`.
On the page that just opened, add the line `**/include` on a new line in the
`Include path`

3. Create a test by writting ([more at](https://google.github.io/googletest/reference/testing.html))

```c++
TEST(SuiteName, TestName)
{
    // your code here
}
```

4. Use one of the the assertion [here](https://google.github.io/googletest/reference/assertions.html) to check values. Below are the most useful ones:
- EXPECT_THAT
- EXPECT_TRUE
- EXPECT_FALSE
- EXPECT_EQ
- EXPECT_NE
- EXPECT_STREQ
- EXPECT_FLOAT_EQ

#### Exemple:

```c++
#include <gtest/gtest.h>

TEST(HelloTest, BasicAssertions)
{
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}
```