#ifndef AWSOFTWARE_BASE_COMMON_STRINGUTILS_HPP
#define AWSOFTWARE_BASE_COMMON_STRINGUTILS_HPP

#include <sstream>

namespace aw {
namespace base {
namespace common {
namespace utils {

namespace detail {

struct StreamWrapper {
    std::stringstream stream;
};

template<typename T>
void concatenateToStringImpl(StreamWrapper& streamWrapper, T& entry) {
    streamWrapper.stream << entry;
}

template<typename... Args, typename T>
void concatenateToStringImpl(StreamWrapper& streamWrapper, T& entry, Args&... rest) {
    streamWrapper.stream << entry;
    concatenateToStringImpl(streamWrapper, rest...);
}

} // namespace detail

template<typename... Args>
std::string concatenateToString(const Args& ... args) {
    detail::StreamWrapper streamWrapper;
    detail::concatenateToStringImpl(streamWrapper, args...);
    return streamWrapper.stream.str();
}

} // namespace utils
} // namespace common
} // namespace base
} // namespace aw

#endif // AWSOFTWARE_BASE_COMMON_STRINGUTILS_HPP