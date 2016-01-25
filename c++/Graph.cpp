//Katherine Sullivan
//CSCI 335 Graph Assignment


#include "Graph.h"
#include <iostream> //std::cout, std::cerr
#include <queue> //std::priority_queue
#include <functional> //std::greater


//any uses of graph.at(v) instead of graph[v] are because doing this fixed compiler errors for some reason

template <class T>
Undirected_Graph<T>::Undirected_Graph()
{}
    
template <class T>
Undirected_Graph<T>::Undirected_Graph(const T& node)
{
    graph[node];
}

//access graph statistics:

template <class T>
unsigned Undirected_Graph<T>::total_weight() const
{
    return _total_cost;
}
    
template <class T>
unsigned Undirected_Graph<T>::count_nodes() const
{
    return graph.size();
}

template <class T>
unsigned Undirected_Graph<T>::count_edges() const
{
    return edge_count;
}

template <class T>
bool Undirected_Graph<T>::contains(const T& node) const
{
    return graph.find(node)!=graph.end();
}

//adds an edge between one and two with the given weight
template <class T>
void Undirected_Graph<T>::connect(const T& one, const T& two, unsigned weight) //if one or two is not in map it gets added
{
    //MST won't work if the graph is not connected but connect() will allow floating edges because of how I have to build the graph
    
    //prevent nodes connecting to themselves
    if(one==two)
    {
        return;
    }
    
    //check edge doesn't already exist
    //if graph[one] is being created with this loop, then it was about to be added anyway
    for(const Edge& e : graph[one])
    {
        if(e.node2==two)
        {
            return;
        }
    }
    
    //else:
    
    //add edge to both keys
    graph[one].push_back(Edge(one, two, weight));
    graph[two].push_back(Edge(two, one, weight));
    
    
    _total_cost+=weight;
    ++edge_count;
    
    altered_since_last_calculations=true;
}


//computes MST starting from first
template <class T>
Undirected_Graph<T> Undirected_Graph<T>::minimum_spanning_tree(const T& first) const
{
    altered_since_last_calculations=false;
    
    if(graph.empty() || !contains(first))
    {
        return Undirected_Graph<T>{};
    }
    
    else if(count_edges() < count_nodes()) //edge_count == nodes-1, this is already an MST and there is only one solution
    {
        return *this;
    }
    
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> edges; //min heap
    
    std::unordered_map<T, Prim> vertices;
    
    for(const auto& v : graph)
    {
        vertices.insert(std::pair<T, Prim>(v.first, Prim{}));
    }
    
    //check first and queue its edges
    vertices[first].dv=0;
    vertices[first].known=true;
    vertices[first].pv=first;
    
    for(const Edge& e : graph.at(first))
    {
        vertices[e.node2].dv=e.weight;
        vertices[e.node2].pv=first;
        edges.push(e);
    }
    
    //check every vertex
    while(!all_known(vertices))
    {
        if(edges.empty())
        {
            std::cerr<<"Unconnected graph, cannot complete MST\n";
            break; //build and return incomplete min_tree with nodes already found
        }
        
        const Edge min=edges.top(); 
        edges.pop();
        
        //min.node1 was marked known when this edge was queued, so only check min.node2
        
        if(!vertices[min.node2].known) //ignore and discard edge if node2 is already known
        {
            //expand min.node2
            
            for(const Edge& edge : graph.at(min.node2))
            {
                edges.push(edge);
            }
            
            Prim& info=vertices[min.node2];
            if(min.weight<info.dv)
            {
                info.dv=min.weight;
                info.pv=min.node1;
            }
            vertices[min.node2].known=true;
        }//if !min.node2.known
    }//while !all_known
    
    
    //construct minimum spanning tree
    Undirected_Graph<T> min_tree(first);
    
    for(const auto& v : vertices)
    {
        //vertices[first] is mostly a placeholder, since first.pv is itself the edge won't be added
        const Prim& node=v.second;
        min_tree.connect(v.first, node.pv, node.dv);
    }
    return min_tree;
}


//Depth first search w/ depth limit on MST(start)
template <class T>
void Undirected_Graph<T>::depth_first_search(const T& start, const unsigned depth_limit) const
{
    //dynamic programming
    static std::unordered_map<T, Undirected_Graph<T>> mst;
    
    if(!contains(start))
    {
        std::cout<<start<<" is not in graph.\n";
        return;
    }
    
    
    auto min_tree=mst.find(start);
    
    if(min_tree==mst.end())
    {
        //create MST
        mst.insert(std::pair<T, Undirected_Graph<T>>(start, std::move(minimum_spanning_tree(start))));
    }
    
    //if MST exists, make sure the graph hasn't changed since it was created
    //yes, I know that isn't a scenario that would come up
    else if(altered_since_last_calculations)
    {
        mst[start]=std::move(minimum_spanning_tree(start));
    }
    
    std::unordered_set<T> found;
    mst[start]._dfs(start, 0, 0, depth_limit, found);
}

template<class T>
void Undirected_Graph<T>::_dfs(const T& current_node, const unsigned distance_from_parent, const unsigned current_depth, const unsigned depth_limit, std::unordered_set<T>& found) const
{
    //at a new node, print and add it to found
    found.insert(current_node);
    for(unsigned tab=0; tab<current_depth; ++tab) //align output to current_depth
    {
        std::cout<<'\t';
    }
    std::cout<<current_node<<" ("<<distance_from_parent<<")\n";
    
    const auto& pair = graph.find(current_node);
    
    if(pair==graph.end()) //error checking
    {
        std::cout<<current_node<<" is not in graph\n";
        return;
    }
    
    else if(current_depth<depth_limit)
    {
        for(const Edge& edge : pair->second)
        {
            if(found.find(edge.node2)==found.end()) //only unsearched nodes
            {
                _dfs(edge.node2, edge.weight, current_depth+1, depth_limit, found);
            }//if not found
        }//for each edge
    } //else if limit not reached
    
    //else current_depth==depth_limit, stop
}

//checks if every element in list is known
template<class T>
bool Undirected_Graph<T>::all_known(const std::unordered_map<T, Prim>& list)
{
    for(const auto& el : list)
    {
        if(!el.second.known)
        {
            return false;
        }
    }
    return true;
}


/*******************
        EDGE
*******************/

template <class T>
Undirected_Graph<T>::Edge :: Edge(const T& origin, const T& dest, unsigned cost):
    node1(origin), node2(dest), weight(cost)
{} //graph handles cases of node1==node2

//for std::prioriy_queue in minimum_spanning_tree
template<class T>
bool Undirected_Graph<T>::Edge :: operator>(const Edge& other) const
{
    return weight>other.weight;
}

//direction doesn't matter
template<class T>
bool Undirected_Graph<T>::Edge :: operator==(const Edge& other) const
{
    if(node1==other.node1) return node2==other.node2;
    else if(node1==other.node2) return node2==other.node1;
    else return false;
}

template <class T>
bool Undirected_Graph<T>::Edge :: operator!=(const Edge& other) const
{
    return !(*this==other);
}
