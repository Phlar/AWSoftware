#include "base.module/ModuleProvider.hpp"

#include <algorithm>
#include <mutex>

namespace aw {
namespace base {

std::atomic_flag ModuleProvider::m_instanceLock = ATOMIC_FLAG_INIT;
ModuleProviderWeakPtr ModuleProvider::m_weakInstance = ModuleProviderPtr(nullptr);


ModuleProviderPtr ModuleProvider::getInstance() {

    ModuleProviderPtr instance(nullptr);

    // Check / construction should be fast enough so a spin lock should be sufficient here.
    while (m_instanceLock.test_and_set()) {};  // Spin as long as the flag is not set to 'false'.

    instance = m_weakInstance.lock();
    if (!instance) {
        instance = ModuleProviderPtr(new ModuleProvider()); // Can't use make_shared because of visibility.
        m_weakInstance = instance;
    }

    m_instanceLock.clear(); // Indicate to stop spinning.
    return instance;
}


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
