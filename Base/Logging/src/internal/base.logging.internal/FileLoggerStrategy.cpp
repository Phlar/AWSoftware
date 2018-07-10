#include "base.logging.internal/FileLoggerStrategy.hpp"

namespace aw {
namespace base {
namespace logging {

FileLoggerStrategy::FileLoggerStrategy(const boost::filesystem::path& filePath)
: m_filePath(filePath)
, m_stream() {
}

~FileLoggerStrategy::FileLoggerStrategy() {
}

void FileLoggerStrategy::open() {

	using filesystem = boost::filesystem;
	
	if(!filesystem::is_file(m_filePath) {
		std::cout << "Error opening log-file '" << m_filePath << "' is not a file."
		return;
	};

	const auto directory(m_filePath.parent_path());
	if(!filesystem::exists(directory)) {
		filesystem::create_directories(directory);
	}
	m_stream = std::ofstream(m_filePath, std::ofstream::out);
}

void FileLoggerStrategy::close() {

	if(m_stream.is_open()) {
		m_stream.close();
	}
}

void FileLoggerStrategy::logEntry(const LogEntry& entry) {

	using namespace std::chrono;
	
	auto convertedTime = system_clock::to_time_t(std::get<0>(entry));
	auto stringTime = std::asctime(std::gmtime(&convertedTime));
	m_stream << stringTime << " "
			 << std::get<1>() << " "
			 << std::get<2>() << " "
			 << std::get<3>() << "\n";
}

} // namespace logging
} // namespace base
} // namespace aw
