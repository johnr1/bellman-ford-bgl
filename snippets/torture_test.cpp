void torture_test(unsigned times){
    std::cout << "Running torture test, for testing algorithm results" << std::endl;
    for(int tests=0; tests<times; ++tests){
        unsigned n = rand() % 2000 + 10;
        Graph BG = randomGraph(n);

        auto LG = boostToLeda(BG);
        leda::node ls = LG.choose_node();
        Vertex bs = LG[ls];

        std::vector<long> bdist (n);
        std::vector<Vertex> bpred(n);
        CostPropertyMap bcosts = boost::get(&EdgeProperties::cost, BG);

        leda::node_array<leda::edge> lpred(LG);
        leda::node_array<long> ldist(LG);
        leda::edge_array<long> lcosts = LG.edge_data();

        bool no_neg_cycle;
        bellman_ford(BG, bs, bcosts, bdist, bpred);
        std::vector<VertexLabel> blabels = labelVertices(BG, no_neg_cycle, bdist, bpred);
        bool results = bellman_ford_checker(BG, bs, bcosts, bdist, bpred);
        if(!results){
            std::cout << "Checker assertion failed" << std::endl;
            return;
        }

        BELLMAN_FORD_B_T(LG, ls,lcosts,ldist,lpred);
        leda::node_array<VertexLabel> llabels = ledaLabelVertices(LG, no_neg_cycle, ls, lpred);

        leda::node v;
        forall_nodes(v, LG){
            if(llabels[v] != blabels[LG[v]]){
                std::cout << "label assertion failed" << std::endl;
                return;
            }
            if(ldist[v] != bdist[LG[v]]){
                std::cout << "Dist assertion failed" << std::endl;
                return;
            }
            if(lpred[v] == nil){
                if(bpred[LG[v]] != LG[v]){
                    std::cout << "pred assertion failed" << LG[lpred[v]] << " != " << bpred[LG[v]] << std::endl;
                    return;
                }
            }else{
                if(LG[LG.source(lpred[v])] != bpred[LG[v]]){
                    std::cout << "pred assertion failed" << LG[lpred[v]] << " != " << bpred[LG[v]] << std::endl;
                    return;
                }
            }
        }
        std::cout << "TEST: " << tests << " OK" << std::endl;

    }
}
