#include <bits/stdc++.h>
using namespace std;

// ------------------------- Position -------------------------
struct Position
{
    int x, y;
    Position(int a = 0, int b = 0) : x(a), y(b) {}
    bool operator==(const Position &other) const { return x == other.x && y == other.y; }
};

// ------------------------- Player -------------------------
struct Player
{
    Position pos;
    bool alive;
    bool carryingTreasure;
    Player(int x = 0, int y = 0)
    {
        pos = Position(x, y);
        alive = true;
        carryingTreasure = false;
    }
};

// ------------------------- GameResult -------------------------
struct GameResult
{
    int winner; // 0=A, 1=B, -1=Draw
    int steps;
    int capturesA, capturesB;
};

// ------------------------- GameState -------------------------
class GameState
{
public:
    int rows, cols;
    vector<Player> teamA, teamB;
    Position treasureA, treasureB;
    bool turnBased;
    int capturesA, capturesB;

    GameState(int r = 5, int c = 6, bool turnMode = true)
    {
        rows = r;
        cols = c;
        turnBased = turnMode;
        capturesA = capturesB = 0;
        treasureA = Position(0, 0);
        treasureB = Position(0, 0);
    }

    Position clampPos(const Position &p) const
    {
        int nx = p.x, ny = p.y;
        if (nx < 0)
            nx = 0;
        if (nx >= rows)
            nx = rows - 1;
        if (ny < 0)
            ny = 0;
        if (ny >= cols)
            ny = cols - 1;
        return Position(nx, ny);
    }

    void initCustom(Position a1, Position a2, Position b1, Position b2, Position tA, Position tB)
    {
        teamA.clear();
        teamB.clear();
        a1 = clampPos(a1);
        a2 = clampPos(a2);
        b1 = clampPos(b1);
        b2 = clampPos(b2);
        tA = clampPos(tA);
        tB = clampPos(tB);
        teamA.emplace_back(a1.x, a1.y);
        teamA.emplace_back(a2.x, a2.y);
        teamB.emplace_back(b1.x, b1.y);
        teamB.emplace_back(b2.x, b2.y);
        treasureA = tA;
        treasureB = tB;
        capturesA = capturesB = 0;
    }

    // Apply moves: vectors of moves for each player (0=stay,1=up,2=down,3=left,4=right)
    void applyMoves(vector<int> movesA, vector<int> movesB)
    {
        while ((int)movesA.size() < (int)teamA.size())
            movesA.push_back(0);
        while ((int)movesB.size() < (int)teamB.size())
            movesB.push_back(0);

        auto movePlayer = [&](Player &p, int move)
        {
            if (!p.alive)
                return;
            if (move == 1 && p.pos.x > 0)
                p.pos.x--;
            else if (move == 2 && p.pos.x < rows - 1)
                p.pos.x++;
            else if (move == 3 && p.pos.y > 0)
                p.pos.y--;
            else if (move == 4 && p.pos.y < cols - 1)
                p.pos.y++;
        };

        if (turnBased)
        {
            for (int i = 0; i < (int)teamA.size(); ++i)
                movePlayer(teamA[i], movesA[i]);
            checkCaptures();
            for (int i = 0; i < (int)teamB.size(); ++i)
                movePlayer(teamB[i], movesB[i]);
            checkCaptures();
        }
        else
        {
            for (int i = 0; i < (int)teamA.size(); ++i)
                movePlayer(teamA[i], movesA[i]);
            for (int i = 0; i < (int)teamB.size(); ++i)
                movePlayer(teamB[i], movesB[i]);
            checkCaptures();
        }
        checkTreasurePickup();
    }

    void checkCaptures()
    {
        for (auto &a : teamA)
        {
            for (auto &b : teamB)
            {
                if (a.alive && b.alive && a.pos == b.pos)
                {
                    // If B is in A's home half (y < cols/2), B is captured by A.
                    if (b.pos.y < cols / 2)
                    {
                        b.alive = false;
                        capturesA++;
                    }
                    // Else if A is in B's half, A is captured by B.
                    else if (a.pos.y >= cols / 2)
                    {
                        a.alive = false;
                        capturesB++;
                    }
                }
            }
        }
    }

