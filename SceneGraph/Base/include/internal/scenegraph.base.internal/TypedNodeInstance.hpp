#ifndef AWSOFTWARE_SCENEGRAPH_BASE_INTERNAL_TNODEINSTANCE_HPP
#define AWSOFTWARE_SCENEGRAPH_BASE_INTERNAL_TNODEINSTANCE_HPP

#include <memory>

#include "scenegraph.base.internal/NodeInstance.hpp"
#include "scenegraph.base.internal/TypedNodeOccurrence.hpp"


namespace aw {
namespace scenegraph {
namespace base {
namespace internal {

template<typename T>
class TypedNodeInstance : public NodeInstance,
                          public std::enable_shared_from_this<TypedNodeInstance<T>> {

    public:

        using TypedNodeInstancePtr = std::shared_ptr<TypedNodeInstance<typename T::TInstance>>;
        using TypedNodeOccurrencePtr = std::shared_ptr<TypedNodeOccurrence<typename T::TOccurrence>>;
        using TypedNodeOccurrenceWeakPtr = std::weak_ptr<TypedNodeOccurrence<typename T::TOccurrence>>;

        TypedNodeInstance() {
        }

        virtual ~TypedNodeInstance() {
        }

        TypedNodeInstancePtr createClone() {
            return (static_cast<T*>(this))->createClone();
        }

        TypedNodeOccurrencePtr createOccurrence() {

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

        void addChild(NodeOccurrencePtr occurrence /*boost::optional<std::size_t> position*/) {

            // Todo: Support placing the node at a certain position.
            // Todo: Assert the node.

            if (checkAddingNodeAsChildCausesCycle(occurrence)) {
                // Todo: Log on a meaningful way.
            }

            auto parentInstance(occurrence->getParent());
            if (parentInstance != nullptr && parentInstance != shared_from_this()) {
                parentInstance->removeChild(occurrence);

                m_children.push_back(occurrence);
                // occurrence->(shared_from_this());  // Todo: Adjust the occurrence's parent entry!
            }
        }

        void addChild(NodeInstancePtr instance /*boost::optional<std::size_t> position*/) {

            // Todo: Assert the node.

            if (checkAddingNodeAsChildCausesCycle(occurrence)) {
                // Todo: Log on a meaningful way.
            }

            m_children.push_back(instance);
            instance->m_parents.push_back(shared_from_this());
        }

        void accept(INodeVisitorPtr visitor) final {
            visitor->visit(shared_from_this());
        }

    protected:

        bool checkAddingNodeAsChildCausesCycle(INodePtr node) const {

            // Todo: Assert the node.

            const pathsToRoot(utils::getPathsUpwards(shared_from_this()));
            for (auto& path : pathsToRoot) {
                if (path.find(node) != path.cend()) {
                    return false;
                }
            }
            return true;
        }

        using WeakNodeOccurrenceList = std::list<NodeOccurrenceWeakPtr>;

        WeakNodeOccurrenceList m_occurrences; // Do not alter this to a container that invalidates its iterators when inserting / removing elements!
};

} // namespace internal
} // namespace base
} // namespace scenegraph
} // namespace aw

#endif // AWSOFTWARE_SCENEGRAPH_BASE_INTERNAL_TNODEINSTANCE_HPP