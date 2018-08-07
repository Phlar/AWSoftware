#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING

#include <gtest/gtest.h>

#include "base.common/StringUtils.hpp"

using namespace testing;
using namespace aw::base::common;
using namespace aw::base::common::utils;

class CustomType final {

    public:
        CustomType() = delete;
        CustomType(const std::string& value)
        : m_value(value) {
        }

        friend std::ostream& operator<< (std::ostream& stream, const CustomType& rhs);

    private:
        std::string m_value;
};

inline std::ostream& operator<< (std::ostream& stream, const CustomType& rhs) {
    stream << rhs.m_value;
    return stream;
}


TEST(TestStringUtils, TestStringConcatenationOneBuiltInType) {

    const std::string expectedResult("123");
    std::string actualResult;

    EXPECT_NO_THROW(actualResult = concatenateToString(123));
    EXPECT_EQ(expectedResult, actualResult);
}

TEST(TestStringUtils, TestStringConcatenationOneCustomType) {

    const std::string expectedResult("Hello world!");
    std::string actualResult;

    EXPECT_NO_THROW(actualResult = concatenateToString(CustomType(expectedResult)));
    EXPECT_EQ(expectedResult, actualResult);
}

TEST(TestStringUtils, TestStringConcatenationMultipleBuiltInTypes) {

    const std::string expectedResult("Hello42");
    std::string actualResult;

    EXPECT_NO_THROW(actualResult = concatenateToString("Hello", 42));
    EXPECT_EQ(expectedResult, actualResult);
}

TEST(TestStringUtils, TestStringConcatenationMultipleDifferentTypes) {

    const std::string expectedResult("Hello123CustomType");
    std::string actualResult;

    EXPECT_NO_THROW(actualResult = concatenateToString("Hello", 123, CustomType("CustomType")));
    EXPECT_EQ(expectedResult, actualResult);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
