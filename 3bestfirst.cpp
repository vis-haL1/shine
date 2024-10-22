#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

void addEdge(vector<vector<int>>& adjList, int start, int end) {
    adjList[start].push_back(end);
    adjList[end].push_back(start);
}

bool DLS(const vector<vector<int>>& adjList, int node, int goal, int limit, unordered_set<int>& visited) {
    if (node == goal) {
        return true;
    }
    if (limit <= 0) {
        return false;
    }

    visited.insert(node);

    for (int neighbor : adjList[node]) {
        if (visited.find(neighbor) == visited.end()) {
            if (DLS(adjList, neighbor, goal, limit- 1, visited)) {
                return true;
            }
        }
    }

    visited.erase(node);
    return false;
}

int IDDFS(const vector<vector<int>>& adjList, int start, int goal, int maxDepth) {
    for (int depth = 0; depth <= maxDepth; depth++) {
        unordered_set<int> visited;
        if (DLS(adjList, start, goal, depth, visited)) {
            cout << "Goal found at depth: " << depth << endl;
            return depth;
        }
        
    }
    return -1;
}

int main() {
    int vertices = 11;
    int edges = 11;

    vector<vector<int>> adjList(vertices);

    addEdge(adjList, 0, 1); 
    addEdge(adjList, 0, 2);
    addEdge(adjList, 0, 3);
    addEdge(adjList, 1, 5);
    addEdge(adjList, 1, 7);
    addEdge(adjList, 2, 5);
    addEdge(adjList, 2, 4);
    addEdge(adjList, 3, 4);
    addEdge(adjList, 3, 9);
    addEdge(adjList, 7, 8);
    addEdge(adjList, 5, 6);
    addEdge(adjList, 4, 6);
    addEdge(adjList, 9, 10);
   

    int start = 0;
    int goal = 10;
    int maxDepth = 10;
    int result = IDDFS(adjList, start, goal, maxDepth);

    if (result == -1) {
        cout << "Goal not reachable within depth limit" << endl;
    }

    return 0;
}