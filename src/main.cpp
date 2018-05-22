#include <iostream>
#include <LEDA/graph/graph.h>
#include <boost/graph/random.hpp>
#include <boost/random/mersenne_twister.hpp>

#include "../include/graph.h"
#include "../include/graph_gen.h"
#include "../include/benchmark.h"
#include "../include/run.h"

#include "../include/bellman_ford.h"

enum class Command {benchmark, run};

Command command;
unsigned N=200;
unsigned iterations=3;
GraphType graph_type = GraphType::random;

void printUsage(std::string programName) {
    std::cout << "Usage:  "<< programName << " benchmark [-t type] [-n vertexes] [-i iterations]\n"
              << "or:\t" << programName << " run [-t type] [-n vertexes]\n\n"
              << "benchmark\tAccurately times all algorithms for a graph and prints results.\n"
              << "run\t\tPerforms a run of the bellman ford algorithm, tests for integrity, prints results.\n"
              << "-t\t\tThe type of the graph ['random' | 'grid'] (default random) \n"
              << "-n\t\tNumber of vertexes for random graph(default 200)\n"
              << "\t\tNumber of vertexes in one dimension of grid (Total: n*n) (default 200)\n"
              << "-i\t\tIterations to run the benchmark for\n"  
              << "--help\t\tPrint this message.\n";
}

void parseArguments(int argc, char *argv[]) {
    command = Command::run;
    if(argc < 2){
        //std::cout << "No argument given. Running default action. Pass '--help' for more actions." << std::endl;
        std::cout << "No argument given" << std::endl;
        printUsage(argv[0]);
        exit(-1);
    }

    int i = 1;
    while(i < argc) {
        std::string arg(argv[i]);

        if(arg == "benchmark") {
            command = Command::benchmark;
        }
        else if(arg == "run") {
            command = Command::run;
        }
        else if(arg == "-n" && i+1 < argc) {
            int tmp = atoi(argv[++i]);
            N = tmp > 0 ? tmp : N;
        }
        else if(arg == "-t" && i+1 < argc){
            std::string gt(argv[++i]);
            if(gt == "random") graph_type = GraphType::random;
            else if(gt == "grid")graph_type = GraphType::grid;
        }
        else if(arg == "-i" && i+1 < argc){
            int tmp = atoi(argv[++i]);
            iterations = tmp > 0 ? tmp : iterations;
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
        benchmark(N, graph_type, iterations);
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

        run_my_bf(G, s);
    }

    return 0;
}
