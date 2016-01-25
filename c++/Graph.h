//Katherine Sullivan
//CSCI 335 Graph Assignment

#ifndef UNDIRECTED_GRAPH_H
#define UNDIRECTED_GRAPH_H

#include <vector> //std::vector
#include <unordered_map> //std::unordered_map
#include <unordered_set> //std::unordered_set

template<class T>
class Undirected_Graph
{
    public:
    Undirected_Graph();
    
    //create a graph with one node and no edges, for mst()
    Undirected_Graph(const T& first_node);
    
    
    unsigned total_weight() const;

    unsigned count_nodes() const;
    
    unsigned count_edges() const;
    
    bool contains(const T& node) const;
 
 
    //adds an Edge between one and two to both vertices
    //does nothing if: one==two, or there is already such an edge
    //because of the way the graph is built in main it will allow an edge between two new nodes, ie. not connected to the rest
    void connect(const T& one, const T& two, unsigned weight);
 
    //returns a minimum spanning tree using Prim's algorithm, starting with the given node
    //if the graph is not connected it will return an MST of the connected subgraph
    Undirected_Graph minimum_spanning_tree(const T& first) const;
    
    //performs depth first search on a minimum spanning tree beginning from start, up to the given depth limit
    void depth_first_search(const T& start, const unsigned depth_limit) const;
    
    private:
        struct Edge
        {
            Edge(const T& origin, const T& dest, unsigned cost);
            T node1; //can't depend on the map key because in minimum_spanning_tree this will end up by itself in the heap
            T node2;
            unsigned weight;
            
            bool operator>(const Edge& other) const;
            
            bool operator==(const Edge& other) const;
            bool operator!=(const Edge& other) const;
        };
        
        struct Prim //for Prim's algorithm in minimum_spanning_tree()
        {
            unsigned dv=INFINITY;
            T pv;
            bool known=false;
            
            static const unsigned INFINITY=-1;
        };
        
        
        /**
        recursive depth_first_search, prints the current node
        current_node - the node the search is currently on
        distance_from_parent - the cost of traversing from a parent at the previous depth level (for determining edge length)
        current_depth - unweighted distance from start of search
        depth_limit - the depth level at which to stop (never changes)
        found - the set of all vertices already visited
        */
        void _dfs(const T& current_node, const unsigned distance_from_parent,
               const unsigned current_depth, const unsigned depth_limit, std::unordered_set<T>& found) const;
        
        
        //returns true if no Prim in list is still unknown
        static bool all_known(const std::unordered_map<T, Prim>& list);
        
        
        
        //table out all outgoing edges from node T
        //since undirected, both ends have outgoing edges toward each other
        std::unordered_map<T, std::vector<Edge>> graph;
        
        unsigned _total_cost=0;
        unsigned edge_count=0;
        
        //used to check if any changes have been made to the graph (which only allows adding edges)
        //since MST was last calculated
        mutable bool altered_since_last_calculations=true; //modified in minimum_spanning_tree()
};


#endif // UNDIRECTED_GRAPH_H
