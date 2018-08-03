#include "scenegraph.base.internal/NodeOccurrence.hpp"

#include "scenegraph.base.internal/NodeInstance.hpp"

namespace aw {
namespace scenegraph {
namespace base {
namespace internal {

NodeOccurrence::NodeOccurrence()
: m_parent(NodeInstancePtr(nullptr)) {
}

NodeOccurrence::~NodeOccurrence() {
}

NodeInstancePtr NodeOccurrence::getParent() const {
    return m_parent.lock();
}

} // namespace internal
} // namespace base
} // namespace scenegraph
} // namespace aw