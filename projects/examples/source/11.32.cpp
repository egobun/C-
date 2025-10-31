/////////////////////////////////////////////////////////////////////////////////////

// support : www.cs.usfca.edu/~galles/visualization/Dijkstra.html

/////////////////////////////////////////////////////////////////////////////////////

#include <array>
#include <cassert>
#include <iterator>

/////////////////////////////////////////////////////////////////////////////////////

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/named_function_params.hpp>

/////////////////////////////////////////////////////////////////////////////////////

int main()
{
    using graph_t = boost::adjacency_list 
    < 
        boost::vecS, boost::vecS, boost::directedS, 
        
        boost::no_property, boost::property < boost::edge_weight_t, int >
    > ;

//  ---------------------------------------------------------------------------------

    graph_t graph;

//  ---------------------------------------------------------------------------------

    boost::add_edge(0, 2, 1, graph);

    boost::add_edge(1, 1, 2, graph);

    boost::add_edge(1, 3, 3, graph);

    boost::add_edge(2, 1, 4, graph);

    boost::add_edge(2, 3, 5, graph);

    boost::add_edge(3, 1, 6, graph);

    boost::add_edge(3, 4, 7, graph);

    boost::add_edge(4, 0, 8, graph);

    boost::add_edge(4, 1, 9, graph);

//  ---------------------------------------------------------------------------------

	std::array < int, 5 > array = {};

//  ---------------------------------------------------------------------------------

	boost::dijkstra_shortest_paths(graph, 0, boost::distance_map(std::begin(array)));

//  ---------------------------------------------------------------------------------

	assert((array == std::array < int, 5 > ({ 0, 5, 1, 6, 13 })));
}

/////////////////////////////////////////////////////////////////////////////////////