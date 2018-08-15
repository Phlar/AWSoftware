#ifndef AWSOFTWARE_SCENEGRAPH_BASE_INTERNAL_TNODEINSTANCE_HPP
#define AWSOFTWARE_SCENEGRAPH_BASE_INTERNAL_TNODEINSTANCE_HPP

#include <memory>

#include "base.common/Assert.hpp"

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

        using TypedNodeInstancePtr = std::shared_ptr<typename T::TInstance>;
        using TypedNodeOccurrencePtr = std::shared_ptr<typename T::TOccurrence>;
        using TypedNodeOccurrenceWeakPtr = std::weak_ptr<typename T::TOccurrence>;
        using TypedNodeOccurrenceList = std::list<TypedNodeOccurrencePtr>;

        TypedNodeInstance() {
        }

        virtual ~TypedNodeInstance() {
        }

        TypedNodeOccurrencePtr createOccurrence() {

            m_occurrences.push_back(TypedNodeOccurrenceWeakPtr(TypedNodeOccurrencePtr(nullptr)));
            auto iter = std::prev(m_occurrences.end()); // With C++14 at hand this becomes obsolete due to lambda init-captures.
            auto occurrence = TypedNodeOccurrencePtr(
                new typename T::TOccurrence(std::static_pointer_cast<typename T::TInstance>(shared_from_this())),
                [this, iter](T::TOccurrence* rawOccurrence) {
                    m_occurrences.erase(iter);
                    delete rawOccurrence;
                }
            );
            *iter = occurrence;
            return occurrence;
        }

        TypedNodeOccurrenceList getOccurrences() const {
            TypedNodeOccurrenceList result;
            std::transform(m_occurrences.begin(), m_occurrences.end(), std::back_inserter(result), [](TypedNodeOccurrenceWeakPtr node) {
                return node.lock();
            });
            return result;
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
            ASSERT(visitor, "Error applying visitor to node-occurrence, invalid visitor-object provided.");
            visitor->visit(shared_from_this());
        }

    private:

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

        using WeakTypedNodeOccurrenceList = std::list<TypedNodeOccurrenceWeakPtr>;
        WeakTypedNodeOccurrenceList m_occurrences; // Do not alter this to a container that invalidates its iterators when inserting / removing elements!
};

} // namespace internal
} // namespace base
} // namespace scenegraph
} // namespace aw

#endif // AWSOFTWARE_SCENEGRAPH_BASE_INTERNAL_TNODEINSTANCE_HPP