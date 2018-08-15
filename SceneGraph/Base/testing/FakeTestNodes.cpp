#include "FakeTestNodes.hpp"

namespace aw {
namespace scenegraph {
namespace base {
namespace internal {


FakeTestInstance::FakeTestInstance() {
}

FakeTestInstance::~FakeTestInstance() {
}

FakeTestOccurrence::FakeTestOccurrence(FakeTestInstancePtr instance)
: TypedNodeOccurrence<FakeTestTrait>(instance) {
}

FakeTestOccurrence::~FakeTestOccurrence() {
}

} // namespace internal
} // namespace base
} // namespace scenegraph
} // namespace aw