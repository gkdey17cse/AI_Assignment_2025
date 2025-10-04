# Results from 1.cpp

## 1. Turn Based
Do you want default setup? (y/n): y
Using default setup (5x6 board).

- Choose mode: 1 = Single Game, 2 = Tournament: 2
- Choose gameplay type for tournament: 1=Turn-based, 2=Simultaneous: 1
- Enter number of games per pairing: 100
- Show concise per-game lines? (y/n): n
```bash
===== Tournament: 100 games per ordered pair =====
Random (A) vs Greedy (B) --> A_wins=99, B_wins=0, Draws=1, avgStepsA=75.60
Random (A) vs AlphaBeta (B) --> A_wins=42, B_wins=51, Draws=7, avgStepsA=88.48, avgStepsB=81.92
Random (A) vs MCTS (B) --> A_wins=44, B_wins=49, Draws=7, avgStepsA=85.45, avgStepsB=97.61
Greedy (A) vs Random (B) --> A_wins=0, B_wins=98, Draws=2, avgStepsB=68.78
Greedy (A) vs AlphaBeta (B) --> A_wins=0, B_wins=100, Draws=0, avgStepsB=72.45
Greedy (A) vs MCTS (B) --> A_wins=0, B_wins=99, Draws=1, avgStepsB=68.19
AlphaBeta (A) vs Random (B) --> A_wins=47, B_wins=37, Draws=16, avgStepsA=91.57, avgStepsB=94.03
AlphaBeta (A) vs Greedy (B) --> A_wins=100, B_wins=0, Draws=0, avgStepsA=73.08
AlphaBeta (A) vs MCTS (B) --> A_wins=50, B_wins=47, Draws=3, avgStepsA=94.58, avgStepsB=90.30
MCTS (A) vs Random (B) --> A_wins=44, B_wins=47, Draws=9, avgStepsA=90.30, avgStepsB=79.49
MCTS (A) vs Greedy (B) --> A_wins=99, B_wins=0, Draws=1, avgStepsA=77.87
MCTS (A) vs AlphaBeta (B) --> A_wins=51, B_wins=41, Draws=8, avgStepsA=87.94, avgStepsB=90.44
```

## 2. Simulation Based


Do you want default setup? (y/n): y
Using default setup (5x6 board).

- Choose mode: 1 = Single Game, 2 = Tournament: 2
- Choose gameplay type for tournament: 1=Turn-based, 2=Simultaneous: 2
- Enter number of games per pairing: 100
- Show concise per-game lines? (y/n): n

```bash
===== Tournament: 100 games per ordered pair =====
Random (A) vs Greedy (B) --> A_wins=99, B_wins=0, Draws=1, avgStepsA=73.16
Random (A) vs AlphaBeta (B) --> A_wins=48, B_wins=42, Draws=10, avgStepsA=84.12, avgStepsB=77.31
Random (A) vs MCTS (B) --> A_wins=43, B_wins=51, Draws=6, avgStepsA=89.35, avgStepsB=71.59
Greedy (A) vs Random (B) --> A_wins=0, B_wins=97, Draws=3, avgStepsB=74.16
Greedy (A) vs AlphaBeta (B) --> A_wins=0, B_wins=98, Draws=2, avgStepsB=62.83
Greedy (A) vs MCTS (B) --> A_wins=0, B_wins=100, Draws=0, avgStepsB=71.38
AlphaBeta (A) vs Random (B) --> A_wins=45, B_wins=46, Draws=9, avgStepsA=68.51, avgStepsB=75.50
AlphaBeta (A) vs Greedy (B) --> A_wins=96, B_wins=0, Draws=4, avgStepsA=71.82
AlphaBeta (A) vs MCTS (B) --> A_wins=59, B_wins=34, Draws=7, avgStepsA=73.15, avgStepsB=73.65
MCTS (A) vs Random (B) --> A_wins=41, B_wins=51, Draws=8, avgStepsA=80.85, avgStepsB=78.22
MCTS (A) vs Greedy (B) --> A_wins=99, B_wins=0, Draws=1, avgStepsA=65.80
MCTS (A) vs AlphaBeta (B) --> A_wins=56, B_wins=38, Draws=6, avgStepsA=76.05, avgStepsB=78.08
```