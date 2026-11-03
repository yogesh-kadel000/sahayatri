#include <iostream>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

namespace {
struct Edge {
    int to;
    int weight;
};

constexpr int kInf = 1'000'000'000;
} // namespace

int main() {
    constexpr int node_count = 6;
    std::vector<std::vector<Edge>> adjacency(node_count);
    const std::vector<std::tuple<int, int, int>> edges = {
        {0, 1, 7}, {0, 2, 9}, {0, 5, 14}, {1, 2, 10}, {1, 3, 15},
        {2, 3, 11}, {2, 5, 2}, {3, 4, 6}, {4, 5, 9}};

    for (const auto& [u, v, weight] : edges) {
        adjacency[u].push_back({v, weight});
        adjacency[v].push_back({u, weight});
    }

    std::vector<int> distance(node_count, kInf);
    using State = std::pair<int, int>; // distance, node
    std::priority_queue<State, std::vector<State>, std::greater<State>> queue;

    constexpr int start = 0;
    distance[start] = 0;
    queue.push({0, start});

    while (!queue.empty()) {
        const auto [current_distance, u] = queue.top();
        queue.pop();
        if (current_distance != distance[u]) {
            continue;
        }

        for (const Edge& edge : adjacency[u]) {
            const int candidate = current_distance + edge.weight;
            if (candidate < distance[edge.to]) {
                distance[edge.to] = candidate;
                queue.push({candidate, edge.to});
            }
        }
    }

    std::cout << "Shortest distances from node " << start << ":\n";
    for (int node = 0; node < node_count; ++node) {
        std::cout << node << ' ' << distance[node] << '\n';
    }
}
