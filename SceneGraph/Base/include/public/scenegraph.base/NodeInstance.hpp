#ifndef AWSOFTWARE_SCENEGRAPH_BASE_NODES_HPP
#define AWSOFTWARE_SCENEGRAPH_BASE_NODES_HPP

#include "scenegraph.base.internal/Node.hpp"


namespace aw {
namespace scenegraph {
namespace base {

// Class template forward-declaration.
template<typename T>
class NodeInstance;

template<typename T>
class NodeOccurrence;


template<typename T>
class NodeInstance : public Node,
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

    protected:

        std::list<NodeOccurrenceWeakPtr> m_occurrences; // Do not alter this to a container that invalidates its iterators when inserting / removing elements!
};


template<typename T>
class NodeOccurrence : public Node {

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

    protected:

        NodeInstancePtr m_instance;
};


} // namespace base
} // namespace scenegraph
} // namespace aw

#endif // AWSOFTWARE_SCENEGRAPH_BASE_NODES_HPP