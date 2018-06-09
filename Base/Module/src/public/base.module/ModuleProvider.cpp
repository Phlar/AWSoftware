#include "base.module/ModuleProvider.hpp"

#include <algorithm>
#include <mutex>

namespace aw {
namespace base {

ModuleProvider::ModuleProvider()
: m_modules()
, m_accessMutex() {
}

ModuleProvider::~ModuleProvider() {
}

void ModuleProvider::addModule(IModuleSPtr module) {

    if(!module) {
        throw(std::invalid_argument("Invalid module to register."));
    }
   
    std::unique_lock<std::shared_mutex> uniqueLock(m_accessMutex);
    const auto result(m_modules.insert(std::make_pair(module->getUUID(), module)));
    if(!result.second) {
        // Todo: Log me!
    }
}

IModuleSPtr ModuleProvider::getModule(const ModuleUUID& uuid) const {

    return getModuleInternal(uuid);
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
