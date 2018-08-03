#ifndef AWSOFTWARE_SCENEGRAPH_BASE_INTERNAL_NODEINSTANCE_HPP
#define AWSOFTWARE_SCENEGRAPH_BASE_INTERNAL_NODEINSTANCE_HPP

#include <memory>

#include "scenegraph.base.internal/INode.hpp"


namespace aw {
namespace scenegraph {
namespace base {
namespace internal {

class NodeInstance : public INode {

    public:

        NodeInstance();
        virtual ~NodeInstance();

        INodeList getParents() const;
        INodeList getChildren() const;

    protected:
    
        using WeakINodeList = std::list<INodeWeakPtr>;

        WeakINodeList m_parents;
        INodeList m_children;
};

using NodeInstancePtr = std::shared_ptr<NodeInstance>;
using NodeInstanceWeakPtr = std::weak_ptr<NodeInstance>;

} // namespace internal
} // namespace base
} // namespace scenegraph
} // namespace aw

#endif // AWSOFTWARE_SCENEGRAPH_BASE_INTERNAL_NODEINSTANCE_HPP