#include "scenegraph.base.internal/NodeInstance.hpp"

#include <algorithm>


namespace aw {
namespace scenegraph {
namespace base {
namespace internal {

 NodeInstance::NodeInstance()
: m_parents(WeakINodeList())
, m_children(INodeList()) {
}

NodeInstance::~NodeInstance() {
}

INodeList NodeInstance::getParents() const {

    INodeList result;
    std::transform(m_parents.begin(), m_parents.end(), std::back_inserter(result), [](INodeWeakPtr node) {
        return node.lock();
    });
    return result;
}

INodeList NodeInstance::getChildren() const {
    return m_children;
}

} // namespace internal
} // namespace base
} // namespace scenegraph
} // namespace aw