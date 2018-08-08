#include "scenegraph.base.internal.gmock/MockINodeVisitor.hpp"

namespace aw {
namespace scenegraph {
namespace base {
namespace internal {

MockINodeVisitorPtr MockINodeVisitor::create() {
    return std::make_shared<MockINodeVisitor>();
}

} // namespace internal
} // namespace base
} // namespace scenegraph
} // namespace aw