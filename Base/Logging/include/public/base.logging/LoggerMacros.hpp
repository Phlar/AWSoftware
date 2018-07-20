#ifndef AWSOFTWARE_BASE_LOGGING_LOGGERTYPES_HPP
#define AWSOFTWARE_BASE_LOGGING_LOGGERTYPES_HPP

#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <tuple>


#include <boost/signals2.hpp>

#include "base.common/Signals.hpp"


namespace aw {
namespace base {
namespace logging {


enum class LogLevel {
    LOG_LEVEL_ERROR = 0,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_DEBUG
};

inline std::ostream& operator<<(std::ostream& stream, const LogLevel& rhs) {

    switch (rhs) {
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


using LogEntry = std::tuple<
    std::chrono::system_clock::time_point,
    std::thread::id,
    LogLevel,
    std::string>;

using LoggedEntry = std::tuple<
    LogLevel,
    std::string>;

using LogHandler = std::function<void(const LoggedEntry&)>;
using LogHandlerSignalConnection = boost::signals2::connection;
using LogHandlerSignal = boost::signals2::signal<void(const LoggedEntry&)>;

} // namespace logging
} // namespace base
} // namespace aw

#endif // AWSOFTWARE_BASE_LOGGING_LOGGERTYPES_HPP