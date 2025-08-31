#include <iostream>
#include <fstream>
#include <vector>
#include "search/bfs.h"
#include "search/container.h"

State read_input(const std::string& filename) {
    State s;
    std::ifstream fin(filename);
    if (!fin) {
        std::cerr << "Cannot open input file!\n";
        exit(1);
    }

    int num_containers;
    fin >> s.side >> num_containers;

    s.containers.resize(num_containers);
    for (int i = 0; i < num_containers; i++) {
        fin >> s.containers[i]; // works because operator>> is overloaded
    }

    fin.close();
    return s;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }

    State initial = read_input(argv[1]);
    BFS bfs;
    bfs.search(initial);

    return 0;
}
