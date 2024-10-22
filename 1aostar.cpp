#include <iostream>
#include <vector>

#define MAX 10
#define INF 9999

using namespace std;

int cost[MAX][MAX], n, goal[MAX], heuristic[MAX], solution[MAX];

int minCost(int parent) {
    int min = INF;
    for (int i = 0; i < n; i++) {
        if (cost[parent][i] != INF && heuristic[i] < min) {
            min = heuristic[i];
        }
    }
    return min;
}

void AOStar(int node) {
    if (goal[node]) {
        solution[node] = 1;
        return;
    }

    int minSubCost = minCost(node);
    cout << "Expanding node: " << node << " with cost " << minSubCost << endl;

    for (int i = 0; i < n; i++) {
        if (cost[node][i] != INF && heuristic[i] == minSubCost) {
            AOStar(i);
            if (solution[i]) {
                solution[node] = 1;
                break;
            }
        }
    }
}

int main() {
    n = 6;

    int tempCost[MAX][MAX] = {
        {0, 1, INF, 4, INF, INF},
        {INF, 0, 2, INF, 6, INF},
        {INF, INF, 0, 3, INF, 1},
        {INF, INF, INF, 0, 2, 5},
        {INF, INF, INF, INF, 0, 1},
        {INF, INF, INF, INF, INF, 0}
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cost[i][j] = tempCost[i][j];
        }
    }

    int tempHeuristic[MAX] = {8, 6, 3, 1, 0, 2};
    for (int i = 0; i < n; i++) {
        heuristic[i] = tempHeuristic[i];
    }

    int tempGoal[MAX] = {0, 0, 0, 0, 1, 0};
    for (int i = 0; i < n; i++) {
        goal[i] = tempGoal[i];
    }

    int start = 0;

    AOStar(start);

    if (solution[start])
        cout << "Solution found." << endl;
    else
        cout << "No solution found." << endl;

    return 0;
}
