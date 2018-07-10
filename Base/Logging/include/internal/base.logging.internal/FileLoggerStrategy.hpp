#ifndef AWSOFTWARE_BASE_LOGGING_INTERNAL_FILELOGGER_HPP
#define AWSOFTWARE_BASE_LOGGING_INTERNAL_FILELOGGER_HPP

#include "fstream"

#include <mutex>
#include <thread>
#include <tuple>

#include <boost/filesystem.hpp>

#include "base.logging/ILogger.hpp"


namespace aw {
namespace base {
namespace logging {

class FileLoggerStrategy final {

    public:

		FileLoggerStrategy() = delete;
		FileLoggerStrategy(const boost::filesystem::path& filePath);
        ~FileLoggerStrategy();

		void open();
		void close();
		void logEntry(const LogEntry&);

	private:

		std::ofstream m_stream;
};

} // namespace logging
} // namespace base
} // namespace aw

#endif // AWSOFTWARE_BASE_LOGGING_INTERNAL_FILELOGGER_HPP