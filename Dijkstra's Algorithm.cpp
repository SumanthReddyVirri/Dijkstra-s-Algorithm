#include <iostream>
#include <vector>
#include <limits>
#include <set>
#include <algorithm>

const int INF = std::numeric_limits<int>::max();

void Dijkstra(const std::vector<std::vector<int>>& graph, int source, int target) {
    int V = graph.size();
    std::vector<int> dist(V, INF);
    std::vector<int> prev(V, -1);
    std::set<std::pair<int, int>> queue;

    dist[source] = 0;
    queue.insert({0, source});

    while (!queue.empty()) {
        int u = queue.begin()->second;
        queue.erase(queue.begin());

        if (u == target) break;

        for (int v = 0; v < V; ++v) {
            if (graph[u][v] && dist[v] > dist[u] + graph[u][v]) {
                queue.erase({dist[v], v});
                dist[v] = dist[u] + graph[u][v];
                prev[v] = u;
                queue.insert({dist[v], v});
            }
        }
    }

    if (dist[target] == INF) {
        std::cout << "There is no path from " << source << " to " << target << std::endl;
    } else {
        std::vector<int> path;
        for (int at = target; at != -1; at = prev[at]) {
            path.push_back(at);
        }
        std::reverse(path.begin(), path.end());

        std::cout << "The shortest path from " << source << " to " << target << " is: ";
        for (int v : path) {
            std::cout << v << " ";
        }
        std::cout << "\nThe path cost is: " << dist[target] << std::endl;
    }
}

int main() {
    int V;
    std::cout << "Enter the number of vertices: ";
    std::cin >> V;

    std::vector<std::vector<int>> graph(V, std::vector<int>(V));

    std::cout << "Enter the adjacency matrix:\n";
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            std::cin >> graph[i][j];
            if (graph[i][j] == 0 && i != j) {
                graph[i][j] = INF;
            }
        }
    }

    int source, target;
    std::cout << "Enter the source node: ";
    std::cin >> source;
    std::cout << "Enter the target node: ";
    std::cin >> target;

    Dijkstra(graph, source, target);

    return 0;
}
