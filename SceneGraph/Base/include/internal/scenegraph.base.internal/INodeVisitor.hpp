#ifndef AWSOFTWARE_SCENEGRAPH_BASE_INTERNAL_INODEVISITOR_HPP
#define AWSOFTWARE_SCENEGRAPH_BASE_INTERNAL_INODEVISITOR_HPP

#include <memory>


namespace aw {
namespace scenegraph {
namespace base {
namespace internal {

class INode;
using INodePtr = std::shared_ptr<INode>;

class INodeVisitor {

    public:

        virtual ~INodeVisitor() = default;

        virtual void visit(INodePtr) = 0;
};

using INodeVisitorPtr = std::shared_ptr<INodeVisitor>;

} // namespace internal
} // namespace base
} // namespace scenegraph
} // namespace aw

#endif // AWSOFTWARE_SCENEGRAPH_BASE_INTERNAL_INODEVISITOR_HPP