#include "base.module/ModuleProvider.hpp"

#include <algorithm>
#include <mutex>

namespace aw {
namespace base {

ModuleProvider::ModuleProvider(const std::list<IModuleSPtr>& modules)
: m_modules()
, m_accessMutex() {
    for(auto& module : modules) {
        addModule(module);
    }
}

void ModuleProvider::addModule(IModuleSPtr module) {
    if(!module) {
        throw(std::invalid_argument("Invalid module to register."));
    }
   
    std::unique_lock<std::shared_mutex> uniqueLock(m_accessMutex);
    const auto result(m_modules.insert(std::make_pair(module->getUUID(), module)));
    if(!result.second) {
        // Todo: Log not being able to add module.
    }
}

IModuleSPtr ModuleProvider::getModule(const ModuleUUID& uuid) const {
    auto module(getModuleInternal(uuid));
    if (!module) {
        // Todo: More meaningful message.
        throw(std::logic_error("No module found for uuid"));
    }
    return module;
}

bool ModuleProvider::hasModule(const ModuleUUID& uuid) const {
    return getModuleInternal(uuid) != nullptr;
}

IModuleSPtr ModuleProvider::getModuleInternal(const ModuleUUID& uuid) const {

    std::shared_lock<std::shared_mutex> sharedLock(m_accessMutex);
    const auto iter(m_modules.find(uuid));
    return (iter != m_modules.cend()) ? iter->second : nullptr;
}

} // namespace base
} // namespace aw
