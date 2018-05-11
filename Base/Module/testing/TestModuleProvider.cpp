
#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING

#include <gtest/gtest.h>

#include <boost/regex.hpp>


TEST(MyTest, FooTest) {

    int i(42);

    EXPECT_EQ(i, 42);
}

TEST(MyTest, BarTest) {

    int i(42);

    EXPECT_NE(i, 42);

    std::string s = "Boost Libraries";
    boost::regex expr{ "\\w+\\s\\w+" };
    std::cout << "LALALA: " << std::boolalpha << boost::regex_match(s, expr) << '\n';
}

int main(int argc, char **argv) {
     testing::InitGoogleTest(&argc, argv);
     return RUN_ALL_TESTS();
}