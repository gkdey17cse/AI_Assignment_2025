// main.cpp
// Container loading problem - single file
// - 4 stacks fixed: stacks 0-1 = left/port, 2-3 = right/starboard
// - Hard constraints enforced: balance (left/right diff <= BALANCE_LIMIT), max height, and weight (no heavier above lighter)
// - BFS explores state space (with node limit), Greedy and A* use heuristics
// - Prints to console and to output.txt
//
// Compile:
//   g++ -std=c++17 -O2 -o main main.cpp
// Run:
//   ./main   (reads input.txt, writes output.txt)

#include <bits/stdc++.h>
using namespace std;
using Clock = chrono::high_resolution_clock;

constexpr int NUM_STACKS = 4;
int MAX_HEIGHT = 4;
int BALANCE_LIMIT = 20;
int N = 0;

const int LOAD_COST = 1;
const int PENALTY_UNIT = 2;
const int BFS_NODE_LIMIT = 2000000; // adjust as needed

struct Container
{
    int weight;
    int dest;
};
vector<Container> containers;

struct Action
{
    int cid;
    int stack_id;
};

struct State
{
    vector<vector<int>> stacks;
    unsigned int loaded_mask = 0;
    int g_cost = 0;
};

struct ParentInfo
{
    string parent_key = "";
    Action action = {-1, -1};
    int g = 0;
};

// Dual output helper
struct DualOut
{
    ofstream fout;
    bool ok = false;
    DualOut(const string &fname)
    {
        fout.open(fname);
        ok = fout.is_open();
        if (!ok)
            cerr << "Warning: could not open " << fname << " for writing\n";
    }
    ~DualOut()
    {
        if (fout.is_open())
            fout.close();
    }
    template <typename T>
    DualOut &operator<<(const T &x)
    {
        cout << x;
        if (ok)
            fout << x;
        return *this;
    }
    DualOut &operator<<(ostream &(*manip)(ostream &))
    {
        manip(cout);
        if (ok)
            manip(fout);
        return *this;
    }
};

// ---------- state key ----------
string state_key(const State &st)
{
    string key;
    key.reserve(256);
    for (int s = 0; s < NUM_STACKS; ++s)
    {
        key.push_back('|');
        for (int c : st.stacks[s])
        {
            key += to_string(c);
            key.push_back(',');
        }
    }
    key += "#";
    key += to_string(st.loaded_mask);
    return key;
}

// ---------- violation counters (destination blocks, weight inversions) ----------
pair<int, int> count_dest_and_weight_violations(const State &st)
{
    int dest_block = 0;
    int wt_viol = 0;
    for (int s = 0; s < NUM_STACKS; ++s)
    {
        const auto &col = st.stacks[s];
        int h = (int)col.size();
        for (int i = 0; i < h; ++i)
        {
            for (int j = i + 1; j < h; ++j)
            {
                int below = col[i], above = col[j];
                if (containers[below].dest < containers[above].dest)
                    dest_block++;
                if (containers[above].weight > containers[below].weight)
                    wt_viol++;
            }
        }
    }
    return {dest_block, wt_viol};
}

int count_balance_violation(const State &st)
{
    int left = 0, right = 0;
    for (int i = 0; i < 2; ++i)
        for (int c : st.stacks[i])
            left += containers[c].weight;
    for (int i = 2; i < 4; ++i)
        for (int c : st.stacks[i])
            right += containers[c].weight;
    return (abs(left - right) > BALANCE_LIMIT) ? 1 : 0;
}

int compute_total_violations(const State &st, bool include_balance)
{
    auto p = count_dest_and_weight_violations(st);
    int total = p.first + p.second;
    if (include_balance)
        total += count_balance_violation(st);
    return total;
}

