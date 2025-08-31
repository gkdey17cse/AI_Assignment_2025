# Container Loading Problem Solver

This project implements various search algorithms to solve the Container Loading Problem with destination and balance constraints.

## Problem Description

The goal is to load containers onto a ship with the following constraints:
1. **Destination constraint**: Containers for earlier ports should not be blocked by containers for later ports
2. **Balance constraint**: The weight difference between port and starboard sides must be within a specified limit
3. **Weight distribution**: Heavier containers should be placed at the bottom of stacks

## Input Format

Create an `input.txt` file with the following format:
<num_bays> <max_weight_diff> <max_height>
<weight1> <destination1>
<weight2> <destination2>

```bash
ContainerLoadingProblem/
│── README.md
│── Makefile
│── input.txt
│
├── include/
│   ├── state.h
│   ├── search.h
│
├── src/
│   ├── main.cpp
│   ├── state.cpp
│   ├── search/
│       ├── bfs.cpp
│       ├── dfs.cpp
│       ├── iddfs.cpp
│       ├── greedy.cpp
│       ├── astar.cpp
│
├── obj/
│   ├── src/
│   │   ├── main.o
│   │   ├── state.o
│   │   ├── search/
│   │       ├── bfs.o
│   │       ├── dfs.o
│   │       ├── iddfs.o
│   │       ├── greedy.o
│   │       ├── astar.o
│
└── results/
    ├── solution_bfs.txt
    ├── solution_dfs.txt
    ├── solution_iddfs.txt
    ├── solution_greedy.txt
    ├── solution_astar.txt
```

Our Approach to Container Loading Problem
Problem Understanding:
We need to load containers onto a ship with two sides (port/starboard), multiple bays, and height constraints while respecting:

Destination constraints: Earlier destination containers should not be blocked

Balance constraints: Weight difference between sides must be within limits

Weight distribution: Heavier containers should be at the bottom

Solution Strategy:

State Representation: We model the ship as a 3D grid [side][bay][tier] tracking container positions

Search Algorithms: Implement BFS, DFS, IDDFS, Greedy, and A* to explore possible loading sequences

Cost Model:

Loading cost: 1 unit per container

Penalty cost: 2 units per constraint violation

Heuristics: For informed search, we use:

Number of unloaded containers

Constraint violation counts

Bay utilization balance

Key Features:

Input Flexibility: Handles variable bays, height limits, and weight constraints

Constraint Enforcement: Validates solutions against all problem constraints

Progress Monitoring: Shows search progress and timeout handling

Solution Analysis: Provides detailed cost breakdown and constraint violations

Algorithm Implementation:

BFS: Explores all states level by level, guaranteed to find optimal solution

State Pruning: Uses visited state tracking to avoid duplicates

Memory Management: Efficient state representation and exploration

The algorithm systematically explores different loading sequences, evaluating each state against the constraints and selecting the most optimal loading configuration that minimizes both loading time and constraint violations.

## Building and Running

```bash
make        # Build the project
make run    # Run with default input
make clean  # Clean build files
```
Output
The program will generate solution files in the results/ directory showing:

Final container configuration

Cost breakdown (loading cost + penalty cost)

Constraint violations

Weight distribution between sides

File Structure
include/: Header files

src/: Source code files

src/search/: Search algorithm implementations

obj/: Object files (generated during build)

results/: Solution output files