#include "base.module/ModuleProvider.hpp"

#include <algorithm>


namespace aw {
namespace base {

ModuleProvider::ModuleProvider(const std::list<IModuleSPtr>& modules)
: m_modules() {
    for(auto& module : modules) {
        addModule(module);
	}
}

void ModuleProvider::addModule(IModuleSPtr module) {
	if(!module) {
		throw(std::invalid_argument("Invalid module to register."));
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
	auto iter(std::find_if(m_modules.begin(), m_modules.end(), [&uuid](const IModuleSPtr& module) {
		return module->getUUID() == uuid;
	}));
	return (iter != m_modules.cend()) ? *iter : nullptr;
}

} // namespace base
} // namespace aw
