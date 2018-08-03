
#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING

#include <gtest/gtest.h>

#include "scenegraph.base\NodeInstance.hpp"

//
//using namespace testing;
//
//
//struct SceneObjectTrait {
//
//    using TInstance = SceneObject;
//
//    using TOccurrence = Occurrence<SceneObject>;
//
//};
//
//
//
//struct GroupObjectTrait {
//
//    using TInstance = GroupObject;
//
//    using TOccurrence = Occurrence<GroupObject>;
//
//};
//
//
//
//
//class ISceneObject {};
//class IGroupObject : public ISceneObject {};
//class IOccurrence : public ISceneObject {};
//class IShapeObject : public ISceneObject {};
//
//
//
//template<typename T>
//class Occurrence : public IOccurrence,
//                   public internal::NodeOccurrence<>
//
//    public NodeOccurrence<T> {
//
//
//};
//
//
//
//template<typename T> 
//class SceneObject : public ISceneObject
//
//    public SceneObject<T> {
//
//    public:
//        std::string m_name;
//};
//
//class GroupObject : public IGroupObject,
//    public SceneObject<GroupObjectTrait> {
//};
//
//class ShapeObject : public IShapeObject,
//    public SceneObject<ShapeObjectTrait> {
//};


// using namespace aw::scenegraph::base;
// using namespace aw::scenegraph::base::internal;

//class FakeSceneComponentInstance;
//using FakeSceneComponentInstancePtr = std::shared_ptr<FakeSceneComponentInstance>;
//
//class FakeSceneComponentInstance : public NodeInstance<FakeSceneComponentInstance> {
//
//    public:
//        FakeSceneComponentInstance() = default;
//        ~FakeSceneComponentInstance() = default;
//
//        FakeSceneComponentInstancePtr createClone() {
//            return std::make_shared<FakeSceneComponentInstance>();
//        }
//
//};
//
//TEST(TestNodes, TestBasicCompilation) {
//
//    auto instance(std::make_shared<NodeInstance<FakeSceneComponentInstance>>());
//    auto occurrenceA(instance->createOccurrence());
//    auto occurrenceB(instance->createOccurrence());
//    auto occurrenceC(instance->createOccurrence());
//    auto occurrenceD(instance->createOccurrence());
//    auto occurrenceE(instance->createOccurrence());
//    auto occurrenceF(instance->createOccurrence());
//    auto occurrenceG(instance->createOccurrence());
//    auto occurrenceH(instance->createOccurrence());
//
//    occurrenceA.reset();
//    occurrenceB.reset();
//    occurrenceC.reset();
//    occurrenceD.reset();
//    occurrenceE.reset();
//    occurrenceF.reset();
//    occurrenceG.reset();
//    occurrenceH.reset();
//
//    auto instanceClone(instance->createClone());
//
//}


int main(int argc, char **argv) {
     testing::InitGoogleTest(&argc, argv);
     return RUN_ALL_TESTS();
}