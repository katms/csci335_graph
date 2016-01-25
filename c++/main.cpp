//Katherine Sullivan
//CSCI 335 Graph Assignment

//used std::priority_queue
//it was either that or deal with the hash table in BinaryHeap


#include <iostream>
#include <fstream> //std::ifstream
#include <vector> //std::vector
#include "Graph.h" 
#include "Graph.cpp"

unsigned levenshtein_distance(const std::string& one, const std::string& two);

int main(int argc, char* argv[])
{
    if(argc!=2)
    {
        std::cerr<<"Usage: findNames <filename>"<<std::endl;
        return 1;
    }
    
    std::ifstream names(argv[1]);
    
    if(names.fail())
    {
        std::cerr<<"Could not open "<<argv[1]<<std::endl;
        return 1;
    }
    
    std::cout<<"Building graph...\n\n";
    Undirected_Graph<std::string> graph;
    
    //this method was at least slightly faster than going back through the file at every name
    std::vector<std::string> prev_names; 
    prev_names.reserve(1000);
    
    //compare each name to every other
    while(!names.eof())
    {
        std::string newest_name;
        names>>newest_name;
        
        for(const std::string& name : prev_names)
        {
            unsigned distance = levenshtein_distance(name, newest_name);
            if(distance<=4)
            {
                graph.connect(name, newest_name, distance);
            }
        }
        prev_names.push_back(newest_name);
    }
    
    std::cout<<"Vertices: "<<graph.count_nodes()<<std::endl;
    std::cout<<"Edges: "<<graph.count_edges()<<"\n\n\n";
    
    //depth first search loop
    std::string input_name;
    unsigned depth_limit;
    do
    {
        std::cout<<"Enter a name and depth limit (Type \"exit\" or Ctrl + C to stop):\n>>> ";
        std::cin>>input_name;
        
        if(input_name=="exit")
        {
            break;
        }
        
        std::cin>>depth_limit; //no error checking for this one

        std::cout<<"Names similar to "<<input_name<<":\n\n";
        graph.depth_first_search(input_name, depth_limit);

    } while(input_name!="exit");

    return 0;
}

//http://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance#C.2B.2B
unsigned levenshtein_distance(const std::string& s1, const std::string& s2)
{
    const size_t len1 = s1.size(), len2 = s2.size();
	std::vector<unsigned int> col(len2+1), prevCol(len2+1);
 
	for (unsigned int i = 0; i < prevCol.size(); i++)
		prevCol[i] = i;
	for (unsigned int i = 0; i < len1; i++) {
		col[0] = i+1;
		for (unsigned int j = 0; j < len2; j++)
			col[j+1] = std::min( std::min(prevCol[1 + j] + 1, col[j] + 1),
								prevCol[j] + (s1[i]==s2[j] ? 0 : 1) );
		col.swap(prevCol);
	}
	return prevCol[len2];
}
