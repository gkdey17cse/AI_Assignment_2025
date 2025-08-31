## Homework Assignment 1: Container Loading Problem using AI Search

### 👩‍🏫 Problem Description

We are tasked with solving the **container loading problem** for a ship. Containers must be loaded from the yard onto the ship under two main constraints:

1. **Destination Constraint**:

   * Containers destined for earlier ports must not be blocked by containers for later ports.
   * Modeled by destination rank (integer). Smaller rank = earlier port.
   * Valid stacks = non-increasing destination order from bottom → top.

2. **Balance Constraint**:

   * The ship must not become too imbalanced during loading.
   * The difference in total weight between **Port** and **Starboard** sides must not exceed a given balance factor.
   * Balance is checked after each placement.

**Goal**: Find a loading plan that respects these constraints and **minimizes cost**, where cost includes:

* Base load/unload cost (per container).
* Penalty for unloading conflicts (blocking).
* Penalty for reshuffling (if required).

---

### 🛠️ Tasks

#### **1. Problem Modeling**

* **State** = current ship configuration (stack contents), remaining containers, current weight difference.
* **Actions** = place one container into a valid stack (Port/Starboard, any bay).
* **Constraints** =

  * Destination order rule.
  * Balance limit rule.
* **Objective Function**:

  $$
  \text{Cost} = \alpha \cdot \text{LoadingCost} + \beta \cdot \text{UnloadingPenalty} + \gamma \cdot \text{ReshufflePenalty}
  $$

---

#### **2. Input Format**

Configuration will be given in `input.txt`.

**Example:**

```
sides = 2
bays = 2
height = 3
balanceLimit = 20
loadCost = 1
unloadCost = 1
reshufflePenalty = 5
containers = (C1,10,1) (C2,20,2) (C3,15,1) (C4,25,3)
```

* `(ID, Weight, DestinationRank)` per container.

---

#### **3. Output**

For each search algorithm, output will include:

* Sequence of placements (which container → which side & bay).
* Final configuration of ship (stacks per bay).
* Total cost of the plan.

---

#### **4. Search Algorithms**

We will implement and test:

* **DFS** (Depth First Search)
* **BFS** (Breadth First Search)
* **IDDFS** (Iterative Deepening DFS)
* **Greedy Best-First Search** (heuristic = minimize blocking + imbalance)
* **A\*** (optimal under admissible heuristic)

---

#### **5. Plan of Execution**

1. **Parse input** from `input.txt`.
2. **Initialize state** with empty ship & all containers in yard.
3. **Expand states** using valid placements.
4. **Run chosen search algorithm** until all containers placed.
5. **Compute final cost** (load/unload + penalties).
6. **Output solution plan** to `results/`.

---

### 📂 Directory Structure

```
ContainerLoadingProblem/
│── README.md
│── Makefile
│── input.txt
│
├── include/
│   ├── state.h
│   ├── search.h
│   ├── heuristic.h
│
├── src/
│   ├── main.cpp
│   ├── state.cpp
│   ├── heuristic.cpp
│   ├── search/
│       ├── bfs.cpp
│       ├── dfs.cpp
│       ├── iddfs.cpp
│       ├── greedy.cpp
│       ├── astar.cpp
│
├── results/
│   ├── solution_bfs.txt
│   ├── solution_dfs.txt
│   ├── solution_astar.txt
```

---

### 📊 Evaluation

* Compare different search algorithms on the same `input.txt`.
* Metrics:

  * **Validity** (constraints satisfied).
  * **Total cost**.
  * **Runtime** (optional).

---

✅ This README + directory structure is clean, modular, and aligned with the assignment.

