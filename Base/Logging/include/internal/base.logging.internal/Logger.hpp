#ifndef AWSOFTWARE_BASE_LOGGING_INTERNAL_LOGGER_HPP
#define AWSOFTWARE_BASE_LOGGING_INTERNAL_LOGGER_HPP

#include <chrono>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <tuple>

#include <boost/signals2.hpp>

#include "base.module/IModule.hpp"
#include "base.logging/ILogger.hpp"

namespace aw {
namespace base {
namespace logging {

template<class T>
class Logger : public ILogger {

      public:
		Logger() = delete;
		Logger(std::unique_ptr<T>&& strategy)
		: m_exitThread(false)
		, m_thread(nullptr)
		, m_mutex()
		, m_waitCondition()
		, m_entries()
		, m_logHandlerSignal()
		, m_strategy(std::move(strategy)) {

            if(!m_strategy) {
                throw std::invalid_argument("Error setting up logger, invalid strategy defined.");
            }

			// Start the logger's thread.
			m_thread = std::unique_ptr<std::thread>(new std::thread([this](){

				// Prepare the strategy.
				m_strategy->open();

				// Process incoming log-messages.
				while(!m_exitThread.load()) {

					// Process all messages.
					std::unique_lock<std::mutex> uniqueLock(m_mutex);

					while(!m_entries.empty()) {
                        const auto loggedEntry(m_strategy->logEntry(m_entries.front()));
                        m_logHandlerSignal(loggedEntry);
						m_entries.pop();
					}

					// No need to protect against spurious wakeups here.
					m_waitCondition.wait(uniqueLock);
				}

				// Let the logging-strategy finish.
				m_strategy->close();
			}));
		}

		virtual ~Logger() {

			if(m_thread) {
				m_exitThread.store(true);
				m_waitCondition.notify_all();
				m_thread->join();
			}
        }

        ModuleUUID getUUID() const override {
			return ILogger::TypeUUID;
        }

        LogHandlerSignalConnection registerLogHandler(LogHandler handler) override {

            if (!handler) {
                throw std::invalid_argument("Error registering logging-handler, invalid handler provided.");
            }

            return m_logHandlerSignal.connect(handler);
        }

        void log(const LogLevel& level, const std::string& message) override {

            std::chrono::system_clock::time_point g(std::chrono::system_clock::now());

			const LogEntry entry(std::make_tuple(std::chrono::system_clock::now(), std::this_thread::get_id(), level, message));
			{
				std::lock_guard<std::mutex> guard(m_mutex);
				m_entries.push(std::move(entry));
			}
			m_waitCondition.notify_all();
		}

    private:

        std::atomic<bool> m_exitThread;
        std::unique_ptr<std::thread> m_thread;
        std::mutex m_mutex;
        std::condition_variable m_waitCondition;

        std::queue<LogEntry> m_entries;
        LogHandlerSignal m_logHandlerSignal;
        std::unique_ptr<T> m_strategy;
};

} // namespace logging
} // namespace base
} // namespace aw

#endif // AWSOFTWARE_BASE_LOGGING_INTERNAL_LOGGER_HPP