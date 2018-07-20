#ifndef AWSOFTWARE_BASE_LOGGING_ILOGGER_HPP
#define AWSOFTWARE_BASE_LOGGING_ILOGGER_HPP

#include <memory>
#include <ostream>

#include "base.module/IModule.hpp"

#include "base.logging/LoggerTypes.hpp"


namespace aw {
namespace base {
namespace logging {

class ILogger : IModule {

	public:
	
		virtual ~ILogger() {
		}

		virtual LogHandlerSignalConnection registerLogHandler(LogHandler) = 0;
        virtual void log(const LogLevel&, const std::string&) = 0;
};
using ILoggerPtr = std::shared_ptr<ILogger>;

} // namespace logging
} // namespace base
} // namespace aw

#endif // AWSOFTWARE_BASE_LOGGING_ILOGGER_HPP