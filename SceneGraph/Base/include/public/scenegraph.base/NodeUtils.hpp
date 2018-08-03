/*#ifndef AWSOFTWARE_SCENEGRAPH_BASE_NODEUTILS_HPP
#define AWSOFTWARE_SCENEGRAPH_BASE_NODEUTILS_HPP

#include <functional>
#include <list>
#include <pair>

#include "scenegraph.base/NodeInstance.hpp"

namespace aw {
namespace scenegraph {
namespace base {
namespace detail {

class NodeCollectingVisitor : public NodeVisitor {

    public:
        NodeCollectingVisitor()
        : m_nodes() {
        }

        virtual ~NodeCollectingVisitor() {
        }

        const NodeList& getNodes() const {
            return m_nodes;
        }

    protected:

        NodeList m_nodes;
};

class RetrieveParentsVisitor : public NodeCollectingVisitor {

    public:

        RetrieveParentsVisitor() {
        }

        virtual ~RetrieveParentsVisitor() {
        }

        void visit(NodePtr) {
            // Todo: Assert here!
        }

        void visit(INodeInstancePtr instance) {
            // Todo: Assert the instance validity.
            m_nodes.insert(m_nodes.end(), instance->getParents());
        }

        void visit(INodeOccurrencePtr occurrence) {
            // Todo: Assert the occurrence's validity.
            m_nodes.push_back(occurrence->getParent());
        }

};


class RetrieveChildrenVisitor : public NodeCollectingVisitor {

    public:
        RetrieveChildrenVisitor() {
        }

        virtual ~RetrieveChildrenVisitor() {
        }

        void visit(NodePtr) {
            // Todo: Assert here!
        }

        void visit(INodeInstancePtr instance) {
            m_nodes.insert(m_nodes.end(), instance->getChildren());
        }

        void visit(INodeOccurrencePtr) {
        }
};

class RetrieveChildrenVisitor : public NodeVisitor {

};

} // namespace detail

namespace utils {

using NodeList = std::list<NodePtr>;
using NodePath = std::list<NodePtr>;
using NodePaths = std::list<NodePath>;

using GetNextNodesFnc = std::function<NodeList(NodePtr)>;
using IsFinishedFnc = std::function(bool<NodePtr>);


// Todo: Move to cpp.
NodePaths getPaths(NodePtr startNode, GetNextNodesFnc getNextNodesFnc, IsFinishedFnc isFinishedFnc) {

    using QueueEntry = std::pair<NodePtr, NodePath>;
    using Queue = std::list<QueueEntry>;

    NodesPaths result;
    Queue toProcess;

    // Place the first entry.
    toProcess.push_back(std::make_pair(startNode, NodePath));

    do {

        Queue newPathsToProcess;

        std::erase(std::remove_if(toProcess.begin(), toProcess.end(), 
            [&](QueueEntry& entry) {

                if(isFinishedFnc(entry.first)) {
                    result.push_back(entry.second);
                    return true;
                } else {
                    auto nextNodes(getNextNodesFnc(entry.first));

                    // Todo: Assert if there's no node returned - we're not finished and not receiving any more nodes, that's an error.

                    const auto currentPath(entry.second);
                    
                    // Treat the first 'new' node...
                    entry.second.push_back(entry.first);
                    entry.first = nextNodes.front();
                    nextNodes.pop_front();

                    // ...all (additional (starting at the 'second' node) nodes form new paths.
                    for (auto iter(nextNodes.begin()); iter != nextNodes.end(), ++iter) {
                        newPathsToProcess.push_back(std::make_pair(*iter, currentPath));
                    }
                    return false;
                }
        }));

        toProcess.splice(toProcess.end(), std::move(newPathsToProcess));

    } while(!toProcess.empty());

    return result;
}


// Collects all the paths starting at the 'start-node' down the tree leading to the 
// provided target-node. If no target-node is specified, paths in the entire tree
// will be determined. i.e. all nodes become target-nodes that have no more children attached.
// Todo: Does the latter one make sense? Do we ever have to retrieve all resolved paths?
//       Maybe for serialization-purposes?
static NodePaths getPathsDownwards(detail::NodePtr startNode, detail::NodePtr targetNode) {

    NodePaths result;

    // Todo: Check the start-node validity.

    // If there's a target-node provided it is way cheaper to invert the path-determination.
    if(targetNode) {
        auto pathsUpwards(getPathsUpwards(targetNode, startNode));
        // Todo: Invert the temporary result.
        result = pathsUpwards;
    }
    else {

        using GetNextNodesFnc = std::function<NodeList(NodePtr)>;
        using IsFinishedFnc = std::function(bool<NodePtr>);

        result = getPaths(startNode, nullptr, 
            [](NodePtr node){
                // Todo: Avoid recreating the visitor each time.
                auto nodeCollector(std::make_shared<RetrieveChildrenVisitor>());
                node->accept(visitor);
                return nodeCollector->getNodes();
            },
            [&targetNode](NodePtr node) {
                return (targetNode == node);
            },
        );
    }
    return result;
}

// Collects all the paths starting at the 'start-node' up the tree leading to the
// provided target-node. If no target-node is specified, the root node will be used 
// as the target-node. i.e. the instance that itself does not have a parent attached.
static getPathsUpwards(detail::NodePtr startNode, detail::NodePtr targetNode = nullptr) {

    NodePaths result;

    // Todo: Check the start-node validity.

    // If there's a target-node provided it is way cheaper to invert the path-determination.
    if (targetNode) {
        auto pathsUpwards(getPathsUpwards(targetNode, startNode));
        // Todo: Invert the temporary result.
        result = pathsUpwards;
    }
    else {

        using GetNextNodesFnc = std::function<NodeList(NodePtr)>;
        using IsFinishedFnc = std::function(bool<NodePtr>);

        result = getPaths(startNode, nullptr,
            [](NodePtr node) {
                // Todo: Avoid recreating the visitor each time.
                auto nodeCollector(std::make_shared<RetrieveParentsVisitor>());
                node->accept(visitor);
                return nodeCollector->getNodes();
            },
            [&targetNode](NodePtr node) {
                // Todo: Avoid recreating the visitor each time.
                // Todo: Check whether the visitor could - for both lambdas - be kept outside
                //       instead of creating / evaluating it in both lambdas.
                if (targetNode) {
                    return (targetNode == node);
                } else {
                    auto nodeCollector(std::make_shared<RetrieveParentsVisitor>());
                    node->accept(visitor);
                    const auto parents(nodeCollector->getNodes());
                    if (parents.empty()) {
                        return true;
                    } else if (parents.size() == 1) {
                        return parents.front() == nullptr;
                    }
                    return false;
                }
            },
        );
    }
    return result;
}


} // namespace base
} // namespace scenegraph
} // namespace aw

#endif // AWSOFTWARE_SCENEGRAPH_BASE_NODEUTILS_HPP*/