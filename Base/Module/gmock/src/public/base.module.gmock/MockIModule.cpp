#include "base.module.gmock\MockIModule.hpp"

namespace aw {
namespace base {

MockIModulePtr MockIModule::create() {
    return std::make_shared<MockIModule>();
}

} // namespace base
} // namespace aw