// ---------- pretty violation description ----------
void describe_violations(const State &st, DualOut &out)
{
    for (int s = 0; s < NUM_STACKS; ++s)
    {
        out << "Stack " << s << " (bottom->top): ";
        for (int c : st.stacks[s])
            out << c << "(" << containers[c].weight << "," << containers[c].dest << ") ";
        out << "\n";
    }
    auto p = count_dest_and_weight_violations(st);
    int left = 0, right = 0;
    for (int i = 0; i < 2; ++i)
        for (int c : st.stacks[i])
            left += containers[c].weight;
    for (int i = 2; i < 4; ++i)
        for (int c : st.stacks[i])
            right += containers[c].weight;

    // list specifics
    for (int s = 0; s < NUM_STACKS; ++s)
    {
        const auto &col = st.stacks[s];
        int h = (int)col.size();
        for (int i = 0; i < h; ++i)
        {
            for (int j = i + 1; j < h; ++j)
            {
                int below = col[i], above = col[j];
                if (containers[below].dest < containers[above].dest)
                    out << "DEST-BLOCK stack " << s << " below " << below << " blocked by " << above << "\n";
                if (containers[above].weight > containers[below].weight)
                    out << "WT-VIOL stack " << s << " above " << above << " heavier than " << below << "\n";
            }
        }
    }
    if (abs(left - right) > BALANCE_LIMIT)
    {
        out << "BAL-VIOL: left=" << left << " right=" << right << " limit=" << BALANCE_LIMIT << "\n";
    }
    out << "Totals: dest-blocks=" << p.first << " wt-viol=" << p.second << " balance-viol=" << (abs(left - right) > BALANCE_LIMIT ? 1 : 0) << "\n";
    out << "Total violations (for reporting) = " << (p.first + p.second + (abs(left - right) > BALANCE_LIMIT ? 1 : 0)) << " (penalty each=" << PENALTY_UNIT << ")\n";
}

// ---------- possible actions (enforce HARD constraints) ----------
// Returns list of valid actions (placing a remaining container onto a stack)
// Enforces:
//   - stack not full
//   - weight constraint: container.weight <= top.weight (or stack empty)
//   - balance constraint after placement: abs(left-right) <= BALANCE_LIMIT
vector<Action> possible_actions_hard(const State &cur)
{
    vector<Action> acts;
    // current left/right weights
    int left = 0, right = 0;
    for (int i = 0; i < 2; ++i)
        for (int c : cur.stacks[i])
            left += containers[c].weight;
    for (int i = 2; i < 4; ++i)
        for (int c : cur.stacks[i])
            right += containers[c].weight;

    for (int cid = 0; cid < N; ++cid)
    {
        if ((cur.loaded_mask >> cid) & 1u)
            continue;
        int w = containers[cid].weight;
        for (int s = 0; s < NUM_STACKS; ++s)
        {
            if ((int)cur.stacks[s].size() >= MAX_HEIGHT)
                continue;
            if (!cur.stacks[s].empty())
            {
                int topc = cur.stacks[s].back();
                if (w > containers[topc].weight)
                    continue; // can't place heavier above lighter
            }
            int new_left = left, new_right = right;
            if (s < 2)
                new_left += w;
            else
                new_right += w;
            if (abs(new_left - new_right) > BALANCE_LIMIT)
                continue; // hard balance
            acts.push_back({cid, s});
        }
    }
    return acts;
}

// ---------- BFS (hard constraints) ----------
bool BFS_search(State start, State &goal_out, map<string, ParentInfo> &parent_map, int &expanded_nodes, int node_limit = BFS_NODE_LIMIT)
{
    queue<State> q;
    unordered_set<string> visited;
    parent_map.clear();
    expanded_nodes = 0;

    string sk = state_key(start);
    q.push(start);
    visited.insert(sk);
    parent_map[sk] = {"", {-1, -1}, 0};

    while (!q.empty())
    {
        State cur = q.front();
        q.pop();
        expanded_nodes++;
        if (expanded_nodes > node_limit)
        {
            return false; // node limit reached
        }
        if ((int)__builtin_popcount(cur.loaded_mask) == N)
        {
            goal_out = cur;
            return true;
        }
        auto acts = possible_actions_hard(cur);
        for (const auto &a : acts)
        {
            State nxt = cur;
            nxt.stacks[a.stack_id].push_back(a.cid);
            nxt.loaded_mask |= (1u << a.cid);
            nxt.g_cost = cur.g_cost + LOAD_COST;
            string k = state_key(nxt);
            if (visited.insert(k).second)
            {
                parent_map[k] = {state_key(cur), a, nxt.g_cost};
                q.push(nxt);
            }
        }
    }
    return false;
}

// ---------- Greedy best-first (hard constraints) ----------
struct PQNodeG
{
    State st;
    int h;
};
struct PQCmpG
{
    bool operator()(const PQNodeG &a, const PQNodeG &b) const { return a.h > b.h; }
};

