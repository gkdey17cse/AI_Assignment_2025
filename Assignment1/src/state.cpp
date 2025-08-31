#include "state.h"
#include <queue>
#include <algorithm>
#include <sstream>
#include <cmath>

State::State(int bays, int max_diff, int height, const std::vector<Container> &conts)
    : num_bays(bays), max_weight_diff(max_diff), max_height(height), containers(conts),
      cost(0), parent_index(-1), last_action(-1), port_weight(0), starboard_weight(0)
{
    // Initialize empty stacks for both sides
    stacks.resize(2); // 0 = port, 1 = starboard
    for (int side = 0; side < 2; side++)
    {
        stacks[side].resize(num_bays);
    }
}

State::State(const State &other)
    : num_bays(other.num_bays), max_weight_diff(other.max_weight_diff), max_height(other.max_height),
      stacks(other.stacks), containers(other.containers),
      cost(other.cost), parent_index(other.parent_index), last_action(other.last_action),
      port_weight(other.port_weight), starboard_weight(other.starboard_weight)
{
}

bool State::isGoal() const
{
    // All containers are loaded
    for (size_t i = 0; i < containers.size(); i++)
    {
        if (!containers[i].loaded)
            return false;
    }
    return true;
}

std::vector<State> State::getSuccessors() const
{
    std::vector<State> successors;

    // For each unloaded container
    for (size_t i = 0; i < containers.size(); i++)
    {
        if (containers[i].loaded)
            continue;

        // First, try to fill empty bays (prioritize better distribution)
        for (int side = 0; side < 2; side++)
        {
            for (int bay = 0; bay < num_bays; bay++)
            {
                // Check if this bay is empty - prioritize filling empty bays
                if (stacks[side][bay].empty())
                {
                    State new_state = *this;
                    new_state.loadContainer(i, side, bay);
                    new_state.setParentIndex(-1);
                    new_state.setLastAction(i * 100 + side * 10 + bay);

                    if (new_state.isValid())
                    {
                        successors.push_back(new_state);
                    }
                }
            }
        }

        // Then try non-empty bays
        for (int side = 0; side < 2; side++)
        {
            for (int bay = 0; bay < num_bays; bay++)
            {
                // Skip empty bays (already handled above) and full bays
                if (stacks[side][bay].empty() || stacks[side][bay].size() >= static_cast<size_t>(max_height))
                    continue;

                State new_state = *this;
                new_state.loadContainer(i, side, bay);
                new_state.setParentIndex(-1);
                new_state.setLastAction(i * 100 + side * 10 + bay);

                if (new_state.isValid())
                {
                    successors.push_back(new_state);
                }
            }
        }
    }

    return successors;
}

void State::loadContainer(int container_id, int side, int bay)
{
    if (container_id < 0 || container_id >= static_cast<int>(containers.size()))
        return;
    if (side < 0 || side > 1)
        return;
    if (bay < 0 || bay >= num_bays)
        return;

    // Mark container as loaded
    containers[container_id].loaded = true;

    // Add container to the stack
    stacks[side][bay].push_back(containers[container_id]);

    // Update weights
    if (side == 0)
    {
        port_weight += containers[container_id].weight;
    }
    else
    {
        starboard_weight += containers[container_id].weight;
    }

    // Update cost (1 for loading, plus penalties for violations)
    cost += 1;
    int violations = calculateDestinationViolations() + calculateWeightDistributionScore();
    cost += violations * 2; // 2 units penalty per violation
}

bool State::isValid() const
{
    // Check weight difference constraint
    int weight_diff = std::abs(port_weight - starboard_weight);
    if (weight_diff > max_weight_diff)
    {
        return false;
    }

    return true;
}

int State::calculateWeightDifference() const
{
    return std::abs(port_weight - starboard_weight);
}

int State::calculateDestinationViolations() const
{
    int violations = 0;

    // Check each stack for destination violations
    for (int side = 0; side < 2; side++)
    {
        for (int bay = 0; bay < num_bays; bay++)
        {
            const auto &stack = stacks[side][bay];
            for (size_t i = 1; i < stack.size(); i++)
            {
                // If a container above has an earlier destination than one below, it's a violation
                if (stack[i].destination < stack[i - 1].destination)
                {
                    violations++;
                }
            }
        }
    }

    return violations;
}

int State::calculateWeightDistributionScore() const
{
    int score = 0;

    // Check each stack for weight distribution violations
    for (int side = 0; side < 2; side++)
    {
        for (int bay = 0; bay < num_bays; bay++)
        {
            const auto &stack = stacks[side][bay];
            for (size_t i = 1; i < stack.size(); i++)
            {
                // If a container above is heavier than one below, it's a violation
                if (stack[i].weight > stack[i - 1].weight)
                {
                    score++;
                }
            }
        }
    }

    return score;
}

std::string State::toString() const
{
    std::stringstream ss;

    ss << "Cost: " << cost << " (Loading: " << (cost - 2 * (calculateDestinationViolations() + calculateWeightDistributionScore()))
       << ", Penalty: " << 2 * (calculateDestinationViolations() + calculateWeightDistributionScore()) << ")\n";

    ss << "Weight Difference: " << calculateWeightDifference() << " (Max: " << max_weight_diff << ")\n";
    ss << "Destination Violations: " << calculateDestinationViolations() << "\n";
    ss << "Weight Distribution Violations: " << calculateWeightDistributionScore() << "\n\n";

    ss << "Port side:\n";
    for (int bay = 0; bay < num_bays; bay++)
    {
        ss << "Bay " << bay << ": ";
        for (const auto &container : stacks[0][bay])
        {
            ss << "(" << container.weight << "," << container.destination << ") ";
        }
        ss << "\n";
    }

    ss << "\nStarboard side:\n";
    for (int bay = 0; bay < num_bays; bay++)
    {
        ss << "Bay " << bay << ": ";
        for (const auto &container : stacks[1][bay])
        {
            ss << "(" << container.weight << "," << container.destination << ") ";
        }
        ss << "\n";
    }

    return ss.str();
}

int State::getHeuristic() const
{
    int unloaded = 0;
    for (const auto &container : containers)
    {
        if (!container.loaded)
            unloaded++;
    }

    // Strong penalty for empty bays when containers are available
    int empty_bay_penalty = 0;
    if (unloaded > 0)
    {
        for (int side = 0; side < 2; side++)
        {
            for (int bay = 0; bay < num_bays; bay++)
            {
                if (stacks[side][bay].empty())
                {
                    empty_bay_penalty += 5; // Strong penalty for empty bays
                }
            }
        }
    }

    return unloaded + calculateDestinationViolations() +
           calculateWeightDistributionScore() + empty_bay_penalty;
}