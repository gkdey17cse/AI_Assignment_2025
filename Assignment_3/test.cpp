#include <vector>
using namespace std;
int tasks(int n, vector<int>& a, vector<int>& b) {
    vector<vector<int>> graph(n);
    for (int i = 0; i < a.size(); i++) {
        graph[a[i]].push_back(b[i]);
    }
    
    vector<int> visited(n, 0); // 0: unvisited, 1: visiting, 2: visited
    
    for (int i = 0; i < n; i++) {
        if (visited[i] == 0) {
            vector<int> stack;
            vector<bool> inStack(n, false);
            
            stack.push_back(i);
            while (!stack.empty()) {
                int current = stack.back();
                
                if (visited[current] == 0) {
                    visited[current] = 1;
                    inStack[current] = true;
                    
                    bool added = false;
                    for (int neighbor : graph[current]) {
                        if (visited[neighbor] == 0) {
                            stack.push_back(neighbor);
                            added = true;
                        } else if (inStack[neighbor]) {
                            return n - 1;
                        }
                    }
                    if (!added) {
                        visited[current] = 2;
                        inStack[current] = false;
                        stack.pop_back();
                    }
                } else {
                    visited[current] = 2;
                    inStack[current] = false;
                    stack.pop_back();
                }
            }
        }
    }
    
    return n;
}