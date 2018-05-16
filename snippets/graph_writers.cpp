	Graph G = myGridGraph(10);
	//Graph G = randomGraph(10);
	boost::print_graph(G);

    myEdgeWriter mew(G);
	std::ofstream f("graph.txt");
	boost::write_graphviz(f, G, boost::default_writer(), mew);
	//boost::write_graphviz(f, G);
	f.close();
