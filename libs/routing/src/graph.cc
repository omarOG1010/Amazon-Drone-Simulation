#include "graph.h"
#include <limits>

namespace routing {

/**
 * Retrieves the bounding box of the graph.
 *
 * @return The bounding box of the graph.
 */
BoundingBox GraphBase::GetBoundingBox() const {
    BoundingBox bb;

    // Retrieve all nodes in the graph
    const std::vector<IGraphNode*>& nodes = GetNodes();
    
    // Calculate the bounding box by iterating through all nodes
    for (int i = 0; i < nodes.size(); i++) {
        std::vector<float> pos = nodes[i]->GetPosition();
        if (i == 0) {
            bb.min = pos;  // Set initial minimum position
            bb.max = pos;  // Set initial maximum position
        }
        else {
            // Update minimum and maximum positions
            for (int j = 0; j < pos.size(); j++) {
                if (bb.min[j] > pos[j]) {
                    bb.min[j] = pos[j];  // Update minimum position
                }
                if (bb.max[j] < pos[j]) {
                    bb.max[j] = pos[j];  // Update maximum position
                }
            }
        }
    }

    return bb;
}

/**
 * Finds the nearest node to a given point using a specified distance function.
 *
 * @param point The point for which to find the nearest node.
 * @param distanceFunction The distance function used for calculating distances.
 * @return A pointer to the nearest node.
 */
const IGraphNode* GraphBase::NearestNode(std::vector<float> point, const DistanceFunction& distanceFunction) const {
    const std::vector<IGraphNode*> nodes = GetNodes();
    float minDistance = std::numeric_limits<float>::infinity();
    const IGraphNode* closestNode = NULL;
    // Iterate through all nodes to find the closest one to the given point
    for (auto* node: nodes) {
        auto temp_3d = node->GetPosition();
        float distance = distanceFunction.Calculate(temp_3d, point);
        if (distance < minDistance) {
            closestNode = node;
            minDistance = distance;
        }
    }

    return closestNode;
}

/**
 * Computes a path between two points using a specified routing strategy.
 *
 * @param src The source point.
 * @param dest The destination point.
 * @param pathing The routing strategy used for pathfinding.
 * @return A list of points representing the path between the source and destination.
 */
const std::vector< std::vector<float> > GraphBase::GetPath(std::vector<float> src, std::vector<float> dest, const RoutingStrategy& pathing) const {
    using namespace std;
    // Find the nearest nodes to the source and destination points
    const IGraphNode* start_node = NearestNode(src, EuclideanDistance());
    const IGraphNode* end_node = NearestNode(dest, EuclideanDistance());

    // Compute the path using the specified routing strategy
    vector<string> string_path = pathing.GetPath(this, start_node->GetName(), end_node->GetName());

    // Convert the path from node names to positions
    vector< vector<float> > position_path;
    position_path.push_back(start_node->GetPosition());
    for (int i = 0; i < string_path.size(); i++) {
        position_path.push_back(this->GetNode(string_path[i])->GetPosition());
    }
    position_path.push_back(end_node->GetPosition());

    return position_path; 
}

}

