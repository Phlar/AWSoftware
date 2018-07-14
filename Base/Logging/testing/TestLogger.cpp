
#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING

#include <gtest/gtest.h>

#include "base.logging.internal/Logger.hpp"

using namespace testing;
using namespace aw::base;

class TestLoggerFixture : public Test {

    public:
        TestLoggerFixture() {
		}

		virtual ~TestLoggerFixture() {
        }
};

TEST_F(TestLoggerFixture, TestFoo) {
  
    std::cout << "[TestLoggerFixture] Foo" << std::endl;
}

int main(int argc, char **argv) {
     testing::InitGoogleTest(&argc, argv);
     return RUN_ALL_TESTS();
}