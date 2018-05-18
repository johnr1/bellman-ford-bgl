#include <iostream>
#include <LEDA/graph/graph.h>
#include <cstdlib>
#include <ctime>

#include "../include/graph.h"
#include "../include/benchmark.h"
#include "../include/run.h"

#include "../include/bellman_ford.h"

//
#include "../include/graph_gen.h"
#include <boost/graph/random.hpp>
#include <boost/graph/bellman_ford_shortest_paths.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/graph/graph_utility.hpp>
#include <cstdlib>
//

int main(int argc, char* argv[]) {
    srand (time(NULL));
    boost::mt19937 gen(time(NULL));

    Graph BG = myGridGraph(5);
    auto LG = boostToLeda(BG);
    auto Ls = LG.first_node();
    auto Bs = LG[Ls];


    run_my_bf(BG, Bs);
    run_boost_bf(BG,Bs);
    //run_leda_bf(LG, Ls);

    //benchmark();
    return 0;
}
