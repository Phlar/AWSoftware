#ifndef AWSOFTWARE_SCENEGRAPH_BASE_TESTING_DERIVEDNODES_HPP
#define AWSOFTWARE_SCENEGRAPH_BASE_TESTING_DERIVEDNODES_HPP

#include "scenegraph.base.internal/NodeInstance.hpp"
#include "scenegraph.base.internal/NodeOccurrence.hpp"


namespace aw {
namespace scenegraph {
namespace base {
namespace internal {

class DerivedNodeOccurrence : public NodeOccurrence {

    public:

        DerivedNodeOccurrence();
        virtual ~DerivedNodeOccurrence();

        void setParentInstanceInTest(NodeInstanceWeakPtr);
        void accept(INodeVisitorPtr&) override;
};
using DerivedNodeOccurrencePtr = std::shared_ptr<DerivedNodeOccurrence>;


class DerivedNodeInstance : public NodeInstance {

    public:

        DerivedNodeInstance();
        virtual ~DerivedNodeInstance();

        void setParentsInTest(const WeakINodeList&);
        void setChildrenInTest(const INodeList&);
        void accept(INodeVisitorPtr&) override;
};
using DerivedNodeInstancePtr = std::shared_ptr<DerivedNodeInstance>;

} // namespace internal
} // namespace base
} // namespace scenegraph
} // namespace aw

#endif // AWSOFTWARE_SCENEGRAPH_BASE_TESTING_DERIVEDNODES_HPP