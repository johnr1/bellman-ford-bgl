    // Print results
    VertexIterator vi, vi_end;
    std::cout << "S: " << s << std::endl;
    for(boost::tie(vi, vi_end) = vertices(G); vi != vi_end; ++vi){
        std::cout << "Vertex " << *vi
        << " | Dist: "<< (dist[*vi] == std::numeric_limits<int>::max() ? std::string("INF") : std::to_string(dist[*vi]))
        << " | Pred: " << pred[*vi]
        << " | Label: " << labelName(labels[*vi]) << std::endl;
    }


