
#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING

#include <gtest/gtest.h>

#include "scenegraph.base.internal.gmock/MockINodeVisitor.hpp"

#include "scenegraph.base.internal/TypedNodeInstance.hpp"
#include "scenegraph.base.internal/TypedNodeOccurrence.hpp"

#include "FakeTestNodes.hpp"


using namespace testing;
using namespace aw::scenegraph::base::internal;


class TestTypedNodeOccurrenceFixture : public testing::Test {

    public:

        TestTypedNodeOccurrenceFixture()
        : testInstance(nullptr) {
        }

        virtual ~TestTypedNodeOccurrenceFixture() {
        }

        void SetUp() override {

            ASSERT_NO_THROW(testInstance = std::make_shared<FakeTestInstance>());
        }

        FakeTestInstancePtr testInstance;
};


TEST(TestTypedNodeOccurrence, TestConstructionInvalidParameters) {
    EXPECT_ANY_THROW(FakeTestOccurrence(nullptr));
}

TEST_F(TestTypedNodeOccurrenceFixture, TestConstruction) {

    FakeTestOccurrencePtr testOccurrence;
    EXPECT_NO_THROW(testOccurrence = std::make_shared<FakeTestOccurrence>(testInstance));
}

TEST_F(TestTypedNodeOccurrenceFixture, TestGetInstance) {

    FakeTestOccurrencePtr testOccurrence;
    ASSERT_NO_THROW(testOccurrence = std::make_shared<FakeTestOccurrence>(testInstance));

    FakeTestInstancePtr instance;
    EXPECT_NO_THROW(instance = testOccurrence->getInstance());
    EXPECT_EQ(testInstance, instance);
}

TEST_F(TestTypedNodeOccurrenceFixture, TestApplyInvalidVisitorShouldThrow) {

    FakeTestOccurrencePtr testOccurrence;
    ASSERT_NO_THROW(testOccurrence = std::make_shared<FakeTestOccurrence>(testInstance));

    EXPECT_ANY_THROW(testOccurrence->accept(nullptr));
}

TEST_F(TestTypedNodeOccurrenceFixture, TestApplyVisitor) {

    FakeTestOccurrencePtr testOccurrence;
    ASSERT_NO_THROW(testOccurrence = std::make_shared<FakeTestOccurrence>(testInstance));

    MockINodeVisitorPtr mockINodeVisitor(MockINodeVisitor::create());
    EXPECT_CALL(*mockINodeVisitor, visit(Eq(testOccurrence)));
    EXPECT_NO_THROW(testOccurrence->accept(mockINodeVisitor));
}

int main(int argc, char **argv) {
     testing::InitGoogleTest(&argc, argv);
     return RUN_ALL_TESTS();
}