    void checkTreasurePickup()
    {
        for (auto &a : teamA)
            if (a.alive && !a.carryingTreasure && a.pos == treasureB)
                a.carryingTreasure = true;
        for (auto &b : teamB)
            if (b.alive && !b.carryingTreasure && b.pos == treasureA)
                b.carryingTreasure = true;
    }

    bool checkWin(int teamId) const
    {
        if (teamId == 0)
        {
            for (const auto &a : teamA)
                if (a.carryingTreasure && a.pos.y < cols / 2)
                    return true;
        }
        else
        {
            for (const auto &b : teamB)
                if (b.carryingTreasure && b.pos.y >= cols / 2)
                    return true;
        }
        return false;
    }

    void printBoard() const
    {
        vector<vector<char>> grid(rows, vector<char>(cols, '.'));
        if (treasureA.x >= 0 && treasureA.x < rows && treasureA.y >= 0 && treasureA.y < cols)
            grid[treasureA.x][treasureA.y] = 'T';
        if (treasureB.x >= 0 && treasureB.x < rows && treasureB.y >= 0 && treasureB.y < cols)
            grid[treasureB.x][treasureB.y] = 't';
        for (const auto &a : teamA)
            if (a.alive && a.pos.x >= 0 && a.pos.x < rows && a.pos.y >= 0 && a.pos.y < cols)
                grid[a.pos.x][a.pos.y] = 'A';
        for (const auto &b : teamB)
            if (b.alive && b.pos.x >= 0 && b.pos.x < rows && b.pos.y >= 0 && b.pos.y < cols)
                grid[b.pos.x][b.pos.y] = 'B';

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                cout << grid[i][j] << ' ';
                if (j == cols / 2 - 1)
                    cout << "| ";
            }
            cout << '\n';
        }
        cout << "----------------------\n";
    }
};

// ------------------------- Agent Base -------------------------
class Agent
{
public:
    string name;
    Agent(string n) : name(n) {}
    virtual vector<int> getMoves(const GameState &state, int teamId) = 0;
    virtual ~Agent() = default;
};

// ------------------------- Helpers -------------------------
string moveToString(int m)
{
    if (m == 0)
        return "Stay";
    if (m == 1)
        return "Up";
    if (m == 2)
        return "Down";
    if (m == 3)
        return "Left";
    if (m == 4)
        return "Right";
    return "?";
}
int manhattan(const Position &a, const Position &b) { return abs(a.x - b.x) + abs(a.y - b.y); }

// ------------------------- Random Agent -------------------------
class RandomAgent : public Agent
{
public:
    RandomAgent() : Agent("Random") {}
    vector<int> getMoves(const GameState &state, int teamId) override
    {
        vector<int> moves;
        size_t n = (teamId == 0 ? state.teamA.size() : state.teamB.size());
        for (size_t i = 0; i < n; i++)
            moves.push_back(rand() % 5);
        return moves;
    }
};

// ------------------------- Greedy Agent -------------------------
class GreedyAgent : public Agent
{
public:
    GreedyAgent() : Agent("Greedy") {}
    vector<int> getMoves(const GameState &state, int teamId) override
    {
        vector<int> moves;
        if (teamId == 0)
            for (const auto &p : state.teamA)
                moves.push_back(bestMove(p, state.treasureB));
        else
            for (const auto &p : state.teamB)
                moves.push_back(bestMove(p, state.treasureA));
        return moves;
    }

private:
    int bestMove(const Player &p, const Position &target) const
    {
        if (!p.alive)
            return 0;
        int dx = target.x - p.pos.x;
        int dy = target.y - p.pos.y;
        if (abs(dx) >= abs(dy))
        {
            if (dx < 0)
                return 1;
            if (dx > 0)
                return 2;
        }
        if (dy < 0)
            return 3;
        if (dy > 0)
            return 4;
        return 0;
    }
};

