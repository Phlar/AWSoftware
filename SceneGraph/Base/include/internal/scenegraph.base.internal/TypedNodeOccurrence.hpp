#ifndef AWSOFTWARE_SCENEGRAPH_BASE_INTERNAL_TYPEDNODEOCCURRENCE_HPP
#define AWSOFTWARE_SCENEGRAPH_BASE_INTERNAL_TYPEDNODEOCCURRENCE_HPP

#include <memory>

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
        friend class NodeInstance<U>;

        using TypedNodeInstancePtr = std::shared_ptr<NodeInstance<T::TInstance>>;

        TypedNodeOccurrence() = delete;
        TypedNodeOccurrence(TypedNodeInstancePtr instance)
        : m_instance(instance) {
            // Todo: Assert the instance.
        }

        virtual ~TypedNodeOccurrence() {
        }

        NodeInstancePtr getInstance() const {
            return m_instance;
        }

        void accept(detail::NodeVisitorPtr& visitor) final {
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