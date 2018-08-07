#ifndef AWSOFTWARE_BASE_COMMON_ASSERT_HPP
#define AWSOFTWARE_BASE_COMMON_ASSERT_HPP

#include "base.common/StringUtils.hpp"

#define ASSERT(expression, ...) \
    if(!expression) { \
        throw std::runtime_error(aw::base::common::utils::concatenateToString(__VA_ARGS__)); \
    }

#endif // AWSOFTWARE_BASE_COMMON_ASSERT_HPP