// ------------------------- Utility: generate all joint moves for a team -------------------------
static void generateAllJointMovesRec(int players, vector<int> &cur, vector<vector<int>> &out)
{
    if ((int)cur.size() == players)
    {
        out.push_back(cur);
        return;
    }
    for (int m = 0; m < 5; ++m)
    {
        cur.push_back(m);
        generateAllJointMovesRec(players, cur, out);
        cur.pop_back();
    }
}
static vector<vector<int>> generateAllJointMoves(int players)
{
    vector<vector<int>> out;
    vector<int> cur;
    generateAllJointMovesRec(players, cur, out);
    return out;
}

// ------------------------- Evaluation -------------------------
// positive means good for teamId
double evaluateState(const GameState &s, int teamId)
{
    // Simple heuristic:
    // +10000 if teamId wins, -10000 if opponent wins
    // +500 per player carrying treasure for teamId, -500 for opponent
    // - (sum distances to target) for team players, + (sum distances for opponent)
    // + 50 * (capturesA - capturesB) (if teamId==0) or reverse
    if (s.checkWin(teamId))
        return 10000.0;
    if (s.checkWin(1 - teamId))
        return -10000.0;

    double score = 0.0;
    // captures weight
    int capDiff = (teamId == 0 ? (s.capturesA - s.capturesB) : (s.capturesB - s.capturesA));
    score += 50.0 * capDiff;

    // carrying treasure weight
    if (teamId == 0)
    {
        for (const auto &a : s.teamA)
            if (a.carryingTreasure)
                score += 500.0;
        for (const auto &b : s.teamB)
            if (b.carryingTreasure)
                score -= 500.0;
    }
    else
    {
        for (const auto &b : s.teamB)
            if (b.carryingTreasure)
                score += 500.0;
        for (const auto &a : s.teamA)
            if (a.carryingTreasure)
                score -= 500.0;
    }

    // distance term: closer is better => subtract distances for team, add distances for opponent
    int dTeam = 0, dOpp = 0;
    if (teamId == 0)
    {
        for (const auto &a : s.teamA)
            if (a.alive)
                dTeam += manhattan(a.pos, s.treasureB);
            else
                dTeam += 100;
        for (const auto &b : s.teamB)
            if (b.alive)
                dOpp += manhattan(b.pos, s.treasureA);
            else
                dOpp += 100;
    }
    else
    {
        for (const auto &b : s.teamB)
            if (b.alive)
                dTeam += manhattan(b.pos, s.treasureA);
            else
                dTeam += 100;
        for (const auto &a : s.teamA)
            if (a.alive)
                dOpp += manhattan(a.pos, s.treasureB);
            else
                dOpp += 100;
    }
    score += -1.0 * dTeam + 0.5 * dOpp; // weight distances

    return score;
}

// ------------------------- Alpha-Beta Agent -------------------------
class AlphaBetaAgent : public Agent
{
public:
    AlphaBetaAgent(int depthLimit = 3) : Agent("AlphaBeta"), depthLimit(depthLimit) {}
    vector<int> getMoves(const GameState &state, int teamId) override
    {
        // generate all joint moves for this team (2 players => 25 combos)
        int players = (teamId == 0 ? (int)state.teamA.size() : (int)state.teamB.size());
        auto jointMoves = generateAllJointMoves(players);
        double bestVal = -1e18;
        vector<int> best = jointMoves[0];

        // evaluate each joint move by applying it and running alphabeta search
        for (auto &mv : jointMoves)
        {
            GameState s = state;
            // we need an opponent move placeholder when doing turn-based? In our alphabeta we alternate levels: after this team moves, opponent moves etc.
            // For now: apply mv for this team and call alphabeta for depth-1 with opponent to move
            if (teamId == 0)
            {
                // For opponent moves initially, we don't know; we allow alphabeta to generate opp joint moves at next level
                s.applyMoves(mv, vector<int>(s.teamB.size(), 0)); // apply A's choice (B stays as baseline), then recursion will consider B moves
            }
            else
            {
                s.applyMoves(vector<int>(s.teamA.size(), 0), mv);
            }
            double val = alphabeta(s, depthLimit - 1, -1e18, 1e18, false, teamId);
            if (val > bestVal)
            {
                bestVal = val;
                best = mv;
            }
        }
        return best;
    }

private:
    int depthLimit;

