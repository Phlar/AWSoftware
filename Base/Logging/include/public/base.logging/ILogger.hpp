#ifndef AWSOFTWARE_BASE_LOGGING_ILOGGER_HPP
#define AWSOFTWARE_BASE_LOGGING_ILOGGER_HPP 

#include <memory>
#include <ostream>

#include "base.common/Signals.hpp"
#include "base.module/IModule.hpp"


namespace aw {
namespace base {
namespace logging {
	
enum class LogLevel {
	LOG_LEVEL_ERROR = 0,
	LOG_LEVEL_INFO,
	LOG_LEVEL_WARNING,
	LOG_LEVEL_DEBUG
};

std::ostream& operator<<(std::ostream& stream, const LogLevel& rhs) {

	switch(rhs) {
		case LogLevel::LOG_LEVEL_ERROR:	  stream << "Error";   break;
		case LogLevel::LOG_LEVEL_INFO:    stream << "Info";    break;
		case LogLevel::LOG_LEVEL_WARNING: stream << "Warning"; break;
		case LogLevel::LOG_LEVEL_DEBUG:   stream << "Debug";   break;
		default: {
			stream << "Unknown LogLevel!";
			break;
		}
	}
	return stream;
}
	

class ILogger : IModule {

	public:
	
		using LogHandler = std::function<const LogLevel&, const std::string&>;
        using LogHandlerSignal = Signal<typename LogHandler::result_type(typename LogHandler::argument_type)>;
        using LogHandlerSignalPtr = std::shared_ptr<LogHandlerSignal>;

		virtual ~ILogger() {
		}

		virtual SignalConnection registerLogHandler(LogHandler) = 0;
        virtual void log(const LogLevel&, const std::string&) = 0;
};
using ILoggerPtr = std::shared_ptr<ILogger>;

} // namespace logging
} // namespace base
} // namespace aw