bool Greedy_search(State start, State &goal_out, map<string, ParentInfo> &parent_map, int &expanded_nodes, int node_limit = BFS_NODE_LIMIT)
{
    priority_queue<PQNodeG, vector<PQNodeG>, PQCmpG> pq;
    unordered_set<string> visited;
    parent_map.clear();
    expanded_nodes = 0;

    pq.push({start, 0});
    parent_map[state_key(start)] = {"", {-1, -1}, 0};

    while (!pq.empty())
    {
        auto top = pq.top();
        pq.pop();
        State cur = top.st;
        string ck = state_key(cur);
        if (visited.count(ck))
            continue;
        visited.insert(ck);
        expanded_nodes++;
        if (expanded_nodes > node_limit)
            return false;
        if ((int)__builtin_popcount(cur.loaded_mask) == N)
        {
            goal_out = cur;
            return true;
        }

        auto acts = possible_actions_hard(cur);
        for (const auto &a : acts)
        {
            State nxt = cur;
            nxt.stacks[a.stack_id].push_back(a.cid);
            nxt.loaded_mask |= (1u << a.cid);
            nxt.g_cost = cur.g_cost + LOAD_COST;
            string k = state_key(nxt);
            if (visited.count(k))
                continue;
            // heuristic: prefer fewer dest-blocks and weight violations (soft)
            auto dv = count_dest_and_weight_violations(nxt);
            int heuristic = dv.first * 5 + dv.second * 2 + (N - __builtin_popcount(nxt.loaded_mask)); // weighted
            parent_map[k] = {ck, a, nxt.g_cost};
            pq.push({nxt, heuristic});
        }
    }
    return false;
}

// ---------- A* (hard constraints + improved heuristic) ----------
struct ANode
{
    State st;
    int g;
    int h;
};
struct ACmp
{
    bool operator()(const ANode &a, const ANode &b) const
    {
        if (a.g + a.h != b.g + b.h)
            return a.g + a.h > b.g + b.h;
        return a.g < b.g;
    }
};

bool Astar_search(State start, State &goal_out, map<string, ParentInfo> &parent_map, int &expanded_nodes, int node_limit = BFS_NODE_LIMIT)
{
    priority_queue<ANode, vector<ANode>, ACmp> pq;
    unordered_map<string, int> bestg;
    parent_map.clear();
    expanded_nodes = 0;

    auto initial_dv = count_dest_and_weight_violations(start);
    int h0 = initial_dv.first * 5 + initial_dv.second * 2 + (N - __builtin_popcount(start.loaded_mask));
    pq.push({start, 0, h0});
    bestg[state_key(start)] = 0;
    parent_map[state_key(start)] = {"", {-1, -1}, 0};

    while (!pq.empty())
    {
        auto top = pq.top();
        pq.pop();
        State cur = top.st;
        string ck = state_key(cur);
        int curg = top.g;
        // skip if we have a better g recorded
        if (bestg.count(ck) && curg > bestg[ck])
            continue;
        expanded_nodes++;
        if (expanded_nodes > node_limit)
            return false;
        if ((int)__builtin_popcount(cur.loaded_mask) == N)
        {
            goal_out = cur;
            return true;
        }

        auto acts = possible_actions_hard(cur);
        for (const auto &a : acts)
        {
            State nxt = cur;
            nxt.stacks[a.stack_id].push_back(a.cid);
            nxt.loaded_mask |= (1u << a.cid);
            int newg = curg + LOAD_COST;
            string k = state_key(nxt);
            if (bestg.count(k) && newg >= bestg[k])
                continue;
            bestg[k] = newg;
            // heuristic: penalize destination blocks more, weight violations somewhat, and remaining loads
            auto dv = count_dest_and_weight_violations(nxt);
            int hn = dv.first * 5 + dv.second * 2 + (N - __builtin_popcount(nxt.loaded_mask));
            parent_map[k] = {ck, a, newg};
            pq.push({nxt, newg, hn});
        }
    }
    return false;
}

// ---------- reconstruct path ----------
vector<Action> reconstruct_actions(const map<string, ParentInfo> &parent_map, const string &goal_key)
{
    vector<Action> seq;
    string cur = goal_key;
    if (!parent_map.count(cur))
        return seq;
    while (!parent_map.at(cur).parent_key.empty())
    {
        seq.push_back(parent_map.at(cur).action);
        cur = parent_map.at(cur).parent_key;
    }
    reverse(seq.begin(), seq.end());
    return seq;
}

