#ifndef AWSOFTWARE_SCENEGRAPH_BASE_INTERNAL_TYPEDNODEOCCURRENCE_HPP
#define AWSOFTWARE_SCENEGRAPH_BASE_INTERNAL_TYPEDNODEOCCURRENCE_HPP

#include <memory>

#include "base.common/Assert.hpp"

#include "scenegraph.base.internal/INodeVisitor.hpp"
#include "scenegraph.base.internal/NodeOccurrence.hpp"


namespace aw {
namespace scenegraph {
namespace base {
namespace internal {

template<typename T>
class TypedNodeOccurrence : public NodeOccurrence,
                            public std::enable_shared_from_this<TypedNodeOccurrence<T>> {
    public:

        // Allow friendship to arbitrary typed NodeInstances.
        template<typename U>
        friend class TypedNodeInstance;

        using TypedNodeInstancePtr = std::shared_ptr<TypedNodeInstance<typename T::TInstance>>;

        TypedNodeOccurrence() = delete;
        TypedNodeOccurrence(TypedNodeInstancePtr instance)
        : m_instance(instance) {
            ASSERT(m_instance, "Error setting up node-occurrence, invalid node-instance provided.");
        }

        virtual ~TypedNodeOccurrence() {
        }

        NodeInstancePtr getInstance() const {
            return m_instance;
        }

        void accept(INodeVisitorPtr& visitor) final {
            // Todo: Assert the visitor.
            visitor->visit(shared_from_this());
        }

    protected:

        NodeInstanceWeakPtr m_parent;
        TypedNodeInstancePtr m_instance;
};

} // namespace internal
} // namespace base
} // namespace scenegraph
} // namespace aw

#endif // AWSOFTWARE_SCENEGRAPH_BASE_INTERNAL_TYPEDNODEOCCURRENCE_HPP