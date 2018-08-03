#ifndef AWSOFTWARE_SCENEGRAPH_BASE_INTERNAL_NODEOCCURRENCE_HPP
#define AWSOFTWARE_SCENEGRAPH_BASE_INTERNAL_NODEOCCURRENCE_HPP

#include <memory>

#include "scenegraph.base.internal/INode.hpp"


namespace aw {
namespace scenegraph {
namespace base {
namespace internal {

class NodeInstance;
using NodeInstancePtr = std::shared_ptr<NodeInstance>;
using NodeInstanceWeakPtr = std::weak_ptr<NodeInstance>;

class NodeOccurrence : public INode {

    public:

        NodeOccurrence();
        virtual ~NodeOccurrence();

        NodeInstancePtr getParent() const;

    protected:

        NodeInstanceWeakPtr m_parent;
};

using NodeOccurrencePtr = std::shared_ptr<NodeOccurrence>;
using NodeOccurrenceWeakPtr = std::weak_ptr<NodeOccurrence>;

} // namespace internal
} // namespace base
} // namespace scenegraph
} // namespace aw

#endif // AWSOFTWARE_SCENEGRAPH_BASE_INTERNAL_NODEOCCURRENCE_HPP