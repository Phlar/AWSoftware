
#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING

#include <gtest/gtest.h>

#include "scenegraph.base.internal.gmock/MockINodeVisitor.hpp"

#include "scenegraph.base.internal/TypedNodeInstance.hpp"
#include "scenegraph.base.internal/TypedNodeOccurrence.hpp"

#include "FakeTestNodes.hpp"


using namespace testing;
using namespace aw::scenegraph::base::internal;


class TestTypedNodeInstanceFixture : public testing::Test {

public:

    TestTypedNodeInstanceFixture()
    : typedNodeInstance(nullptr) {
    }

    virtual ~TestTypedNodeInstanceFixture() {
    }

    void SetUp() override {
        ASSERT_NO_THROW(typedNodeInstance = std::make_shared<TypedNodeInstance<FakeTestTrait>>());
    }

    std::shared_ptr<TypedNodeInstance<FakeTestTrait>> typedNodeInstance;
};


TEST(TestTypedNodeInstance, TestConstruction) {

    std::shared_ptr<FakeTestInstance> testInstance;
    EXPECT_NO_THROW(testInstance = std::make_shared<FakeTestInstance>());
}

TEST_F(TestTypedNodeInstanceFixture, TestCreatedOccurrencesLifetime) {

    FakeTestOccurrencePtr firstOccurrence, secondOccurrence;

    EXPECT_NO_THROW(firstOccurrence = typedNodeInstance->createOccurrence());
    ASSERT_TRUE(firstOccurrence != nullptr);

    EXPECT_NO_THROW(secondOccurrence = typedNodeInstance->createOccurrence());
    ASSERT_TRUE(secondOccurrence != nullptr);

    // Check the referenced instances - scoped since the returned list claims ownership on the occurrences otherwise.
    {
        std::list<FakeTestOccurrencePtr> occurrences;
        EXPECT_NO_THROW(occurrences = typedNodeInstance->getOccurrences());
        EXPECT_THAT(std::list<FakeTestOccurrencePtr>({ firstOccurrence, secondOccurrence }), ContainerEq(occurrences));
    }

    {
        // Resest the created occurrences step by step...
        std::list<FakeTestOccurrencePtr> occurrences;
        firstOccurrence.reset();
        EXPECT_NO_THROW(occurrences = typedNodeInstance->getOccurrences());
        EXPECT_THAT(occurrences, ContainerEq(std::list<FakeTestOccurrencePtr>({ secondOccurrence })));
    }

    {
        std::list<FakeTestOccurrencePtr> occurrences;
        secondOccurrence.reset();
        EXPECT_NO_THROW(occurrences = typedNodeInstance->getOccurrences());
        EXPECT_THAT(occurrences, ContainerEq(std::list<FakeTestOccurrencePtr>({})));
    }
}

// Todo: Add tests on adding / modifying children here.


TEST_F(TestTypedNodeInstanceFixture, TestApplyInvalidVisitorShouldThrow) {

    std::shared_ptr<FakeTestInstance> testInstance;
    ASSERT_NO_THROW(testInstance = std::make_shared<FakeTestInstance>());

    EXPECT_ANY_THROW(testInstance->accept(nullptr));
}

TEST_F(TestTypedNodeInstanceFixture, TestApplyVisitor) {

    std::shared_ptr<FakeTestInstance> testInstance;
    ASSERT_NO_THROW(testInstance = std::make_shared<FakeTestInstance>());

    MockINodeVisitorPtr mockINodeVisitor(MockINodeVisitor::create());
    EXPECT_CALL(*mockINodeVisitor, visit(Eq(testInstance)));
    EXPECT_NO_THROW(testInstance->accept(mockINodeVisitor));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}