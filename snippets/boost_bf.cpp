#include <boost/graph/bellman_ford_shortest_paths.hpp>
	
	// Declare graph
	Graph G = randomGraph(10);
	boost::print_graph(G);
	
	// Get property map from bundled property cost
	CostPropertyMap costsMap = boost::get(&EdgeProperties::cost, G);

	// Declare dist(intialized to long-max = inf) and pred vectors
	std::vector<long> distance (10, (std::numeric_limits <long>::max)());
	std::vector<Vertex> pred(10);
	
	// Source is vertex 0
	int s = 0;

	// Initialize preds to self(signifies null)
	for (int i = 0; i < 10; ++i) pred[i] = i;
	
	// Set start vertex distance=0
	distance[s] = 0;

	// Run algo
	bool r = bellman_ford_shortest_paths
	  (G, int(10), costsMap, &pred[0], &distance[0],
		boost::closed_plus<long>(), std::less<long>(), boost::default_bellman_visitor());

	// Print results
	if (r){
		std::pair<VertexIterator, VertexIterator> vi;
		for (vi = vertices(G); vi.first != vi.second; ++vi.first)
			std::cout << *vi.first << ": " << std::setw(3) << distance[*vi.first]
		  		<< " " << pred[*vi.first] << std::endl;
	}
	else
	  std::cout << "negative cycle" << std::endl;
