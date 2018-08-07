#include "scenegraph.base.internal.gmock\MockINode.hpp"

namespace aw {
namespace scenegraph {
namespace base {
namespace internal {

MockINodePtr MockINode::create() {
    return std::make_shared<MockINode>();
}

} // namespace internal
} // namespace base
} // namespace scenegraph
} // namespace aw