# Container Loading Problem – Search-Based Solution

### AI Assignment 1 | Roll - MT24035 | IIIT Delhi

---

## 1. Overview

This project addresses the **Container Loading Optimization Problem** using search algorithms (**Breadth-First Search (BFS), Greedy Best-First Search, and A\***).
The goal is to determine the optimal placement of containers on a ship while **minimizing cost** and respecting **constraints** such as **balance, destination order, and weight distribution**.

The program reads an input configuration file, executes all three algorithms, and outputs detailed reports including **costs, violations, computation time, and final stack arrangements**.

---

## 2. Problem Formulation

The container loading problem is modeled as a **state-space search problem**.

### Ship Structure

* The ship has **4 stacks** (2 on **port/left side**, 2 on **starboard/right side**).
* Each stack has a **maximum height (H)**.
* A **balance limit** restricts the allowed weight difference between port and starboard sides.

### State Representation (5-tuple)

A state is defined as:

$$
s = \langle stacks, loaded\_mask, g, h, f \rangle
$$

* **stacks** → current arrangement of containers across stacks
* **loaded\_mask** → bitmask of which containers are placed
* **g** → cost accumulated so far
* **h** → heuristic estimate of remaining cost
* **f = g + h** → evaluation function (for A\*)

### Initial State

* All stacks empty, no container loaded.

### Actions

$$
a = Load(c_i, stack_j)
$$

Select an unloaded container $c_i$ and place it on stack $j$.

### Transition Model

Placing a container updates:

* The stack content
* The loaded mask
* The cost $g$

### Goal Test

* All containers are loaded
* **Hard constraints satisfied** (balance, max height, weight ordering)

---

## 3. Constraints

* **Destination Constraint** → Containers for earlier ports must not be blocked by later ones.
* **Balance Constraint** → Weight difference between port & starboard ≤ balance limit.
* **Weight Ordering Constraint** → Heavier containers cannot be above lighter ones in the same stack.

### Cost Model

* **Load cost** = 1 per container
* **Destination violation** = +2 penalty
* **Weight violation** = +1 penalty
* **Balance violation** = Forbidden (invalid state)

---

## 4. Input & Output

### Input Format (`input.txt`)

```
<num_stacks> <max_height> <balance_limit>
<num_containers>
<weight_0> <dest_0>
<weight_1> <dest_1>
...
```

**Example:**

```
4 3 15
6
5 1
7 2
4 1
6 3
8 2
3 1
```

### Output

The program prints results for each algorithm including:

* Solution found (Yes/No)
* Nodes expanded & time taken
* Total cost and violations
* Final container arrangement per stack
* Detailed violation report

---

## 5. How to Compile and Run

```bash
g++ -o main main.cpp
./main
```

* Place `input.txt` in the same directory.
* Results are displayed in **console** and also saved to **output.txt**.

---

## 6. Algorithms Implemented

1. **BFS (Breadth-First Search)**

   * Explores all states level by level.
   * Guarantees completeness but exponential in time & space.

2. **Greedy Best-First Search**

   * Uses heuristic = `5 × (dest-blocks) + 2 × (weight violations) + (remaining containers)`
   * Fast, but may miss optimal solution if heuristic misleads.

3. **A\* Search**

   * Uses $f = g + h$, where `g` = cost so far, `h` = heuristic estimate.
   * Guarantees optimal solution if heuristic is admissible.

---

## 7. Results & Analysis

### Comparison Table

| Algorithm  | Solution Found | Cost | Violations | Nodes Expanded | Why this result?                                                     |
| ---------- | -------------- | ---- | ---------- | -------------- | -------------------------------------------------------------------- |
| **BFS**    | Yes            | 14   | 1          | 8986           | Explores all states, found feasible but not optimal solution.        |
| **Greedy** | Yes            | 12   | 0          | 45             | Heuristic guided directly to a violation-free arrangement.           |
| **A\***    | Yes            | 12   | 0          | 7330           | Optimal solution found; more nodes than Greedy but provably correct. |

### Insights

* **BFS** → Exhaustive, impractical for larger inputs.
* **Greedy** → Very efficient, can find perfect solutions when heuristic aligns well.
* **A\*** → More costly than Greedy but guarantees **optimality**.

---

## 8. Conclusion

The performance of the algorithms on the container loading problem demonstrates the trade-offs between **completeness, efficiency, and optimality**:

* **BFS** → Complete but computationally expensive. Useful only for very small cases or correctness validation.
* **Greedy Best-First** → Fast and effective when guided by a strong heuristic. However, lacks any guarantee of optimality.
* **A\*** → Balances efficiency with theoretical guarantees. It may explore more nodes than Greedy, but ensures the **best possible solution** is found.

Thus, for practical container loading optimization, **A\*** is the most reliable choice, while **Greedy** is suitable when speed is prioritized and near-optimal solutions are acceptable.

