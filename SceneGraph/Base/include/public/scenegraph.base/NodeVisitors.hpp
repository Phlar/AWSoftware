#ifndef AWSOFTWARE_SCENEGRAPH_BASE_NODEVISITORS_HPP
#define AWSOFTWARE_SCENEGRAPH_BASE_NODEVISITORS_HPP

#include <functional>
#include <list>
#include <pair>

#include "scenegraph.base/NodeInsance.hpp"

namespace aw {
namespace scenegraph {
namespace base {

namespace detail {

};

namespace utils {

using NodeList = std::list<NodePtr>;
using NodePath = std::list<NodePtr>;
using NodePaths = std::list<NodePath>;

using GetNextNodesFnc = std::function<NodeList(NodePtr)>;
using IsFinishedFnc = std::function(bool<NodePtr>);

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

}




// Collects all the paths starting at the 'start-node' down the tree leading to the 
// provided target-node. If no target-node is specified, paths in the entire tree
// will be determined. i.e. all nodes become target-nodes that have no more children attached.
// Todo: Does the latter one make sense? Do we ever have to retrieve all resolved paths?
//       Maybe for serialization-purposes?
static getPathsDownwards(detail::NodePtr startNode, detail::NodePtr targetNode) {

    // Todo: Check the start-node validity.

    // If there's a target-node provided it is way cheaper to invert the path-determination.
    if(targetNode) {
        auto pathsUpwards(getPathsUpwards(targetNode, startNode));
        // Todo: Invert the temporary result.
        const auto pathsDownwards(pathsUpwards);
        return pathsDownwards;
    }
    else {

        // Todo:

    }
}

// Collects all the paths starting at the 'start-node' up the tree leading to the
// provided target-node. If no target-node is specified, the root node will be used 
// as the target-node. i.e. the instance that itself does not have a parent attached.
static getPathsUpwards(detail::NodePtr startNode, detail::NodePtr targetNode = nullptr) {
}




};

} // namespace base
} // namespace scenegraph
} // namespace aw

#endif // AWSOFTWARE_SCENEGRAPH_BASE_NODEVISITORS_HPP