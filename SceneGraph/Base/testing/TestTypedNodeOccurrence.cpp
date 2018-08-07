
#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING

#include <gtest/gtest.h>

#include "scenegraph.base.internal/TypedNodeOccurrence.hpp"


using namespace aw::scenegraph::base::internal;

struct TestInstance {
};

struct TestOccurrence {
};

struct TestTrait {
    using TInstance = TestInstance;
    using TOccurrence = TestOccurrence;
};


TEST(TestTypedNodeOccurrence, TestConstructionInvalidParameters) {

    EXPECT_ANY_THROW(TypedNodeOccurrence<TestTrait>(nullptr));
}


int main(int argc, char **argv) {
     testing::InitGoogleTest(&argc, argv);
     return RUN_ALL_TESTS();
}