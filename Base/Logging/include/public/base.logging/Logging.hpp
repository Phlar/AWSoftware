#ifndef AWSOFTWARE_BASE_LOGGING_LOGGING_HPP
#define AWSOFTWARE_BASE_LOGGING_LOGGING_HPP

#include "base.logging/ILogger.hpp"
#include "base.module/ModuleProvider.hpp"
#include "base.common/StringUtils.hpp"

namespace aw {
namespace base {
namespace logging {
namespace detail {

template<typename... Args>
void logMessage(const LogLevel& logLevel, Args&&... args) {

    auto moduleProvider(ModuleProvider::getInstance());

    // Is there a logger installed?
    auto logger(std::dynamic_pointer_cast<ILogger>(moduleProvider->getModule(ILogger::TypeUUID)));
    if(logger) {
        logger->log(logLevel, aw::base::common::utils::concatenateToString(args...));
    }
    else {
        std::cerr << "No logger installed for message: '" << aw::base::common::utils::concatenateToString(args...) << "'\n";
    }
}

} // namespace detail
} // namespace logging
} // namespace base
} // namespace aw

#define LOG_ERROR(...) aw::base::logging::detail::logMessage(aw::base::logging::LogLevel::LOG_LEVEL_ERROR, __VA_ARGS__);
#define LOG_INFO(...) aw::base::logging::detail::logMessage(aw::base::logging::LogLevel::LOG_LEVEL_INFO, __VA_ARGS__);
#define LOG_WARNING(...) aw::base::logging::detail::logMessage(aw::base::logging::LogLevel::LOG_LEVEL_WARNING, __VA_ARGS__);
#define LOG_DEBUG(...) aw::base::logging::detail::logMessage(aw::base::logging::LogLevel::LOG_LEVEL_DEBUG, __VA_ARGS__);

#endif // AWSOFTWARE_BASE_LOGGING_LOGGING_HPP