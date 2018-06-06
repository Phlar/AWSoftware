#ifndef AWSOFTWARE_BASE_MODULE_MODULEPROVIDER_HPP
#define AWSOFTWARE_BASE_MODULE_MODULEPROVIDER_HPP

#include <algorithm>
#include <map>
#include <memory>
#include <shared_mutex>

#include "base.module/IModule.hpp"

namespace aw {
namespace base {

// Well, this one most likely will be a singleton...
class ModuleProvider final {

    public:

        using ModuleMapping = std::map<ModuleUUID, IModuleSPtr>;

        ModuleProvider();
        virtual ~ModuleProvider();
    
        ModuleProvider(const ModuleProvider&) = delete;
        ModuleProvider& operator=(const ModuleProvider&) = delete;    

        void addModule(IModuleSPtr);
        IModuleSPtr getModule(const ModuleUUID&) const;
        bool hasModule(const ModuleUUID& uuid) const;

    private:

        IModuleSPtr getModuleInternal(const ModuleUUID& uuid) const;

        ModuleMapping m_modules;
        mutable std::shared_mutex m_accessMutex;
};

} // namespace base
} // namespace aw

#endif // AWSOFTWARE_BASE_MODULE_MODULEPROVIDER_HPP
