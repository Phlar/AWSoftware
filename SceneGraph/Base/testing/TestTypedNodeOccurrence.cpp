
#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING

#include <gtest/gtest.h>

#include "scenegraph.base.internal.gmock/MockINodeVisitor.hpp"

#include "scenegraph.base.internal/TypedNodeInstance.hpp"
#include "scenegraph.base.internal/TypedNodeOccurrence.hpp"


using namespace testing;
using namespace aw::scenegraph::base::internal;

struct TestInstance {
};

struct TestOccurrence {
};

struct TestTrait {
    using TInstance = TestInstance;
    using TOccurrence = TestOccurrence;
};

class TestTypedNodeOccurrenceFixture : public testing::Test {

    public:

        TestTypedNodeOccurrenceFixture()
        : typedNodeInstance(nullptr) {
        }

        virtual ~TestTypedNodeOccurrenceFixture() {
        }

        void SetUp() override {

            ASSERT_NO_THROW(typedNodeInstance = std::make_shared<TypedNodeInstance<TestTrait>>());
        }

        std::shared_ptr<TypedNodeInstance<TestTrait>> typedNodeInstance;
};


TEST(TestTypedNodeOccurrence, TestConstructionInvalidParameters) {
    EXPECT_ANY_THROW(TypedNodeOccurrence<TestTrait>(nullptr));
}

TEST_F(TestTypedNodeOccurrenceFixture, TestConstruction) {

    std::shared_ptr<TypedNodeOccurrence<TestTrait>> typedNodeOccurrence;
    EXPECT_NO_THROW(typedNodeOccurrence = std::make_shared<TypedNodeOccurrence<TestTrait>>(typedNodeInstance));
}

TEST_F(TestTypedNodeOccurrenceFixture, TestGetInstance) {

    std::shared_ptr<TypedNodeOccurrence<TestTrait>> typedNodeOccurrence;
    ASSERT_NO_THROW(typedNodeOccurrence = std::make_shared<TypedNodeOccurrence<TestTrait>>(typedNodeInstance));

    NodeInstancePtr instance;
    EXPECT_NO_THROW(instance = typedNodeOccurrence->getInstance());
    EXPECT_EQ(typedNodeInstance, instance);
}

TEST_F(TestTypedNodeOccurrenceFixture, TestApplyInvalidVisitorShouldThrow) {

    std::shared_ptr<TypedNodeOccurrence<TestTrait>> typedNodeOccurrence;
    ASSERT_NO_THROW(typedNodeOccurrence = std::make_shared<TypedNodeOccurrence<TestTrait>>(typedNodeInstance));

    EXPECT_ANY_THROW(typedNodeOccurrence->accept(nullptr));
}

TEST_F(TestTypedNodeOccurrenceFixture, TestApplyVisitor) {

    std::shared_ptr<TypedNodeOccurrence<TestTrait>> typedNodeOccurrence;
    ASSERT_NO_THROW(typedNodeOccurrence = std::make_shared<TypedNodeOccurrence<TestTrait>>(typedNodeInstance));

    MockINodeVisitorPtr mockINodeVisitor(MockINodeVisitor::create());
    EXPECT_CALL(*mockINodeVisitor, visit(Eq(typedNodeOccurrence)));
    EXPECT_NO_THROW(typedNodeOccurrence->accept(mockINodeVisitor));
}

int main(int argc, char **argv) {
     testing::InitGoogleTest(&argc, argv);
     return RUN_ALL_TESTS();
}