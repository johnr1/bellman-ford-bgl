#include <iostream>
#include <ctime>
#include <LEDA/graph/graph.h>

#include "../include/graph.h"
#include "../include/graph_gen.h"
#include "../include/benchmark.h"
#include "../include/run.h"

int main(int argc, char* argv[]) {
    srand (static_cast<unsigned>(time(NULL))); // seed RNG

    Graph BG = randomGraph(50);
    auto LG = boostToLeda(BG);
    auto Ls = LG.choose_node();
    auto Bs = LG[Ls];

    run_my_bf(BG, Bs);
    run_boost_bf(BG,Bs);
    run_leda_bf(LG, Ls);

    //benchmark();
    return 0;
}
