#include "base.logging.gmock\MockILogger.hpp"

namespace aw {
namespace base {
namespace logging {

MockILoggerPtr MockILogger::create() {
    return std::make_shared<MockILogger>();
}

} // namespace logging
} // namespace base
} // namespace aw