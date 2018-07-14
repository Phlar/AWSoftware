
#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING

#include <gtest/gtest.h>

using namespace testing;
//using namespace aw::base;

class TestFileLoggerStrategyFixture : public Test {

    public:
        TestFileLoggerStrategyFixture() {
		}

		virtual ~TestFileLoggerStrategyFixture() {
        }
};

TEST_F(TestFileLoggerStrategyFixture, TestFoo) {
  
    std::cout << "[TestFileLoggerStrategyFixture] Foo" << std::endl;
}

int main(int argc, char **argv) {
     testing::InitGoogleTest(&argc, argv);
     return RUN_ALL_TESTS();
}