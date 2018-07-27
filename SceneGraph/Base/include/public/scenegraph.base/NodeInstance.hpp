#ifndef AWSOFTWARE_SCENEGRAPH_BASE_NODES_HPP
#define AWSOFTWARE_SCENEGRAPH_BASE_NODES_HPP

#include "scenegraph.base.internal/Node.hpp"


namespace aw {
namespace scenegraph {
namespace base {

namespace detail {

class Node;
using NodePtr = std::shared_ptr<Node>;

class NodeVisitor {

    public:
        NodeVisitor() {
        }

        virtual ~NodeVisitor() {
        }

        virtual void visit(NodePtr) = 0;

};
using NodeVisitorPtr = std::shared_ptr<NodeVisitor>;


// Topmost 'internal' node enabling visitor support.
class Node {

    public:
        Node() {
        }

        virtual ~Node() {
        }

        virtual void accept(NodeVisitorPtr&) = 0;
};

// Merly serving the purpose as tag-interfaces.
class INodeInstance : public Node {};
using INodeInstancePtr = std::shared_ptr<INodeInstance>;
using INodeInstanceWeakPtr = std::weak_ptr<INodeInstance>;

class INodeOccurrence : public Node {};
using INodeOccurrencePtr = std::shared_ptr<INodeOccurrence>;
using INodeOccurrenceWeakPtr = std::weak_ptr<INodeOccurrence>;

} // namespace detail


// Class template forward-declaration.
template<typename T>
class NodeInstance;

template<typename T>
class NodeOccurrence;


template<typename T>
class NodeInstance : public aw::scenegraph::base::detail::INodeInstance,
                     public std::enable_shared_from_this<NodeInstance<T>> {

    public:

        using NodeInstancePtr = std::shared_ptr<NodeInstance<T>>;
        using NodeOccurrencePtr = std::shared_ptr<NodeOccurrence<T>>;
        using NodeOccurrenceWeakPtr = std::weak_ptr<NodeOccurrence<T>>;

        NodeInstance() {
        }

        virtual ~NodeInstance() {
        }

        NodeInstancePtr createClone() {
            return (static_cast<T*>(this))->createClone();
        }

        NodeOccurrencePtr createOccurrence() {

            m_occurrences.push_back(NodeOccurrenceWeakPtr(NodeOccurrencePtr(nullptr)));
            auto iter = std::prev(m_occurrences.end()); // With C++14 at hand this becomes obsolete due to lambda init-captures.
            auto occurrence = NodeOccurrencePtr(
                new NodeOccurrence<T>(shared_from_this()),
                [this, iter](NodeOccurrence<T>* rawOccurrence) {
                    m_occurrences.erase(iter);
                    delete rawOccurrence;
                }
            );
            *iter = occurrence;
            return occurrence;
        }

        void addChild(detail::NodeOccurrencePtr occurrence, /*boost::optional<std::size_t> position*/) {
            // 1) Get all paths of this instance up to the root.
            // 1.1) If one of the paths contains an instance matching the occurrence's "to add" instance, this would lead to a cycle - return.
            // 2) Check whether the occurrence has a parent instance != nullptr.
            //        if so, then detach the node from the parent node.
            // 3) Add it as a new node.
        }

        void addChild(detail::INodeInstancePtr instance, /*boost::optional<std::size_t> position*/) {
            // 1) Get all paths of this instance up to the root.
            // 1.1) If one of the paths contains an instance matching the instance to add, this would lead to a cycle - return.
            // 2) Add it as a new node.
        }

        void accept(detail::NodeVisitorPtr& visitor) final {
            visitor->visit(shared_from_this());
        }

    protected:

        //std::list<NodeWeakPtr> m_parents;
        //std::list<NodePtr> m_children;

        std::list<NodeOccurrenceWeakPtr> m_occurrences; // Do not alter this to a container that invalidates its iterators when inserting / removing elements!
};


template<typename T>
class NodeOccurrence : public aw::scenegraph::base::detail::INodeOccurrence,
                       public std::enable_shared_from_this<NodeOccurrence<T>> {
    public:

        using NodeInstancePtr = std::shared_ptr<NodeInstance<T>>;

        NodeOccurrence(NodeInstancePtr instance)
        : m_instance(instance) {
            // Todo: Assert the instance.
        }

        virtual ~NodeOccurrence() {
        }

        NodeInstancePtr getInstance() const {
            return m_instance;
        }

        void accept(detail::NodeVisitorPtr& visitor) final {
        }

    protected:

        NodeInstancePtr m_instance;
};


} // namespace base
} // namespace scenegraph
} // namespace aw

#endif // AWSOFTWARE_SCENEGRAPH_BASE_NODES_HPP