    // maximizingPlayer == true means it's 'teamId' turn to choose; false -> opponent turn
    double alphabeta(GameState s, int depth, double alpha, double beta, bool maximizingPlayer, int teamId)
    {
        if (depth <= 0 || s.checkWin(0) || s.checkWin(1))
        {
            return evaluateState(s, teamId);
        }
        int curTeam = maximizingPlayer ? teamId : 1 - teamId;
        int players = (curTeam == 0 ? (int)s.teamA.size() : (int)s.teamB.size());
        auto jointMoves = generateAllJointMoves(players);

        if (maximizingPlayer)
        {
            double value = -1e18;
            for (auto &mv : jointMoves)
            {
                GameState ns = s;
                if (curTeam == 0)
                    ns.applyMoves(mv, vector<int>(ns.teamB.size(), 0));
                else
                    ns.applyMoves(vector<int>(ns.teamA.size(), 0), mv);
                double childVal = alphabeta(ns, depth - 1, alpha, beta, false, teamId);
                value = max(value, childVal);
                alpha = max(alpha, value);
                if (alpha >= beta)
                    break; // beta cutoff
            }
            return value;
        }
        else
        {
            double value = 1e18;
            for (auto &mv : jointMoves)
            {
                GameState ns = s;
                if (curTeam == 0)
                    ns.applyMoves(mv, vector<int>(ns.teamB.size(), 0));
                else
                    ns.applyMoves(vector<int>(ns.teamA.size(), 0), mv);
                double childVal = alphabeta(ns, depth - 1, alpha, beta, true, teamId);
                value = min(value, childVal);
                beta = min(beta, value);
                if (alpha >= beta)
                    break; // alpha cutoff
            }
            return value;
        }
    }
};

// ------------------------- Simulation (random playout) -------------------------
int simulateRandomPlayout(GameState s, int maxSteps = 60)
{
    // returns: winner 0/1/-1
    RandomAgent randAgent;
    GreedyAgent greedyAgent;
    for (int step = 0; step < maxSteps; ++step)
    {
        // both teams pick random moves for playout
        vector<int> aMoves = randAgent.getMoves(s, 0);
        vector<int> bMoves = randAgent.getMoves(s, 1);
        s.applyMoves(aMoves, bMoves);
        bool aWin = s.checkWin(0), bWin = s.checkWin(1);
        if (aWin && bWin)
            return -1;
        if (aWin)
            return 0;
        if (bWin)
            return 1;
    }
    return -1;
}

// ------------------------- MCTS-lite Agent (simulation-based chooser) -------------------------
class MCTSAgent : public Agent
{
public:
    MCTSAgent(int simsPerMove = 30, int playoutMax = 60) : Agent("MCTS"), simsPerMove(simsPerMove), playoutMax(playoutMax) {}
    vector<int> getMoves(const GameState &state, int teamId) override
    {
        int players = (teamId == 0 ? (int)state.teamA.size() : (int)state.teamB.size());
        auto jointMoves = generateAllJointMoves(players);
        // if only one candidate (shouldn't happen) return it
        double bestRate = -1.0;
        vector<int> best = jointMoves[0];

        for (auto &mv : jointMoves)
        {
            int wins = 0;
            for (int sim = 0; sim < simsPerMove; ++sim)
            {
                GameState s = state;
                if (teamId == 0)
                    s.applyMoves(mv, vector<int>(s.teamB.size(), 0));
                else
                    s.applyMoves(vector<int>(s.teamA.size(), 0), mv);
                // now simulate rest randomly until terminal
                int winner = simulateRandomPlayout(s, playoutMax);
                if (winner == teamId)
                    wins++;
            }
            double rate = (double)wins / (double)simsPerMove;
            // prefer higher win rate, break ties by lower simulation time implicit
            if (rate > bestRate)
            {
                bestRate = rate;
                best = mv;
            }
        }
        return best;
    }

private:
    int simsPerMove;
    int playoutMax;
};

