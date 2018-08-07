#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>
#include <thread>

#include "base.logging/Logging.hpp"
#include "base.module/IModule.hpp"
#include "base.logging.gmock/MockILogger.hpp"


using namespace testing;
using namespace aw::base;

TEST(TestLogging, TestLoggingMacrosWithoutInstantiatedModuleProvider) {

    EXPECT_NO_THROW(LOG_DEBUG("foo"));
}

TEST(TestLogging, TestLoggingMacrosWithoutRegisteredLogger) {

    auto moduleProvider(ModuleProvider::getInstance());
    EXPECT_NO_THROW(LOG_DEBUG("foo"));
}

TEST(TestLogging, TestLoggingMacrosInvalidLoggerInstalled) {

    class FakeModule : public IModule {

        public:

            FakeModule() {}
            virtual ~FakeModule() {}

            ModuleUUID getUUID() const override {
                return aw::base::logging::ILogger::TypeUUID;
            }
    };

    // Register a faulty logger...
    auto moduleProvider(ModuleProvider::getInstance());
    moduleProvider->addModule(std::make_shared<FakeModule>());

    EXPECT_NO_THROW(LOG_DEBUG("foo"));
}

TEST(TestLogging, TestLogMacros) {

    // Register a mock-logger.
    auto mockLogger(std::make_shared<aw::base::logging::MockILogger>());
    EXPECT_CALL(*mockLogger, getUUID()).WillRepeatedly(Return(aw::base::logging::ILogger::TypeUUID));

    auto moduleProvider(ModuleProvider::getInstance());
    moduleProvider->addModule(mockLogger);

    // Check all macros / levels.
    testing::InSequence seq;

    EXPECT_CALL(*mockLogger, log(testing::Eq(aw::base::logging::LogLevel::LOG_LEVEL_ERROR), testing::Eq("Foo 1")));
    EXPECT_NO_THROW(LOG_ERROR("Foo ", 1));

    EXPECT_CALL(*mockLogger, log(testing::Eq(aw::base::logging::LogLevel::LOG_LEVEL_INFO), testing::Eq("Bar 2")));
    EXPECT_NO_THROW(LOG_INFO("Bar ", 2));

    EXPECT_CALL(*mockLogger, log(testing::Eq(aw::base::logging::LogLevel::LOG_LEVEL_WARNING), testing::Eq("Hello 3")));
    EXPECT_NO_THROW(LOG_WARNING("Hello ", 3));

    EXPECT_CALL(*mockLogger, log(testing::Eq(aw::base::logging::LogLevel::LOG_LEVEL_DEBUG), testing::Eq("World 4")));
    EXPECT_NO_THROW(LOG_DEBUG("World ", 4));
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
