#include "DerivedNodes.hpp"


namespace aw {
namespace scenegraph {
namespace base {
namespace internal {


DerivedNodeOccurrence::DerivedNodeOccurrence()
: NodeOccurrence() {
}

DerivedNodeOccurrence::~DerivedNodeOccurrence() {
}

void DerivedNodeOccurrence::setParentInstanceInTest(NodeInstanceWeakPtr instance) {
    m_parent = instance;
}

void DerivedNodeOccurrence::accept(INodeVisitorPtr&) {
}



DerivedNodeInstance::DerivedNodeInstance()
: NodeInstance() {
}

DerivedNodeInstance::~DerivedNodeInstance() {
}

void DerivedNodeInstance::setParentsInTest(const WeakINodeList& parents) {
    m_parents = parents;
}

void DerivedNodeInstance::setChildrenInTest(const INodeList& children) {
    m_children = children;
}

void DerivedNodeInstance::accept(INodeVisitorPtr&) {
}

} // namespace internal
} // namespace base
} // namespace scenegraph
} // namespace aw