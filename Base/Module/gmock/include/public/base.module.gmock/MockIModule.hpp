#ifndef AWSOFTWARE_BASE_MODULE_GMOCK_MOCKIMODULE_HPP
#define AWSOFTWARE_BASE_MODULE_GMOCK_MOCKIMODULE_HPP

#include <memory>

#include <gmock/gmock.h>


#include "base.module/IModule.hpp"

namespace aw {
namespace base {

class MockIModule;
using MockIModulePtr = std::shared_ptr<MockIModule>;

class MockIModule : public IModule {

    public:

        static MockIModulePtr create();

        MockIModule() = default;
        virtual ~MockIModule() = default;

        MOCK_CONST_METHOD0(getUUID, ModuleUUID());
};

} // namespace base
} // namespace aw

#endif // AWSOFTWARE_BASE_MODULE_GMOCK_MOCKIMODULE_HPP