// ------------------------- playGame (verbosity 0/1/2) -------------------------
GameResult playGame(GameState env, Agent *A, Agent *B, int verbosity = 2, int gameNum = -1)
{
    if (verbosity == 2)
    {
        cout << "Game Start: Team A(" << A->name << ") vs Team B(" << B->name << ")\n";
        env.printBoard();
    }
    RandomAgent randAgent; // used if agents produce too few moves
    int step = 0, maxSteps = 200;
    while (step++ < maxSteps)
    {
        vector<int> movesA = A->getMoves(env, 0);
        vector<int> movesB = B->getMoves(env, 1);
        // safety: pad
        while ((int)movesA.size() < (int)env.teamA.size())
            movesA.push_back(0);
        while ((int)movesB.size() < (int)env.teamB.size())
            movesB.push_back(0);

        if (verbosity == 2)
        {
            cout << "Step " << step << ":\n";
            cout << "Team A moves: ";
            for (int m : movesA)
                cout << moveToString(m) << " ";
            cout << "\n";
            cout << "Team B moves: ";
            for (int m : movesB)
                cout << moveToString(m) << " ";
            cout << "\n";
        }
        env.applyMoves(movesA, movesB);
        if (verbosity == 2)
            env.printBoard();

        bool aWin = env.checkWin(0), bWin = env.checkWin(1);
        if (aWin && bWin)
        {
            if (verbosity == 1)
            {
                if (gameNum > 0)
                    cout << "Game " << gameNum << ": Draw in " << step << " steps\n";
                else
                    cout << A->name << " vs " << B->name << " -> Draw in " << step << " steps\n";
            }
            return {-1, step, env.capturesA, env.capturesB};
        }
        if (aWin)
        {
            if (verbosity == 1)
            {
                if (gameNum > 0)
                    cout << "Game " << gameNum << ": A won in " << step << " steps\n";
                else
                    cout << A->name << " vs " << B->name << " -> Winner A in " << step << " steps\n";
            }
            return {0, step, env.capturesA, env.capturesB};
        }
        if (bWin)
        {
            if (verbosity == 1)
            {
                if (gameNum > 0)
                    cout << "Game " << gameNum << ": B won in " << step << " steps\n";
                else
                    cout << A->name << " vs " << B->name << " -> Winner B in " << step << " steps\n";
            }
            return {1, step, env.capturesA, env.capturesB};
        }
    }
    if (verbosity == 1)
    {
        if (gameNum > 0)
            cout << "Game " << gameNum << ": Draw (timeout) in " << maxSteps << " steps\n";
        else
            cout << A->name << " vs " << B->name << " -> Draw (timeout) in " << maxSteps << " steps\n";
    }
    return {-1, maxSteps, env.capturesA, env.capturesB};
}

// ------------------------- Tournament -------------------------
void simulateTournament(const GameState &baseEnv, const vector<Agent *> &agents, int games = 100, bool perGameLines = false)
{
    cout << "\n===== Tournament: " << games << " games per ordered pair =====\n";
    for (size_t i = 0; i < agents.size(); ++i)
    {
        for (size_t j = 0; j < agents.size(); ++j)
        {
            if (i == j)
                continue;
            int winA = 0, winB = 0, draw = 0;
            long long stepsA = 0, stepsB = 0;
            for (int g = 1; g <= games; ++g)
            {
                GameState env = baseEnv;
                int verbosity = perGameLines ? 1 : 0;
                GameResult res = playGame(env, agents[i], agents[j], verbosity, perGameLines ? g : -1);
                if (res.winner == 0)
                {
                    winA++;
                    stepsA += res.steps;
                }
                else if (res.winner == 1)
                {
                    winB++;
                    stepsB += res.steps;
                }
                else
                    draw++;
            }
            cout << agents[i]->name << " (A) vs " << agents[j]->name << " (B)  --> "
                 << "A_wins=" << winA << ", B_wins=" << winB << ", Draws=" << draw;
            if (winA)
                cout << ", avgStepsA=" << fixed << setprecision(2) << (double)stepsA / winA;
            if (winB)
                cout << ", avgStepsB=" << fixed << setprecision(2) << (double)stepsB / winB;
            cout << "\n";
        }
    }
}

