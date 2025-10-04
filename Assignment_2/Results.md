- Results from code.cpp

# Tournament Results

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

# Single Game outcome

```bash
PS E:\MTechCSE\Study\Sem3\AI\Assignment\Assignment_2> ./a
Do you want default setup? (y/n): y
Using default setup (5x6).

Choose mode: 1 = Single Game, 2 = Tournament: 1
Choose Agent for Team A (1=Random,2=Greedy,3=AlphaBeta,4=MCTS): 1
Choose Agent for Team B (1=Random,2=Greedy,3=AlphaBeta,4=MCTS): 2
Choose gameplay type: 1=Turn-based,2=Simultaneous: 1
Game Start: Team A(Random) vs Team B(Greedy)
A . . | . . .
A . . | . . .
. T . | . t .
. . . | . . B
. . . | . . B
----------------------
Step 1:
Team A moves: Up Stay
Team B moves: Left Left
A . . | . . .
A . . | . . .
. T . | . t .
. . . | . B .
. . . | . B .
----------------------
Step 2:
Team A moves: Down Down
Team B moves: Left Left
. . . | . . .
A . . | . . .
A T . | . t .
. . . | B . .
. . . | B . .
----------------------
Step 3:
Team A moves: Up Stay
Team B moves: Left Up
A . . | . . .
. . . | . . .
A T . | . t .
. . B | B . .
. . . | . . .
----------------------
Step 4:
Team A moves: Right Down
Team B moves: Up Left
. A . | . . .
. . . | . . .
. T B | . t .
A . B | . . .
. . . | . . .
----------------------
Step 5:
Team A moves: Right Right
Team B moves: Left Up
. . A | . . .
. . . | . . .
. B B | . t .
. A . | . . .
. . . | . . .
----------------------
Step 6:
Team A moves: Stay Left
Team B moves: Stay Left
. . A | . . .
. . . | . . .
. B . | . t .
A . . | . . .
. . . | . . .
----------------------
Step 7:
Team A moves: Right Left
Team B moves: Stay Stay
. . . | A . .
. . . | . . .
. B . | . t .
A . . | . . .
. . . | . . .
----------------------
Step 8:
Team A moves: Down Right
Team B moves: Stay Stay
. . . | . . .
. . . | A . .
. B . | . t .
. A . | . . .
. . . | . . .
----------------------
Step 9:
Team A moves: Up Stay
Team B moves: Stay Stay
. . . | A . .
. . . | . . .
. B . | . t .
. A . | . . .
. . . | . . .
----------------------
Step 10:
Team A moves: Left Down
Team B moves: Stay Stay
. . A | . . .
. . . | . . .
. B . | . t .
. . . | . . .
. A . | . . .
----------------------
Step 11:
Team A moves: Up Stay
Team B moves: Stay Stay
. . A | . . .
. . . | . . .
. B . | . t .
. . . | . . .
. A . | . . .
----------------------
Step 12:
Team A moves: Down Left
Team B moves: Stay Stay
. . . | . . .
. . A | . . .
. B . | . t .
. . . | . . .
A . . | . . .
----------------------
Step 13:
Team A moves: Left Down
Team B moves: Stay Stay
. . . | . . .
. A . | . . .
. B . | . t .
. . . | . . .
A . . | . . .
----------------------
Step 14:
Team A moves: Stay Stay
Team B moves: Stay Stay
. . . | . . .
. A . | . . .
. B . | . t .
. . . | . . .
A . . | . . .
----------------------
Step 15:
Team A moves: Stay Up
Team B moves: Stay Stay
. . . | . . .
. A . | . . .
. B . | . t .
A . . | . . .
. . . | . . .
----------------------
Step 16:
Team A moves: Left Left
Team B moves: Stay Stay
. . . | . . .
A . . | . . .
. B . | . t .
A . . | . . .
. . . | . . .
----------------------
Step 17:
Team A moves: Left Left
Team B moves: Stay Stay
. . . | . . .
A . . | . . .
. B . | . t .
A . . | . . .
. . . | . . .
----------------------
Step 18:
Team A moves: Up Down
Team B moves: Stay Stay
A . . | . . .
. . . | . . .
. B . | . t .
. . . | . . .
A . . | . . .
----------------------
Step 19:
Team A moves: Down Right
Team B moves: Stay Stay
. . . | . . .
A . . | . . .
. B . | . t .
. . . | . . .
. A . | . . .
----------------------
Step 20:
Team A moves: Up Down
Team B moves: Stay Stay
A . . | . . .
. . . | . . .
. B . | . t .
. . . | . . .
. A . | . . .
----------------------
Step 21:
Team A moves: Down Right
Team B moves: Stay Stay
. . . | . . .
A . . | . . .
. B . | . t .
. . . | . . .
. . A | . . .
----------------------
Step 22:
Team A moves: Stay Right
Team B moves: Stay Stay
. . . | . . .
A . . | . . .
. B . | . t .
. . . | . . .
. . . | A . .
----------------------
Step 23:
Team A moves: Down Up
Team B moves: Stay Stay
. . . | . . .
. . . | . . .
A B . | . t .
. . . | A . .
. . . | . . .
----------------------
Step 24:
Team A moves: Up Up
Team B moves: Stay Stay
. . . | . . .
A . . | . . .
. B . | A t .
. . . | . . .
. . . | . . .
----------------------
Step 25:
Team A moves: Down Up
Team B moves: Stay Stay
. . . | . . .
. . . | A . .
A B . | . t .
. . . | . . .
. . . | . . .
----------------------
Step 26:
Team A moves: Stay Stay
Team B moves: Stay Stay
. . . | . . .
. . . | A . .
A B . | . t .
. . . | . . .
. . . | . . .
----------------------
Step 27:
Team A moves: Up Right
Team B moves: Stay Stay
. . . | . . .
A . . | . A .
. B . | . t .
. . . | . . .
. . . | . . .
----------------------
Step 28:
Team A moves: Left Stay
Team B moves: Stay Stay
. . . | . . .
A . . | . A .
. B . | . t .
. . . | . . .
. . . | . . .
----------------------
Step 29:
Team A moves: Left Up
Team B moves: Stay Stay
. . . | . A .
A . . | . . .
. B . | . t .
. . . | . . .
. . . | . . .
----------------------
Step 30:
Team A moves: Down Left
Team B moves: Stay Stay
. . . | A . .
. . . | . . .
A B . | . t .
. . . | . . .
. . . | . . .
----------------------
Step 31:
Team A moves: Up Right
Team B moves: Stay Stay
. . . | . A .
A . . | . . .
. B . | . t .
. . . | . . .
. . . | . . .
----------------------
Step 32:
Team A moves: Up Left
Team B moves: Stay Stay
A . . | A . .
. . . | . . .
. B . | . t .
. . . | . . .
. . . | . . .
----------------------
Step 33:
Team A moves: Down Left
Team B moves: Stay Stay
. . A | . . .
A . . | . . .
. B . | . t .
. . . | . . .
. . . | . . .
----------------------
Step 34:
Team A moves: Stay Stay
Team B moves: Stay Stay
. . A | . . .
A . . | . . .
. B . | . t .
. . . | . . .
. . . | . . .
----------------------
Step 35:
Team A moves: Up Up
Team B moves: Stay Stay
A . A | . . .
. . . | . . .
. B . | . t .
. . . | . . .
. . . | . . .
----------------------
Step 36:
Team A moves: Down Down
Team B moves: Stay Stay
. . . | . . .
A . A | . . .
. B . | . t .
. . . | . . .
. . . | . . .
----------------------
Step 37:
Team A moves: Left Down
Team B moves: Stay Stay
. . . | . . .
A . . | . . .
. B A | . t .
. . . | . . .
. . . | . . .
----------------------
Step 38:
Team A moves: Stay Down
Team B moves: Stay Stay
. . . | . . .
A . . | . . .
. B . | . t .
. . A | . . .
. . . | . . .
----------------------
Step 39:
Team A moves: Left Stay
Team B moves: Stay Stay
. . . | . . .
A . . | . . .
. B . | . t .
. . A | . . .
. . . | . . .
----------------------
Step 40:
Team A moves: Right Up
Team B moves: Stay Stay
. . . | . . .
. A . | . . .
. B A | . t .
. . . | . . .
. . . | . . .
----------------------
Step 41:
Team A moves: Stay Down
Team B moves: Stay Stay
. . . | . . .
. A . | . . .
. B . | . t .
. . A | . . .
. . . | . . .
----------------------
Step 42:
Team A moves: Stay Up
Team B moves: Stay Stay
. . . | . . .
. A . | . . .
. B A | . t .
. . . | . . .
. . . | . . .
----------------------
Step 43:
Team A moves: Up Right
Team B moves: Stay Stay
. A . | . . .
. . . | . . .
. B . | A t .
. . . | . . .
. . . | . . .
----------------------
Step 44:
Team A moves: Stay Stay
Team B moves: Stay Stay
. A . | . . .
. . . | . . .
. B . | A t .
. . . | . . .
. . . | . . .
----------------------
Step 45:
Team A moves: Right Up
Team B moves: Stay Stay
. . A | . . .
. . . | A . .
. B . | . t .
. . . | . . .
. . . | . . .
----------------------
Step 46:
Team A moves: Stay Down
Team B moves: Stay Stay
. . A | . . .
. . . | . . .
. B . | A t .
. . . | . . .
. . . | . . .
----------------------
Step 47:
Team A moves: Right Up
Team B moves: Stay Stay
. . . | A . .
. . . | A . .
. B . | . t .
. . . | . . .
. . . | . . .
----------------------
Step 48:
Team A moves: Down Right
Team B moves: Stay Stay
. . . | . . .
. . . | A A .
. B . | . t .
. . . | . . .
. . . | . . .
----------------------
Step 49:
Team A moves: Down Left
Team B moves: Stay Stay
. . . | . . .
. . . | A . .
. B . | A t .
. . . | . . .
. . . | . . .
----------------------
Step 50:
Team A moves: Down Stay
Team B moves: Stay Stay
. . . | . . .
. . . | A . .
. B . | . t .
. . . | A . .
. . . | . . .
----------------------
Step 51:
Team A moves: Stay Left
Team B moves: Stay Stay
. . . | . . .
. . A | . . .
. B . | . t .
. . . | A . .
. . . | . . .
----------------------
Step 52:
Team A moves: Stay Right
Team B moves: Stay Stay
. . . | . . .
. . . | A . .
. B . | . t .
. . . | A . .
. . . | . . .
----------------------
Step 53:
Team A moves: Right Down
Team B moves: Stay Stay
. . . | . . .
. . . | . . .
. B . | A t .
. . . | . A .
. . . | . . .
----------------------
Step 54:
Team A moves: Left Up
Team B moves: Stay Stay
. . . | . . .
. . . | A . .
. B . | . t .
. . . | A . .
. . . | . . .
----------------------
Step 55:
Team A moves: Left Left
Team B moves: Stay Stay
. . . | . . .
. . A | . . .
. B . | . t .
. . A | . . .
. . . | . . .
----------------------
Step 56:
Team A moves: Left Right
Team B moves: Stay Stay
. . . | . . .
. . . | A . .
. B . | . t .
. A . | . . .
. . . | . . .
----------------------
Step 57:
Team A moves: Left Down
Team B moves: Stay Stay
. . . | . . .
. . . | . . .
. B . | A t .
A . . | . . .
. . . | . . .
----------------------
Step 58:
Team A moves: Up Down
Team B moves: Stay Stay
. . . | . . .
. . . | . . .
A B . | . t .
. . . | A . .
. . . | . . .
----------------------
Step 59:
Team A moves: Stay Down
Team B moves: Stay Stay
. . . | . . .
. . . | . . .
A B . | . t .
. . . | . . .
. . . | A . .
----------------------
Step 60:
Team A moves: Stay Left
Team B moves: Stay Stay
. . . | . . .
. . . | . . .
A B . | . t .
. . . | . . .
. . A | . . .
----------------------
Step 61:
Team A moves: Up Up
Team B moves: Stay Stay
. . . | . . .
A . . | . . .
. B . | . t .
. . A | . . .
. . . | . . .
----------------------
Step 62:
Team A moves: Stay Up
Team B moves: Stay Stay
. . . | . . .
A . . | . . .
. B A | . t .
. . . | . . .
. . . | . . .
----------------------
Step 63:
Team A moves: Left Stay
Team B moves: Stay Stay
. . . | . . .
A . . | . . .
. B A | . t .
. . . | . . .
. . . | . . .
----------------------
Step 64:
Team A moves: Left Down
Team B moves: Stay Stay
. . . | . . .
A . . | . . .
. B . | . t .
. . A | . . .
. . . | . . .
----------------------
Step 65:
Team A moves: Stay Up
Team B moves: Stay Stay
. . . | . . .
A . . | . . .
. B A | . t .
. . . | . . .
. . . | . . .
----------------------
Step 66:
Team A moves: Left Right
Team B moves: Stay Stay
. . . | . . .
A . . | . . .
. B . | A t .
. . . | . . .
. . . | . . .
----------------------
Step 67:
Team A moves: Right Down
Team B moves: Stay Stay
. . . | . . .
. A . | . . .
. B . | . t .
. . . | A . .
. . . | . . .
----------------------
Step 68:
Team A moves: Down Up
Team B moves: Stay Stay
. . . | . . .
. . . | . . .
. A . | A t .
. . . | . . .
. . . | . . .
----------------------
Step 69:
Team A moves: Left Right
Team B moves: Stay Stay
. . . | . . .
. . . | . . .
A T . | . A .
. . . | . . .
. . . | . . .
----------------------
Step 70:
Team A moves: Stay Stay
Team B moves: Stay Stay
. . . | . . .
. . . | . . .
A T . | . A .
. . . | . . .
. . . | . . .
----------------------
Step 71:
Team A moves: Left Down
Team B moves: Stay Stay
. . . | . . .
. . . | . . .
A T . | . t .
. . . | . A .
. . . | . . .
----------------------
Step 72:
Team A moves: Stay Left
Team B moves: Stay Stay
. . . | . . .
. . . | . . .
A T . | . t .
. . . | A . .
. . . | . . .
----------------------
Step 73:
Team A moves: Right Stay
Team B moves: Stay Stay
. . . | . . .
. . . | . . .
. A . | . t .
. . . | A . .
. . . | . . .
----------------------
Step 74:
Team A moves: Stay Left
Team B moves: Stay Stay
. . . | . . .
. . . | . . .
. A . | . t .
. . A | . . .
. . . | . . .
----------------------
Winner: Team A
Steps: 74 Captures(A:2, B:0)
```
