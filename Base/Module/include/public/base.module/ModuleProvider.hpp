#ifndef AWSOFTWARE_BASE_MODULE_MODULEPROVIDER_HPP
#define AWSOFTWARE_BASE_MODULE_MODULEPROVIDER_HPP

#include <algorithm>
#include <list>
#include <memory>

#include "base.module/IModule.hpp"


namespace aw {
namespace base {

// Todo: Add thread safety.
// Well, this one most likely will be a singleton...
class ModuleProvider final {

    public:

        ModuleProvider() = default;
        ~ModuleProvider() = default;

        ModuleProvider(const std::list<IModuleSPtr>&);

        void addModule(IModuleSPtr);
        IModuleSPtr getModule(const ModuleUUID&) const;
        bool hasModule(const ModuleUUID& uuid) const;

    private:

        IModuleSPtr getModuleInternal(const ModuleUUID& uuid) const;

        std::list<IModuleSPtr> m_modules;
};

} // namespace base
} // namespace aw

#endif // AWSOFTWARE_BASE_MODULE_MODULEPROVIDER_HPP