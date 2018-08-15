#ifndef AWSOFTWARE_SCENEGRAPH_BASE_TESTING_FAKETESTNODES_HPP
#define AWSOFTWARE_SCENEGRAPH_BASE_TESTING_FAKETESTNODES_HPP

#include "scenegraph.base.internal/TypedNodeInstance.hpp"
#include "scenegraph.base.internal/TypedNodeOccurrence.hpp"


namespace aw {
namespace scenegraph {
namespace base {
namespace internal {


class FakeTestInstance;
class FakeTestOccurrence;

struct FakeTestTrait {
    using TInstance = FakeTestInstance;
    using TOccurrence = FakeTestOccurrence;
};

class FakeTestInstance : public TypedNodeInstance<FakeTestTrait> {

    public:
        FakeTestInstance();
        virtual ~FakeTestInstance();
};
using FakeTestInstancePtr = std::shared_ptr<FakeTestInstance>;

class FakeTestOccurrence : public TypedNodeOccurrence<FakeTestTrait> {

    public:
        FakeTestOccurrence(FakeTestInstancePtr instance);
        virtual ~FakeTestOccurrence();
};
using FakeTestOccurrencePtr = std::shared_ptr<FakeTestOccurrence>;

} // namespace internal
} // namespace base
} // namespace scenegraph
} // namespace aw

#endif // AWSOFTWARE_SCENEGRAPH_BASE_TESTING_FAKETESTNODES_HPP