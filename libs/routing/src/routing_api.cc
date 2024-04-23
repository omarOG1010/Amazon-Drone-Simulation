#include "routing_api.h"
#include "parsers/osm/osm_graph_factory.h"
#include "parsers/obj/obj_graph_factory.h"

namespace routing {

/**
 * Constructs a RoutingAPI object.
 * Initializes the factories vector with OSMGraphFactory and ObjGraphFactory.
 */
RoutingAPI::RoutingAPI() {
    factories.push_back(new OSMGraphFactory());
    factories.push_back(new ObjGraphFactory());
}

/**
 * Destroys a RoutingAPI object.
 * Cleans up dynamically allocated factory objects stored in the factories vector.
 */
RoutingAPI::~RoutingAPI() {
    // Clean up dynamically allocated factory objects
    for (int i = 0; i < factories.size(); i++) {
        delete factories[i];
    }
}

/**
 * Loads a graph from a file using the registered graph factories.
 *
 * @param file The path to the file from which to load the graph.
 * @return A pointer to the loaded graph, or NULL if the file format is not supported.
 */
IGraph* RoutingAPI::LoadFromFile(const std::string& file) const {
    // Iterate through the registered graph factories
    for (int i = 0; i < factories.size(); i++) {
        // Attempt to create a graph using the current factory
        IGraph* graph = factories[i]->Create(file);
        // If a graph is successfully created, return it
        if (graph) {
            return graph;
        }
    }

    // If no factory can create a graph, return NULL
    return NULL;
}

/**
 * Adds a new graph factory to the RoutingAPI.
 *
 * @param factory A pointer to the graph factory to add.
 */
void RoutingAPI::AddFactory(const IGraphFactory* factory) {
    // Add the factory to the list of factories
    factories.push_back(factory);
}

}

