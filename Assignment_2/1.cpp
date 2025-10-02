#include <iostream>
#include <vector>
using namespace std;

struct Position
{
    int x, y;
    Position(int a = 0, int b = 0) : x(a), y(b) {}
    bool operator==(const Position &other) const
    {
        return x == other.x && y == other.y;
    }
};

struct Player
{
    Position x, y;
    bool alive;
    bool carryingTreasure;
    
};

class GameState
{
public:
    int rows, cols;
    vector<Player> teamA, teamB;
    Position treasureA, treasureB;
    bool turnBased;

    GameState(int r, int c, bool turnBased)
    {
        rows = r;
        cols = c;
        this->turnBased = turnBased;
        reset();
    }
    void reset()
    {
        teamA.clear();
        teamB.clear();
        // placing Team A left side
        teamA.push_back(Player(0, 1));
    }
};
