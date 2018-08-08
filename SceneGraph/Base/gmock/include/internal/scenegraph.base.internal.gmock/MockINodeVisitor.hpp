#ifndef AWSOFTWARE_SCENEGRAPH_BASE_INTERNAL_GMOCK_MOCKINODEVISITOR_HPP
#define AWSOFTWARE_SCENEGRAPH_BASE_INTERNAL_GMOCK_MOCKINODEVISITOR_HPP

#include <memory>

#include <gmock/gmock.h>

#include "scenegraph.base.internal/INodeVisitor.hpp"


namespace aw {
namespace scenegraph {
namespace base {
namespace internal {

class MockINodeVisitor;
using MockINodeVisitorPtr = std::shared_ptr<MockINodeVisitor>;

class MockINodeVisitor : public INodeVisitor {

    public:

        static MockINodeVisitorPtr create();

        MockINodeVisitor() = default;

        MOCK_METHOD1(visit, void(INodePtr&));
};

} // namespace internal
} // namespace base
} // namespace scenegraph
} // namespace aw

#endif // AWSOFTWARE_SCENEGRAPH_BASE_INTERNAL_GMOCK_MOCKINODEVISITOR_HPP