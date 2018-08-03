//#ifndef AWSOFTWARE_SCENEGRAPH_BASE_NODES_HPP
//#define AWSOFTWARE_SCENEGRAPH_BASE_NODES_HPP
//
//#include <algorithm>
//#include <list>
//#include <memory>
//
//#include "scenegraph.base.internal/Node.hpp"
//
//
//namespace aw {
//namespace scenegraph {
//namespace base {
//namespace detail {
//
//
// Merly serving the purpose as tag-interfaces.
//class NodeInstance : public Node {
//
//    public:
//        NodeInstance()
//        : m_parents()
//        , m_children() {
//        }
//
//        virtual ~NodeInstance() {
//        }
//
//        NodeList getParents() const {
//            NodeList result;
//            std::transform(m_parents.begin(), m_parents.end(), std::back_inserter(result), [](NodeWeakPtr node) {
//                return node.lock();
//            });
//        }
//
//        NodeList getChildren() const {
//            return m_children;
//        }
//
//    protected:
//        std::list<NodeWeakPtr> m_parents;
//        NodeList m_children;
//};
//using NodeInstancePtr = std::shared_ptr<NodeInstance>;
//using NodeInstanceWeakPtr = std::weak_ptr<NodeInstance>;
//
//
//
//class NodeOccurrence : public Node {
//
//    public:
//        NodeOccurrence()
//        : m_parent(NodeInstancePtr(nullptr)) {
//        } 
//
//        virtual ~NodeOccurrence() {
//        }
//
//        NodeInstancePtr getParent() const {
//            return m_parent.lock();
//        }
//
//    protected:
//        NodeInstanceWeakPtr m_parent;
//};
//using INodeOccurrencePtr = std::shared_ptr<NodeOccurrence>;
//using INodeOccurrenceWeakPtr = std::weak_ptr<NodeOccurrence>;
//
//
// End - OWN HEADER.
//
//
//
//
// Class template forward-declaration.
//template<typename T>
//class TypedNodeInstance;
//
//template<typename T>
//class TypedNodeOccurrence;
//
//
//template<typename T>
//class TypedNodeInstance : public aw::scenegraph::base::detail::NodeInstance,
//                          public std::enable_shared_from_this<TypedNodeInstance<T>> {
//
//    public:
//
//        using TypedNodeInstancePtr = std::shared_ptr<TypedNodeInstance<T::TInstance>>;
//        using TypedNodeOccurrencePtr = std::shared_ptr<TypedNodeOccurrence<T::TOccurrence>>;
//        using TypedNodeOccurrenceWeakPtr = std::weak_ptr<TypedNodeOccurrence<T::TOccurrence>>;
//
//        TypedNodeInstance() {
//        }
//
//        virtual ~TypedNodeInstance() {
//        }
//
//        TypedNodeInstancePtr createClone() {
//            return (static_cast<T*>(this))->createClone();
//        }
//
//        TypedNodeOccurrencePtr createOccurrence() {
//
//            m_occurrences.push_back(NodeOccurrenceWeakPtr(NodeOccurrencePtr(nullptr)));
//            auto iter = std::prev(m_occurrences.end()); // With C++14 at hand this becomes obsolete due to lambda init-captures.
//            auto occurrence = NodeOccurrencePtr(
//                new NodeOccurrence<T>(shared_from_this()),
//                [this, iter](NodeOccurrence<T>* rawOccurrence) {
//                    m_occurrences.erase(iter);
//                    delete rawOccurrence;
//                }
//            );
//            *iter = occurrence;
//            return occurrence;
//        }
//
//        void addChild(detail::NodeOccurrencePtr occurrence, /*boost::optional<std::size_t> position*/) {
//
//             Todo: Assert the node.
//
//            if (checkAddingNodeAsChildCausesCycle(occurrence)) {
//                 Todo: Log on a meaningful way.
//            }
//
//            auto parentInstance(occurrence->getParent());
//            if (parentInstance != nullptr && parentInstance != shared_from_this()) {
//                parentInstance->removeChild(occurrence);
//
//                m_children.push_back(occurrence);
//                occurrence->(shared_from_this());  // Todo: Won't work!
//            }
//        }
//
//        void addChild(detail::NodeInstancePtr instance, /*boost::optional<std::size_t> position*/) {
//
//             Todo: Assert the node.
//
//            if (checkAddingNodeAsChildCausesCycle(occurrence)) {
//                 Todo: Log on a meaningful way.
//            }
//
//            m_children.push_back(instance);
//            instance->m_parents.push_back(shared_from_this());
//
//             1) Get all paths of this instance up to the root.
//             1.1) If one of the paths contains an instance matching the instance to add, this would lead to a cycle - return.
//             2) Add it as a new node.
//        }
//
//        void accept(detail::NodeVisitorPtr& visitor) final {
//            visitor->visit(shared_from_this());
//        }
//
//    protected:
//
//        bool checkAddingNodeAsChildCausesCycle(NodePtr node) const {
//
//             Todo: Assert the node.
//
//            const pathsToRoot(utils::getPathsUpwards(shared_from_this()));
//            for (auto& path : pathsToRoot) {
//                if (path.find(node) != path.cend()) {
//                    return false;
//                }
//            }
//            return true;
//        }
//
//        std::list<NodeOccurrenceWeakPtr> m_occurrences; // Do not alter this to a container that invalidates its iterators when inserting / removing elements!
//
//        std::list<NodeWeakPtr> m_parents;
//        std::list<NodePtr> m_children;
//};
//
//
//template<typename T>
//class TypedNodeOccurrence : public aw::scenegraph::base::detail::Node,
//                            public std::enable_shared_from_this<TypedNodeOccurrence<T>> {
//    public:
//
//        template<typename U>
//        friend class NodeInstance<U>;
//
//        using TypedNodeInstancePtr = std::shared_ptr<NodeInstance<T::TInstance>>;
//
//        TypedNodeOccurrence() = delete;
//
//        TypedNodeOccurrence(TypedNodeInstancePtr instance)
//        : m_instance(instance) {
//             Todo: Assert the instance.
//        }
//
//        virtual ~TypedNodeOccurrence() {
//        }
//
//        NodeInstancePtr getParent() const {
//            return m_parent.lock();
//        }
//
//        NodeInstancePtr getInstance() const {
//            return m_instance;
//        }
//
//        void accept(detail::NodeVisitorPtr& visitor) final {
//        }
//
//    protected:
//
//        NodeInstanceWeakPtr m_parent;
//        TypedNodeInstancePtr m_instance;
//};
//
//} // namespace detail
//} // namespace base
//} // namespace scenegraph
//} // namespace aw
//
//#endif // AWSOFTWARE_SCENEGRAPH_BASE_NODES_HPP