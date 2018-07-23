#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>
#include <thread>

#include "base.module/IModule.hpp"
#include "base.logging.internal/Logger.hpp"


using namespace testing;
using namespace aw::base;
using namespace aw::base::logging;


struct MockLoggedHandler {

    MOCK_METHOD1(onMessageLogged, void(const LoggedEntry&));
};


struct MockLoggerStrategy {

    MOCK_METHOD0(open, void());
    MOCK_METHOD0(close, void());
    MOCK_METHOD1(logEntry, LoggedEntry(const LogEntry&));
};
using MockLoggerStrategyUPtr = std::unique_ptr<MockLoggerStrategy>;


class TestLoggerFixture : public testing::Test {

    public:

        TestLoggerFixture()
        : mockLoggerStrategy(std::unique_ptr<MockLoggerStrategy>(new MockLoggerStrategy))
        , mockLoggerStrategyRaw(mockLoggerStrategy.get())
        , logger(nullptr) {
        }

        virtual ~TestLoggerFixture() {
        }

        void createLogger() {

            EXPECT_CALL(*mockLoggerStrategyRaw, open());
            EXPECT_CALL(*mockLoggerStrategyRaw, close());
            logger = std::unique_ptr<Logger<MockLoggerStrategy>>(new Logger<MockLoggerStrategy>(std::move(mockLoggerStrategy)));
        }

    protected:

        std::unique_ptr<MockLoggerStrategy> mockLoggerStrategy;

    public:

        MockLoggerStrategy * mockLoggerStrategyRaw;
        std::unique_ptr<Logger<MockLoggerStrategy>> logger;
};

TEST_F(TestLoggerFixture, TestConstructionWithInvalidStrategyShouldThrow) {
    ASSERT_ANY_THROW(std::unique_ptr<Logger<MockLoggerStrategy>>(new Logger<MockLoggerStrategy>(nullptr)););
}

TEST_F(TestLoggerFixture, TestGetUUID) {

    ModuleUUID loggerUUID;

    ASSERT_NO_THROW(createLogger());
    EXPECT_NO_THROW(loggerUUID = logger->getUUID());
    EXPECT_EQ(loggerUUID, ILogger::TypeUUID);
}

TEST_F(TestLoggerFixture, TestRegisteringInvalidHandlerShouldThrow) {

    ASSERT_NO_THROW(createLogger());
    EXPECT_ANY_THROW(logger->registerLogHandler(nullptr));
}

TEST_F(TestLoggerFixture, TestConstructionAndDestructionDelegationToStrategy) {

    ASSERT_TRUE(mockLoggerStrategyRaw);

    testing::InSequence seq;

    // Verify delegation to the strategy when starting the logger...
    ASSERT_NO_THROW(createLogger());
    ASSERT_NO_THROW(logger.reset());
}

TEST_F(TestLoggerFixture, TestLoggerNotifyingAfterLogging) {

    // Synchronization means for the test.
    std::mutex mutex;
    std::condition_variable conditionVariable;
    bool callbackFinished(false);

    const LogLevel logLevel(LogLevel::LOG_LEVEL_DEBUG);
    const std::string messageIn("Hello world!");
    const std::string messageOut("12:34:56 42 Debug Hello world!");
    const std::thread::id testThreadID(std::this_thread::get_id());

    std::thread::id loggerThreadID;
    MockLoggedHandler mockOnLoggedHandler;

    ASSERT_NO_THROW(createLogger());
    ASSERT_TRUE(mockLoggerStrategyRaw);

    // Expect the actual log call on the strategy returning some string...
    EXPECT_CALL(*mockLoggerStrategyRaw, logEntry(_)).WillRepeatedly(Invoke([&](const LogEntry& entry) -> LoggedEntry {
        loggerThreadID = std::this_thread::get_id();

        // Todo: Check construction of the time-point.
        // EXPECT_NE(std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds>(), std::get<0>(entry));
        EXPECT_EQ(testThreadID, std::get<1>(entry));
        EXPECT_EQ(logLevel, std::get<2>(entry));
        EXPECT_EQ(messageIn, std::get<3>(entry));

        return std::make_tuple(logLevel, messageOut);
    }));

    // ...and the callback when finished...
    EXPECT_CALL(mockOnLoggedHandler, onMessageLogged(_)).WillOnce(
        Invoke([&](const LoggedEntry& loggedEntry) {

        EXPECT_EQ(loggerThreadID, std::this_thread::get_id());
        EXPECT_EQ(logLevel, std::get<0>(loggedEntry));
        EXPECT_EQ(messageOut, std::get<1>(loggedEntry));

        callbackFinished = true;
        conditionVariable.notify_one();
    }));

    // Register the callback-handler.
    LogHandlerSignalConnection connection;
    EXPECT_NO_THROW(connection = logger->registerLogHandler(std::bind(&MockLoggedHandler::onMessageLogged, &mockOnLoggedHandler,
        std::placeholders::_1)));

    std::unique_lock<std::mutex> lock(mutex);
    EXPECT_NO_THROW(logger->log(logLevel, messageIn));

    // Wait for the logger thread to have fulfilled the callback.
    ASSERT_NO_THROW([&]() {
        if (!conditionVariable.wait_for(lock, std::chrono::seconds(5), [&]() {
            return callbackFinished; })) {
            throw std::exception("No callback received.");
        }
    }());

    // Unregistering the handler should not result in a callback any more...
    connection.disconnect();
    EXPECT_CALL(mockOnLoggedHandler, onMessageLogged(_)).Times(0);
    EXPECT_NO_THROW(logger->log(logLevel, messageIn));

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

// Todo: How does the logger behave in case of the strategy invoked throws an exception - or the logger thread itself?

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
