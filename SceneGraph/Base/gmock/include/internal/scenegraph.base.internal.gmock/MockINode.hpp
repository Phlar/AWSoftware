#ifndef AWSOFTWARE_SCENEGRAPH_BASE_INTERNAL_GMOCK_MOCKINODE_HPP
#define AWSOFTWARE_SCENEGRAPH_BASE_INTERNAL_GMOCK_MOCKINODE_HPP

#include <memory>

#include <gmock/gmock.h>

#include "scenegraph.base.internal/INode.hpp"


namespace aw {
namespace scenegraph {
namespace base {
namespace internal {

class MockINode;
using MockINodePtr = std::shared_ptr<MockINode>;

class MockINode : public INode {

    public:

        static MockINodePtr create();

        MockINode() = default;
        virtual ~MockINode() = default;

        MOCK_METHOD1(accept, void(INodeVisitorPtr&));
};

} // namespace internal
} // namespace base
} // namespace scenegraph
} // namespace aw

#endif // AWSOFTWARE_SCENEGRAPH_BASE_INTERNAL_GMOCK_MOCKINODE_HPP