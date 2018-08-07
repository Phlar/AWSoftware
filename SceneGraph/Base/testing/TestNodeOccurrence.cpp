
#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING

#include <gtest/gtest.h>

#include "scenegraph.base.internal/NodeInstance.hpp"
#include "scenegraph.base.internal/NodeOccurrence.hpp"

#include "DerivedNodes.hpp"

using namespace testing;
using namespace aw::scenegraph::base::internal;


TEST(TestNodeOccurrence, TestConstruction) {
    EXPECT_NO_THROW(DerivedNodeOccurrence());
}

TEST(TestNodeOccurrence, TestRetrieveParent) {

    NodeInstancePtr parentInstance;
    EXPECT_NO_THROW(parentInstance = std::make_shared<DerivedNodeInstance>());

    NodeInstancePtr result;
    DerivedNodeOccurrencePtr derivedNodeOccurrence;
    ASSERT_NO_THROW(derivedNodeOccurrence = std::make_shared<DerivedNodeOccurrence>());
    EXPECT_NO_THROW(result = derivedNodeOccurrence->getParent());
    EXPECT_EQ(nullptr, result);

    EXPECT_NO_THROW(derivedNodeOccurrence->setParentInstanceInTest(parentInstance));
    EXPECT_NO_THROW(result = derivedNodeOccurrence->getParent());
    EXPECT_EQ(parentInstance, result);
}


int main(int argc, char **argv) {
     testing::InitGoogleTest(&argc, argv);
     return RUN_ALL_TESTS();
}