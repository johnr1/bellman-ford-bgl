# Bellman Ford Boost
The Bellman-Ford shortest path finding algorithm written in C++11 using BGL (Boost Graph Library).
The algorithm finds the shortest paths starting from a single vertex `s` to all other vertices in the graph, and inspired by the LEDA implementation, outputs valid results in the presence of negative cycles.

## Quick Summary
Executing the algorithm in a graph `G`, will yield for each vertex, the *distance* from the starter `s` and the *predecessor* vertex that was used to reach it.

The implementation outputs valid results in the presence of negative cycles by categorizing the vertices into one of three subsets.
* `V+` = Nodes that are not reachable from `s` inside `G` (`dist(v)=+inf`)

* `Vf` = Nodes reachable from `s` that do not belong or are not reachable from a negative cycle (`dist(v)=finite`)

* `V-` = Nodes that belong or are reachable from a negative cycle inside `G` (`dist(v)=-inf`)

Therefore the correct distance is extracted for vertices inside `Vf`, while vertices belonging to or reachable from a negative cycle (`V-`) are labeled as such. 


## Building
Make sure the [boost](https://www.boost.org/) library is installed and then run.

```bash
cd code
make
```

The make file places object files inside `code/build` and the final executable inside `code/bin`.

## Usage
The repo includes the algorithm as well as a some usage examples, performance capturing benchmarks, graph generators and graphviz visualization output.

### Usage in C++ code
```c++
#include "../include/bellman_ford.h"
#include "../include/graph.h"
#include "../include/graph_gen.h"
#include "../include/io.h"

void run_bf(Graph &G, Vertex s){
    // Declare dist(intialized to int-max -> inf) and pred vectors
    std::vector<long> dist (n);
    std::vector<Vertex> pred(n);

    // Get property map from bundled property cost
    CostPropertyMap costs = boost::get(&EdgeProperties::cost, G);

    // Start timer
    boost::timer timer;

    // Run algo
    bool no_neg_cycle = bellman_ford(G, s, costs, dist, pred);

    // Check results and categorize vertices
    // labels gets populated with each vetex susbet (V-, V+, Vf)
    std::vector<int> labels(n); 
    bool correct_results = bellman_ford_checker(G, s, costs, dist, pred, labels);

    // Print results
    std::cout << "S vertex is: " << s << std::endl;
    if (!no_neg_cycle) {
        std::cout << "Negative cycled detected." << std::endl;
    }

    // Visualize results
    std::ofstream f("graph.dot");
	boost::write_graphviz(f, G, boost::default_writer(), MyEdgeWriter(G, pred));
}   
```
Further examples inside `src/benchmark.cpp` and `src/run.cpp`


### Usage from CLI
```
$ ./bin/bellman_ford

No argument given
Usage:  ./bin/bellman_ford benchmark [-t type] [-n vertexes] [-i iterations]
or:     ./bin/bellman_ford run [-t type] [-n vertexes]

benchmark       Accurately times all algorithms for a graph and prints results.
run             Performs a run of the bellman ford algorithm, tests for integrity, prints results.
-t              The type of the graph ['random' | 'grid'] (default random) 
-n              Number of vertexes for random graph(default 200)
                Number of vertexes in one dimension of grid (Total: n*n) (default 200)
-i              Iterations to run the benchmark for
--help          Print this message.


$ ./bin/bellman_ford benchmark -t grid -n 100 -i 5

Running benchmark for 5 iteration(s)...
Graph Type: Grid | Nodes: 10000 | Edges: 19800
BOOST BF Time: 0.934235s (cycle detected)
MY BF Time: 0.438468s


$ ./bin/bellman_ford run -t random -n 6

Running my Bellman Ford algorithm
S vertex is: 1
Vertex: 0 | Dist: 6282 | Pred: 1 | Label: Vf
Vertex: 1 | Dist: 0 | Pred: nil | Label: Vf
Vertex: 2 | Dist: 3178 | Pred: 5 | Label: Vf
Vertex: 3 | Dist: 2659 | Pred: 5 | Label: Vf
Vertex: 4 | Dist: 682 | Pred: 1 | Label: Vf
Vertex: 5 | Dist: 717 | Pred: 1 | Label: Vf
Results OK!
Time to complete: 1.3e-05s
Wrote graphviz format in file graph.dot
