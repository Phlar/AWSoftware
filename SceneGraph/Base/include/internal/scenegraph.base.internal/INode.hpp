#ifndef AWSOFTWARE_SCENEGRAPH_BASE_INTERNAL_INODE_HPP
#define AWSOFTWARE_SCENEGRAPH_BASE_INTERNAL_INODE_HPP

#include <list>
#include <memory>


namespace aw {
namespace scenegraph {
namespace base {
namespace internal {

class INodeVisitor;
using INodeVisitorPtr = std::shared_ptr<INodeVisitor>;

class INode {

    public:

        virtual ~INode() = default;

        virtual void accept(INodeVisitorPtr) = 0;
};

using INodePtr = std::shared_ptr<INode>;
using INodeWeakPtr = std::weak_ptr<INode>;
using INodeList = std::list<INodePtr>;

} // namespace internal
} // namespace base
} // namespace scenegraph
} // namespace aw

#endif // AWSOFTWARE_SCENEGRAPH_BASE_INTERNAL_INODE_HPP