
#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING

#include <gtest/gtest.h>

// #include "base.module\ModuleProvider.hpp"
#include "base.module.gmock\MockIModule.hpp"

using namespace testing;
using namespace aw::base;


class TestModuleProviderFixture : public Test {

    public:
        TestModuleProviderFixture()
        //: moduleProvider(nullptr) {
        {}

        virtual ~TestModuleProviderFixture() {
        }

        void SetUp() override {
         //   ASSERT_NO_THROW(moduleProvider = std::make_shared<ModuleProvider>());
        }

   //     std::shared_ptr<ModuleProvider> moduleProvider;
};

TEST(TestModuleProvider, TestAddAndGetValidModule) {

//     EXPECT_NO_THROW()

    
}


int main(int argc, char **argv) {
     testing::InitGoogleTest(&argc, argv);
     return RUN_ALL_TESTS();
}