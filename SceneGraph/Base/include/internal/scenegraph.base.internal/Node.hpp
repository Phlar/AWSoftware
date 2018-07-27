#ifndef AWSOFTWARE_SCENEGRAPH_BASE_INTERNAL_NODE_HPP
#define AWSOFTWARE_SCENEGRAPH_BASE_INTERNAL_NODE_HPP

#include <list>
#include <memory>


namespace aw {
namespace scenegraph {
namespace base {
namespace internal {

class Node;
using NodePtr = std::shared_ptr<Node>;
using NodeWeakPtr = std::weak_ptr<Node>;

//
//class Node {
//
//    public:
//
//        Node();
//        virtual ~Node();
//
//    protected:
//
//        // std::list<NodeWeakPtr> m_parents;
//        // std::list<NodePtr> m_children;
//};

} // namespace internal
} // namespace base
} // namespace scenegraph
} // namespace aw

#endif // AWSOFTWARE_SCENEGRAPH_BASE_INTERNAL_NODE_HPP