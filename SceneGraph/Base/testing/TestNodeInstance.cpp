#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING

#include <gtest/gtest.h>

#include "scenegraph.base.internal/NodeInstance.hpp"
#include "scenegraph.base.internal.gmock/MockINode.hpp"


using namespace testing;

using namespace aw::scenegraph::base;
using namespace aw::scenegraph::base::internal;


class DerivedNodeInstance : public NodeInstance {

    public:
    
        DerivedNodeInstance() {
        }
        
        virtual DerivedNodeInstance() {
        }
        
        void setParentsInTest(const WeakINodeList& parents) {
            m_parents = parents;
        }
        
        void setChildrenInTest(const INodeList & children) {
            m_parents = children;
        }
};
using DerivedNodeInstancePtr = std::shared_ptr<DerivedNodeInstance>;


TEST(TestNodeInstance, TestConstruction) {
    EXPECT_NO_THROW(NodeInstance());
}

TEST(TestNodeInstance, TestRetrieveParents) {

    DerivedNodeInstancePtr derivedNodeInstance{nullptr};
    ASSERT_NO_THROW(derivedNodeInstance = std::make_shared<DerivedNodeInstance>());
    
    // Get parents right after construction.
    INodeList result;
    EXPECT_NO_THROW(result = derivedNodeInstance->getParents());
    EXPECT_THAT(INodeList(), ContainerEq(result));
    
    // Get parents after they were set in the test.
    const INodeList parents(INodePtr(nullptr), MockINode::create(), MockINode::create());
    const WeakINodeList weakParents;
    std::transform(parents.begin(), parents.end(), std::back_inserter(weakParents), (INodePtr node)[]{
        return INodeWeakPtr(node);
    });
    EXPECT_NO_THROW(derivedNodeInstance->setParentsInTest(weakParents));
    EXPECT_NO_THROW(result = derivedNodeInstance->getParents());
    EXPECT_THAT(parents, ContainerEq(result));
}

TEST(TestNodeInstance, TestRetrieveChildren) {

    DerivedNodeInstancePtr derivedNodeInstance{nullptr};
    ASSERT_NO_THROW(derivedNodeInstance = std::make_shared<DerivedNodeInstance>());
    
    // Get children right after construction.
    INodeList result;
    EXPECT_NO_THROW(result = derivedNodeInstance->getChildren());
    EXPECT_THAT(INodeList(), ContainerEq(result));
    
    // Get children after they were set in the test.
    const INodeList children(INodePtr(nullptr), MockINode::create(), MockINode::create());
    EXPECT_NO_THROW(derivedNodeInstance->setParentsInTest(children));
    EXPECT_NO_THROW(result = derivedNodeInstance->getChildren());
    EXPECT_THAT(children, ContainerEq(result));
}


int main(int argc, char **argv) {
     testing::InitGoogleTest(&argc, argv);
     return RUN_ALL_TESTS();
}
