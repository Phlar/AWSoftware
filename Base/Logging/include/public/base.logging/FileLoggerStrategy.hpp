#ifndef AWSOFTWARE_BASE_LOGGING_FILELOGGERSTRATEGY_HPP
#define AWSOFTWARE_BASE_LOGGING_FILELOGGERSTRATEGY_HPP

#include "fstream"

#include <mutex>
#include <thread>
#include <tuple>

#include <boost/filesystem.hpp>

#include "base.logging/LoggerTypes.hpp"


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
		LoggedEntry logEntry(const LogEntry&);

	private:

        boost::filesystem::path m_filePath;
		std::ofstream m_stream;
};

} // namespace logging
} // namespace base
} // namespace aw

#endif // AWSOFTWARE_BASE_LOGGING_FILELOGGERSTRATEGY_HPP