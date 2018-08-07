#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING

#include <gtest/gtest.h>

#include <memory>

#include "base.common/Assert.hpp"

using namespace testing;
using namespace aw::base::common;
using namespace aw::base::common::utils;

TEST(TestAssertMacro, TestAssertViolation) {

    std::shared_ptr<int> myPtr{nullptr};

    try {

        ASSERT(myPtr, "Error while asserting int-pointer '", myPtr, "'.");
        ASSERT_TRUE(false, "Expected assertion to be violated");

    } catch (const std::runtime_error& e) {
        EXPECT_EQ("Error while asserting int-pointer '00000000'.", std::string(e.what()));
    } catch (const std::exception& e) {
        ASSERT_TRUE(false, "Expected std::runtime_error due to violated assertion (got std::exception derived type).");
    } catch (...) {
        ASSERT_TRUE(false, "Expected std::exception due to violated assertion (got unknown exception-'type'.");
    }
}

TEST(TestAssertMacro, TestAssertNoViolation) {

    std::shared_ptr<int> myPtr{ nullptr };

    try {
        ASSERT(!myPtr, "Error while asserting int-pointer '", myPtr, "'.");
    } catch (...) {
        ASSERT_TRUE(false, "Expected no violation of the assertion.");
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
