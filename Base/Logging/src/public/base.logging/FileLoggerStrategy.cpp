#include "base.logging/FileLoggerStrategy.hpp"

#include <iostream> 

namespace aw {
namespace base {
namespace logging {

FileLoggerStrategy::FileLoggerStrategy(const boost::filesystem::path& filePath)
: m_filePath(filePath)
, m_stream() {
}

FileLoggerStrategy::~FileLoggerStrategy() {
}

void FileLoggerStrategy::open() {

	/*namespace fs = boost::filesystem;
	
	if(!fs::is_file(m_filePath) {
		std::cout << "Error opening log-file '" << m_filePath << "' is not a file."
		return;
	};

	const auto directory(m_filePath.());
	if(!fs::exists(directory)) {
        fs::create_directories(directory);
	}
	m_stream = std::ofstream(m_filePath, std::ofstream::out);*/
}

void FileLoggerStrategy::close() {

	if(m_stream.is_open()) {
		m_stream.close();
	}
}

LoggedEntry FileLoggerStrategy::logEntry(const LogEntry& entry) {

	using namespace std::chrono;
	
	auto convertedTime = system_clock::to_time_t(std::get<0>(entry));
	auto stringTime = std::asctime(std::gmtime(&convertedTime));
	m_stream << stringTime << " "
			 << std::get<1>(entry) << " "
			 << std::get<2>(entry) << " "
			 << std::get<3>(entry) << "\n";

    return LoggedEntry();
}

} // namespace logging
} // namespace base
} // namespace aw
