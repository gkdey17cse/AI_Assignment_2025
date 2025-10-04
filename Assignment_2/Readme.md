# Kabaddi Game AI Simulation

## Overview

This project is an **Artificial Intelligence driven Kabaddi game simulation** built on a grid-based environment. The objective is to compare how different AI agents with unique decision-making strategies perform under the same game rules and conditions.

The game follows simplified Kabaddi mechanics, where two teams (A & B) compete to steal the opponent’s treasure and return it to their own half without being captured.

Implemented Agents:

- **Random Agent** – baseline, non-intelligent.
- **Greedy Agent** – moves towards treasure using heuristics.
- **Alpha-Beta Agent** – uses Minimax with Alpha–Beta pruning.
- **MCTS Agent** – uses Monte Carlo Tree Search simulations.

---

## Rules & Game Setup

- The game is played on a 2D grid (default size: **5×6**).
- Each team has **2 players** and **1 treasure** in its own half.
- Moves available: `Stay`, `Up`, `Down`, `Left`, `Right`.
- A capture occurs when two opponents occupy the same cell in enemy territory.
- A win occurs when a player successfully steals the opponent’s treasure and returns it to their home side.
- Draw conditions:

  - Both teams win simultaneously.
  - Game exceeds max steps (default: 200).

Modes supported:

1. **Turn-based** – Team A moves first, then Team B.
2. **Simultaneous** – Both teams move together.

---

## File Information

- **code.cpp** → Contains the complete code for environment, rules, agents, and simulation.
- **README.md** → (this file) instructions for compilation and usage.
- **Results.md** → Results of the simulation of different Game & Tournament.
- **Documentation.pdf** → Detailed documentation of the work.

---

## Compilation & Execution

### 1. Compile the program

```bash
g++ code.cpp -o kabaddi
```

### 2. Run the executable

```bash
./kabaddi
```

### 3. Example Run

```bash
Do you want default setup? (y/n): y
Using default setup (5x6).

Choose mode: 1 = Single Game, 2 = Tournament: 1
Choose Agent for Team A (1=Random, 2=Greedy, 3=AlphaBeta, 4=MCTS): 1
Choose Agent for Team B (1=Random, 2=Greedy, 3=AlphaBeta, 4=MCTS): 2
Choose gameplay type: 1=Turn-based, 2=Simultaneous: 1
```

---

## Example Outputs

### Single Game (Random vs Greedy – Turn-based)

```
Winner: Team A
Steps: 49
Captures (A:2, B:0)
```

### Tournament Mode (100 Games, Turn-based)

```
Random (A) vs Greedy (B) --> A_wins=99, B_wins=0, Draws=1
AlphaBeta (A) vs MCTS (B) --> A_wins=50, B_wins=47, Draws=3
```

---

## Results Summary

- **Alpha-Beta Agent**: Strongest overall, consistent in both modes.
- **MCTS Agent**: Performs closely to Alpha-Beta but slightly less consistent.
- **Random Agent**: Unpredictable, occasionally outperforms deterministic agents.
- **Greedy Agent**: Weakest, too rigid, loses to all other strategies.

---

## Links

- [GitHub Repository](https://github.com/gkdey17cse/AI_Assignment_2025/tree/main/Assignment_2)
- [Submission Drive Link](https://drive.google.com/drive/u/0/folders/1BcZOZ_CILh2-h756Sk1J3HYpdW4VmWoN)

---

## Author

- **Gour Krishna Dey**
- Roll No: **MT24035** | IIIT Delhi
