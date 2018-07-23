#ifndef AWSOFTWARE_BASE_MODULE_IMODULE_HPP
#define AWSOFTWARE_BASE_MODULE_IMODULE_HPP

#include <memory>

namespace aw {
namespace base {

// Todo: That one should really become an uuid later.
using ModuleUUID = uint64_t;

class IModule {

    public:
        virtual ~IModule() {};

        virtual ModuleUUID getUUID() const = 0;
};
using IModulePtr = std::shared_ptr<IModule>;
using IModuleWeakPtr = std::weak_ptr<IModule>;

} // namespace base
} // namespace aw

#endif // AWSOFTWARE_BASE_MODULE_IMODULE_HPP