// ------------------------- MAIN -------------------------
int main()
{
    srand((unsigned)time(nullptr));

    int rows = 5, cols = 6;
    GameState baseEnv(rows, cols, true);

    Position a1, a2, b1, b2, tA, tB;
    cout << "Do you want default setup? (y/n): ";
    char ch;
    cin >> ch;

    if (ch == 'y' || ch == 'Y')
    {
        a1 = Position(0, 0);
        a2 = Position(1, 0);
        b1 = Position(3, 5);
        b2 = Position(4, 5);
        tA = Position(2, 1);
        tB = Position(2, 4);
        cout << "Using default setup (5x6).\n";
    }
    else
    {
        cout << "Enter Team A Player1 start (row col): ";
        cin >> a1.x >> a1.y;
        cout << "Enter Team A Player2 start (row col): ";
        cin >> a2.x >> a2.y;
        cout << "Enter Team B Player1 start (row col): ";
        cin >> b1.x >> b1.y;
        cout << "Enter Team B Player2 start (row col): ";
        cin >> b2.x >> b2.y;
        cout << "Enter Treasure A position (row col): ";
        cin >> tA.x >> tA.y;
        cout << "Enter Treasure B position (row col): ";
        cin >> tB.x >> tB.y;
    }
    baseEnv.initCustom(a1, a2, b1, b2, tA, tB);

    // Agents
    RandomAgent randomAgent;
    GreedyAgent greedyAgent;
    AlphaBetaAgent alphaAgent(3); // depth 3
    MCTSAgent mctsAgent(30, 60);  // 30 playouts

    vector<Agent *> agents = {&randomAgent, &greedyAgent, &alphaAgent, &mctsAgent};

    cout << "\nChoose mode: 1 = Single Game, 2 = Tournament: ";
    int mode;
    cin >> mode;

    if (mode == 1)
    {
        cout << "Choose Agent for Team A (1=Random,2=Greedy,3=AlphaBeta,4=MCTS): ";
        int ca;
        cin >> ca;
        cout << "Choose Agent for Team B (1=Random,2=Greedy,3=AlphaBeta,4=MCTS): ";
        int cb;
        cin >> cb;
        if (ca < 1 || ca > 4)
            ca = 1;
        if (cb < 1 || cb > 4)
            cb = 1;
        Agent *A = agents[ca - 1];
        Agent *B = agents[cb - 1];

        cout << "Choose gameplay type: 1=Turn-based,2=Simultaneous: ";
        int gm;
        cin >> gm;
        baseEnv.turnBased = (gm == 1);

        GameResult res = playGame(baseEnv, A, B, 2, -1);
        if (res.winner == -1)
            cout << "Result: Draw!\n";
        else
            cout << "Winner: Team " << (res.winner == 0 ? "A" : "B") << "\n";
        cout << "Steps: " << res.steps << " Captures(A:" << res.capturesA << ", B:" << res.capturesB << ")\n";
    }
    else
    {
        cout << "Choose gameplay type for tournament: 1=Turn-based,2=Simultaneous: ";
        int gm;
        cin >> gm;
        baseEnv.turnBased = (gm == 1);

        cout << "Enter number of games per pairing (e.g.100): ";
        int n;
        cin >> n;
        if (n <= 0)
            n = 100;

        cout << "Show concise per-game lines? (y/n): ";
        char pg;
        cin >> pg;
        bool perGame = (pg == 'y' || pg == 'Y');

        simulateTournament(baseEnv, agents, n, perGame);
    }

    // Safe exit pause (optional)
    cout << "\nPress ENTER to exit...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush leftover newline
    string dummy;
    getline(cin, dummy);

    return 0;
}
