
#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING

#include <gtest/gtest.h>

#include "base.module\ModuleProvider.hpp"
#include "base.module.gmock\MockIModule.hpp"


using namespace testing;
using namespace aw::base;

class TestModuleProviderFixture : public Test {

    public:
        TestModuleProviderFixture()
        : mockIModuleA(MockIModule::create())
        , mockIModuleB(MockIModule::create())
        , moduleProvider(nullptr) {
            EXPECT_CALL(*mockIModuleA, getUUID()).WillRepeatedly(Return(ModuleUUID(123)));
            EXPECT_CALL(*mockIModuleB, getUUID()).WillRepeatedly(Return(ModuleUUID(456)));
        }

        virtual ~TestModuleProviderFixture() {
        }

        void SetUp() override {
            ASSERT_NO_THROW(moduleProvider = ModuleProvider::getInstance());
        }

    MockIModulePtr mockIModuleA;
    MockIModulePtr mockIModuleB;

    ModuleProviderPtr moduleProvider;
};


TEST_F(TestModuleProviderFixture, TestModuleProviderLifetime) {

    ASSERT_TRUE(moduleProvider);

    // There should be only one owner - the fixture.
    std::weak_ptr<ModuleProvider> weakModuleProvider(moduleProvider);
    EXPECT_EQ(1, moduleProvider.use_count());
    EXPECT_EQ(moduleProvider, weakModuleProvider.lock());

    // Release the 'last' strong reference.
    EXPECT_NO_THROW(moduleProvider.reset());

    // ModuleProvider instance should not be reachable any more.
    EXPECT_TRUE(weakModuleProvider.expired());
}

TEST_F(TestModuleProviderFixture, TestAddAndGetValidModule) {

    bool isListed(false);
    IModulePtr listedModule(nullptr);

    // Getters before a module is added...
    EXPECT_NO_THROW(isListed = moduleProvider->hasModule(mockIModuleA->getUUID()));
    EXPECT_FALSE(isListed);

    EXPECT_NO_THROW(listedModule = moduleProvider->getModule(mockIModuleA->getUUID()));
    EXPECT_EQ(nullptr, listedModule);

    // ...add a module...
    EXPECT_NO_THROW(moduleProvider->addModule(mockIModuleA));

    // ...now it should be there.
    EXPECT_NO_THROW(isListed = moduleProvider->hasModule(mockIModuleA->getUUID()));
    EXPECT_TRUE(isListed);

    EXPECT_NO_THROW(listedModule = moduleProvider->getModule(mockIModuleA->getUUID()));
    EXPECT_EQ(mockIModuleA, listedModule);
}

TEST_F(TestModuleProviderFixture, TestAddInvalidModule) {

    EXPECT_ANY_THROW(moduleProvider->addModule(nullptr));
}

TEST_F(TestModuleProviderFixture, TestAddingModuleRaisesRefCount) {

    const auto refCountBefore(mockIModuleA.use_count());

    // Add it to the provider.
    EXPECT_NO_THROW(moduleProvider->addModule(mockIModuleA));

    const auto refCountAfter(mockIModuleA.use_count());
    EXPECT_TRUE(refCountAfter > refCountBefore);
}


int main(int argc, char **argv) {
     testing::InitGoogleTest(&argc, argv);
     return RUN_ALL_TESTS();
}