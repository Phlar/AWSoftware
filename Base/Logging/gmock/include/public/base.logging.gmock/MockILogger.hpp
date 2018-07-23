#ifndef AWSOFTWARE_BASE_LOGGING_GMOCK_MOCKIMODULE_HPP
#define AWSOFTWARE_BASE_LOGGING_GMOCK_MOCKIMODULE_HPP

#include <memory>

#include <gmock/gmock.h>

#include "base.module.gmock\MockIModule.hpp"
#include "base.logging\ILogger.hpp"

namespace aw {
namespace base {
namespace logging {

class MockILogger;
using MockILoggerPtr = std::shared_ptr<MockILogger>;

class MockILogger : public MockIModule,
                    public ILogger {

    public:

        static MockILoggerPtr create();

        MockILogger() = default;
        virtual ~MockILogger() = default;

        MOCK_METHOD1(registerLogHandler, LogHandlerSignalConnection(LogHandler));
        MOCK_METHOD2(log, void(const LogLevel&, const std::string&));
};

} // namespace logging
} // namespace base
} // namespace aw

#endif // AWSOFTWARE_BASE_LOGGING_GMOCK_MOCKIMODULE_HPP