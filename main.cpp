#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <queue>
#include <fstream>

using Graph = std::unordered_map<int, std::unordered_set<int>>;

void add_edge(Graph& graph, const int from, const int to);
std::vector<int> find_shortest_path(const Graph& graph, const int start, const int v);

int main() {
    std::ifstream file("graph.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    int v, e;
    file >> v >> e;

    if (v <= 0 || e <= 0) {
        std::cout << "Incorrect input" << std::endl;
        return 1;
    }

    Graph graph;
    int a, b;

    for (size_t i = 0; i < e; i++) {
        file >> a >> b;
        add_edge(graph, a, b);
    }

    int start;
    file >> start;
    file.close();

    std::vector<int> dist = find_shortest_path(graph, start, v);
    for (size_t i = 0; i < v; i++) {
        std::cout << dist[i] << '\n' << std::endl;
    }

    return 0;
}

void add_edge(Graph& graph, const int from, const int to) {
    if (from != to) {
        graph[from].insert(to);
        graph[to].insert(from);
    }
}

std::vector<int> find_shortest_path(const Graph& graph, const int start, const int v) {
    
    std::vector<int> dist(v, -1);

    std::queue<int> q;

    dist[start] = 0;
    q.push(start);

    if (v != 1) {
        while (!q.empty()) {
            int curr = q.front();
            q.pop();

            for (int neighbor : graph.at(curr)) {
                if (dist[neighbor] == -1) { 
                    dist[neighbor] = dist[curr] + 1;
                    q.push(neighbor);
                }
            }
        }
    }

    return dist;
}