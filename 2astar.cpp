#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>

using namespace std;

unordered_map<char, vector<pair<char, int>>> Graph_nodes = {
    {'A', {{'B', 1}, {'C', 4}}},
    {'B', {{'A', 1}, {'D', 2}, {'C', 2}}},
    {'C', {{'A', 4}, {'B', 2}, {'D', 3}}},
    {'D', {{'B', 2}, {'C', 3}, {'E', 1}}},
    {'E', {{'D', 1}, {'F', 5}}},
    {'F', {{'E', 5}, {'G', 1}}},
    {'G', {{'F', 1}}}
};

double h(char n) {
    unordered_map<char, double> H_dist = {
        {'A', 7}, {'B', 6}, {'C', 2}, {'D', 1}, {'E', 3}, {'F', 2}, {'G', 0}
    };
    return H_dist[n];
}

vector<pair<char, int>> get_neighbors(char v) {
    return Graph_nodes.count(v) ? Graph_nodes[v] : vector<pair<char, int>>{};
}

vector<char> aStarAlgo(char start_node, char stop_node) {
    unordered_set<char> open_set;
    unordered_set<char> closed_set;
    unordered_map<char, double> g;
    unordered_map<char, char> parents;

    g[start_node] = 0;
    parents[start_node] = start_node;
    open_set.insert(start_node);

    while (!open_set.empty()) {
        char n = *min_element(open_set.begin(), open_set.end(), [&](char a, char b) {
            return g[a] + h(a) < g[b] + h(b);
        });

        if (n == stop_node) {
            vector<char> path;
            while (parents[n] != n) {
                path.push_back(n);
                n = parents[n];
            }
            path.push_back(start_node);
            reverse(path.begin(), path.end());
            return path;
        }

        open_set.erase(n);
        closed_set.insert(n);

        for (const auto& neighbor : get_neighbors(n)) {
            char m = neighbor.first;
            int weight = neighbor.second;

            if (closed_set.count(m) == 0) {
                double tentative_g = g[n] + weight;

                if (open_set.count(m) == 0) {
                    open_set.insert(m);
                    g[m] = tentative_g;
                    parents[m] = n;
                } else if (tentative_g < g[m]) {
                    g[m] = tentative_g;
                    parents[m] = n;
                }
            }
        }
    }

    cout << "Path does not exist!" << endl;
    return {};
}

int main() {
    vector<char> path = aStarAlgo('A', 'G');
    if (!path.empty()) {
        cout << "Path found: ";
        for (char node : path) {
            cout << node << " ";
        }
        cout << endl;
    }
    return 0;
}
