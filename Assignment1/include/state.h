#ifndef STATE_H
#define STATE_H

#include <vector>
#include <string>
#include <iostream>

struct Container
{
    int id;
    int weight;
    int destination;
    bool loaded;

    Container(int i, int w, int d) : id(i), weight(w), destination(d), loaded(false) {}
};

class State
{
private:
    int num_bays;
    int max_weight_diff;
    int max_height;
    std::vector<std::vector<std::vector<Container>>> stacks; // [side][bay][tier]
    std::vector<Container> containers;
    int cost;
    int parent_index;
    int last_action; // container_id, side, bay

    int port_weight;
    int starboard_weight;

public:
    State(int bays, int max_diff, int height, const std::vector<Container> &conts);
    State(const State &other);

    bool isGoal() const;
    std::vector<State> getSuccessors() const;
    int getCost() const { return cost; }
    int getHeuristic() const;
    bool isValid() const;

    void loadContainer(int container_id, int side, int bay);
    bool isContainerLoaded(int container_id) const;

    int calculateWeightDifference() const;
    int calculateDestinationViolations() const;
    int calculateWeightDistributionScore() const;

    std::string toString() const;

    // Getters and Setters
    int getParentIndex() const { return parent_index; }
    void setParentIndex(int index) { parent_index = index; }
    int getLastAction() const { return last_action; }
    void setLastAction(int action) { last_action = action; }
    int getNumBays() const { return num_bays; }
    int getMaxHeight() const { return max_height; }
    const std::vector<Container> &getContainers() const { return containers; }
    size_t getContainersSize() const { return containers.size(); }
    size_t getStackSize(int side, int bay) const { return stacks[side][bay].size(); }
};

#endif