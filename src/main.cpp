#include <iostream>
#include <ctime>
#include <LEDA/graph/graph.h>
#include <boost/graph/random.hpp>
#include <boost/random/mersenne_twister.hpp>

#include "../include/graph.h"
#include "../include/graph_gen.h"
#include "../include/benchmark.h"
#include "../include/run.h"

enum class Command {benchmark, run};
enum class GraphType {random, grid};

Command command;
unsigned N=200;
GraphType graph_type = GraphType::random;

void printUsage(std::string programName) {
    std::cout << "Usage:  "<< programName << " benchmark\n"
              << "or:\t" << programName << " run [-t type] [-n vertexes]\n\n"
              << "benchmark\tAccurately times all algorithms for all test graphs and prints results.\n"
              << "run\t\tPerforms a run of the bellman ford algorithm, tests for integrity, prints results.\n"
              << "-t\t\tThe type of the graph ['random' | 'grid'] (default random) \n"
              << "-n\t\tNumber of vertexes for random graph(default 200)\n"
              << "\t\tNumber of vertexes in one dimension of grid (Total: n*n) (default 200)\n"
              << "--help\t\tPrint this message.\n";
}

void parseArguments(int argc, char *argv[]) {
    command = Command::run;
    if(argc < 2){
        std::cout << "No argument given. Running default action. Pass '--help' for more actions." << std::endl;
        return;
    }

    int i = 1;
    while(i < argc) {
        std::string arg(argv[i]);

        if(arg == "benchmark") {
            command = Command::benchmark;
            return;
        }

        else if(arg == "run") {
            command = Command::run;
        }
        else if(arg == "-n" && i+1 < argc) {
            int tmp = atoi(argv[++i]);
            N = tmp != 0 ? tmp : 300;
        }
        else if(arg == "-t" && i+1 < argc){
            std::string gt(argv[++i]);
            if(gt == "random") graph_type = GraphType::random;
            else if(gt == "grid")graph_type = GraphType::grid;
        }

        else{
            printUsage(argv[0]);
            exit(2);
        }
        ++i;
    }
}

int main(int argc, char* argv[]) {
    parseArguments(argc, argv);
    srand (time(NULL)); // seed RNG
    boost::mt19937 gen(time(NULL));

    if(command == Command::benchmark){
        benchmark();
    }
    else if(command == Command::run){
        Graph G;
        Vertex s;
        if(graph_type == GraphType::random) {
            G = randomGraph(N);
            s = boost::random_vertex(G, gen);
        }
        else {
            G = myGridGraph(N);
            s = 0;
        }
        //auto LG = boostToLeda(G);

        //run_leda_bf(LG, LG.first_node());
        run_my_bf(G, s);
    }

    return 0;
}