// ---------- run & reporting ----------
void run_and_report(DualOut &out, const string &name,
                    function<bool(State &, State &, map<string, ParentInfo> &, int &)> solver,
                    State &start)
{
    out << "\n=== Running " << name << " ===\n";
    State goal;
    map<string, ParentInfo> parent_map;
    int expanded = 0;
    State start_copy = start;
    auto t0 = Clock::now();
    bool ok = solver(start_copy, goal, parent_map, expanded);
    auto t1 = Clock::now();
    double ms = chrono::duration<double, milli>(t1 - t0).count();
    if (!ok)
    {
        out << name << " : No solution found within node limit or search exhausted.\n";
        out << "Nodes expanded: " << expanded << "\n";
        out << "Time (ms): " << ms << "\n";
        return;
    }
    out << "Solution found.\n";
    out << "Nodes expanded: " << expanded << "\n";
    out << "Time (ms): " << ms << "\n";
    int loads = __builtin_popcount(goal.loaded_mask);
    // report violations (should be zero for balance and weight because we enforce them; dest-blocks may exist)
    auto dv = count_dest_and_weight_violations(goal);
    int balv = count_balance_violation(goal);
    int total_viol = dv.first + dv.second + balv;
    int total_cost = loads * LOAD_COST + total_viol * PENALTY_UNIT;
    out << "Loads performed: " << loads << " (each load cost=" << LOAD_COST << ")\n";
    out << "Destination blocks: " << dv.first << "\n";
    out << "Weight inversions: " << dv.second << "\n";
    out << "Balance violations: " << balv << " (should be 0 since balance is hard)\n";
    out << "Total violations (for reporting): " << total_viol << " (penalty each = " << PENALTY_UNIT << ")\n";
    out << "Total cost = " << total_cost << "\n";

    string gkey = state_key(goal);
    auto actions = reconstruct_actions(parent_map, gkey);
    out << "Load sequence (cid weight dest -> stack):\n";
    int step = 0;
    State replay;
    replay.stacks.assign(NUM_STACKS, {});
    for (auto &a : actions)
    {
        ++step;
        replay.stacks[a.stack_id].push_back(a.cid);
        replay.loaded_mask |= (1u << a.cid);
        out << step << ". cid=" << a.cid << " (w=" << containers[a.cid].weight << " d=" << containers[a.cid].dest << ") -> stack " << a.stack_id << "\n";
    }
    out << "Final stacks:\n";
    for (int s = 0; s < NUM_STACKS; ++s)
    {
        out << "Stack " << s << ": ";
        for (int c : goal.stacks[s])
            out << c << "(" << containers[c].weight << "," << containers[c].dest << ") ";
        out << "\n";
    }
    out << "Violation details:\n";
    describe_violations(goal, out);
}

// ---------- main ----------
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    DualOut dout("output.txt");
    dout << "Container Loading Problem Run\n";

    ifstream fin("input.txt");
    if (!fin.is_open())
    {
        dout << "Error: input.txt not found in current directory.\n";
        return 1;
    }

    // input format:
    // <num_stacks> <max_height> <balance_limit>   (num_stacks ignored; we fixed to 4)
    // <num_containers>
    // <weight_0> <dest_0>
    // ...
    int input_num_stacks;
    fin >> input_num_stacks >> MAX_HEIGHT >> BALANCE_LIMIT;
    fin >> N;
    containers.assign(N, {0, 0});
    dout << "num_stacks=" << NUM_STACKS << " max_height=" << MAX_HEIGHT << " balance_limit=" << BALANCE_LIMIT << "\n";
    dout << "n_containers=" << N << "\n";
    dout << "Containers listing (cid weight dest):\n";
    for (int i = 0; i < N; ++i)
    {
        fin >> containers[i].weight >> containers[i].dest;
        dout << i << " " << containers[i].weight << " " << containers[i].dest << "\n";
    }
    fin.close();

    if (N > NUM_STACKS * MAX_HEIGHT)
    {
        dout << "Error: too many containers (" << N << ") for ship capacity " << NUM_STACKS * MAX_HEIGHT << "\n";
        return 1;
    }

    State start;
    start.stacks.assign(NUM_STACKS, {});
    start.loaded_mask = 0;
    start.g_cost = 0;

    // wrap functions to match run_and_report signature
    auto bfs_wrapper = [&](State &s, State &g, map<string, ParentInfo> &pm, int &expanded)
    {
        return BFS_search(s, g, pm, expanded, BFS_NODE_LIMIT);
    };
    auto greedy_wrapper = [&](State &s, State &g, map<string, ParentInfo> &pm, int &expanded)
    {
        return Greedy_search(s, g, pm, expanded, BFS_NODE_LIMIT);
    };
    auto astar_wrapper = [&](State &s, State &g, map<string, ParentInfo> &pm, int &expanded)
    {
        return Astar_search(s, g, pm, expanded, BFS_NODE_LIMIT);
    };

    run_and_report(dout, "BFS (hard constraints, full search limited by node limit)", bfs_wrapper, start);
    run_and_report(dout, "Greedy Best-First (hard constraints, heuristic)", greedy_wrapper, start);
    run_and_report(dout, "A* (hard constraints, improved heuristic)", astar_wrapper, start);

    dout << "\nEnd of run.\nDone. Results printed to console and output.txt\n";
    return 0;
}
