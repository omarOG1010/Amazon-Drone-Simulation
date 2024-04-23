#include "parsers/obj/obj_graph.h"
#include <fstream>

namespace routing {

/**
 * Constructs an ObjGraph object and initializes it using data from an OBJ file.
 *
 * @param file The path to the OBJ file containing the graph data.
 */
ObjGraph::ObjGraph(const std::string& file) {
    // Open the OBJ file
    std::ifstream objFile;
    objFile.open(file);
    
    if (objFile.is_open()) {
        int numNodes = 0;
        std::string in;

        // Read the OBJ file line by line
        while (objFile >> in) {
            // Process vertex data (vertices start with "v" in OBJ format)
            if (in == "v") {
                std::vector<float> pos;
                float x, y, z;
                objFile >> x >> y >> z;
                // Store vertex position as (x, z, -y) to match typical coordinate systems
                pos.push_back(x);
                pos.push_back(z);
                pos.push_back(-y);

                numNodes++;
                // Add a new graph node with the vertex position
                AddNode(new SimpleGraphNode(std::to_string(numNodes), pos));
            }

            // Process face data (faces start with "f" in OBJ format)
            if (in == "f") {
                std::string a, b, c;
                objFile >> a >> b >> c;
                // Add edges between vertices to represent faces
                AddEdge(a, b);
                AddEdge(b, a);
                AddEdge(b, c);
                AddEdge(c, b);
                AddEdge(c, a);
                AddEdge(a, c);
            }
        }

        // Close the OBJ file
        objFile.close();
    }
}

}

