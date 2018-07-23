#ifndef AWSOFTWARE_BASE_MODULE_MODULEPROVIDER_HPP
#define AWSOFTWARE_BASE_MODULE_MODULEPROVIDER_HPP

#include <algorithm>
#include <atomic>
#include <map>
#include <memory>
#include <shared_mutex>

#include "base.module/IModule.hpp"

namespace aw {
namespace base {

class ModuleProvider;
using ModuleProviderPtr = std::shared_ptr<ModuleProvider>;
using ModuleProviderWeakPtr = std::weak_ptr<ModuleProvider>;

class ModuleProvider final {

    public:

        using ModuleMapping = std::map<ModuleUUID, IModulePtr>;

        static ModuleProviderPtr getInstance();

        ~ModuleProvider();
        ModuleProvider(const ModuleProvider&) = delete;
        ModuleProvider& operator=(const ModuleProvider&) = delete;

        void addModule(IModulePtr);
        IModulePtr getModule(const ModuleUUID&) const;
        bool hasModule(const ModuleUUID& uuid) const;

    private:

        ModuleProvider();

        IModulePtr getModuleInternal(const ModuleUUID& uuid) const;

        ModuleMapping m_modules;
        mutable std::shared_mutex m_accessMutex;


        // Claim weak-ownership on ourselves. This means that the module-provider will be
        // alive as long as at least one client owns a shared_ptr on it.
        static ModuleProviderWeakPtr m_weakInstance;

        // Means implementing a spin-lock upon retrieving the instance of the ModuleProvider.
        // (semantically equal to std::atomic<bool>, however with less functions available).
        // When using C++20 one can omit this 'flag' and rater use std::atomic<weak_ptr<T>> for
        // the above weak-ownership.
        static std::atomic_flag m_instanceLock;
};

} // namespace base
} // namespace aw

#endif // AWSOFTWARE_BASE_MODULE_MODULEPROVIDER_HPP
