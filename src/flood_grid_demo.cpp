#include <algorithm>
#include <array>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

namespace {
constexpr int kRows = 10;
constexpr int kCols = 10;
constexpr int kInf = 1'000'000'000;
using Grid = std::array<std::array<int, kCols>, kRows>;
using Mask = std::array<std::array<bool, kCols>, kRows>;

constexpr int kDr[] = {-1, 1, 0, 0};
constexpr int kDc[] = {0, 0, -1, 1};

Grid make_synthetic_grid() {
    Grid heights{};
    for (int r = 0; r < kRows; ++r) {
        for (int c = 0; c < kCols; ++c) {
            heights[r][c] = (kRows - 1 - r) * 10 + c;
        }
    }

    // Demonstration-only depression; these values are not real terrain data.
    heights[3][4] = 5;
    return heights;
}

Mask find_flooded_cells(const Grid& heights, int level) {
    Mask flooded{};
    std::queue<std::pair<int, int>> queue;

    // Seed the bottom edge, representing a hypothetical water source.
    for (int c = 0; c < kCols; ++c) {
        if (heights[kRows - 1][c] <= level) {
            flooded[kRows - 1][c] = true;
            queue.push({kRows - 1, c});
        }
    }

    while (!queue.empty()) {
        const auto [r, c] = queue.front();
        queue.pop();

        for (int direction = 0; direction < 4; ++direction) {
            const int nr = r + kDr[direction];
            const int nc = c + kDc[direction];
            if (nr >= 0 && nr < kRows && nc >= 0 && nc < kCols &&
                !flooded[nr][nc] && heights[nr][nc] <= level) {
                flooded[nr][nc] = true;
                queue.push({nr, nc});
            }
        }
    }
    return flooded;
}

int count_flooded(const Mask& flooded) {
    int count = 0;
    for (const auto& row : flooded) {
        for (bool cell : row) {
            count += cell ? 1 : 0;
        }
    }
    return count;
}

void print_map(const Mask& flooded) {
    for (const auto& row : flooded) {
        for (bool cell : row) {
            std::cout << (cell ? '#' : '.');
        }
        std::cout << '\n';
    }
}

int least_cost_to_top(const Grid& heights, const Mask& flooded,
                      int start_r, int start_c) {
    if (start_r < 0 || start_r >= kRows || start_c < 0 || start_c >= kCols ||
        flooded[start_r][start_c]) {
        return kInf;
    }

    std::array<std::array<int, kCols>, kRows> distance{};
    for (auto& row : distance) {
        row.fill(kInf);
    }

    using State = std::tuple<int, int, int>; // cost, row, column
    std::priority_queue<State, std::vector<State>, std::greater<State>> queue;
    distance[start_r][start_c] = 0;
    queue.push({0, start_r, start_c});

    while (!queue.empty()) {
        const auto [cost, r, c] = queue.top();
        queue.pop();
        if (cost != distance[r][c]) {
            continue;
        }
        if (r == 0) {
            return cost;
        }

        for (int direction = 0; direction < 4; ++direction) {
            const int nr = r + kDr[direction];
            const int nc = c + kDc[direction];
            if (nr < 0 || nr >= kRows || nc < 0 || nc >= kCols ||
                flooded[nr][nc]) {
                continue;
            }

            const int move_cost = 1 + std::max(0, heights[nr][nc] - heights[r][c]);
            if (cost + move_cost < distance[nr][nc]) {
                distance[nr][nc] = cost + move_cost;
                queue.push({distance[nr][nc], nr, nc});
            }
        }
    }
    return kInf;
}
} // namespace

int main() {
    const Grid heights = make_synthetic_grid();

    std::cout << "Synthetic flood-connected cell counts:\n";
    for (int level : {5, 15, 25, 35, 45}) {
        std::cout << "level " << level << ": "
                  << count_flooded(find_flooded_cells(heights, level)) << '\n';
    }

    constexpr int level = 25;
    const Mask flooded = find_flooded_cells(heights, level);
    std::cout << "\nSynthetic map at level " << level
              << " (# = connected flooded cell, . = other cell):\n";
    print_map(flooded);

    const int cost = least_cost_to_top(heights, flooded, 8, 9);
    if (cost == kInf) {
        std::cout << "No dry path from the demonstration start to the top row.\n";
    } else {
        std::cout << "Demonstration least path cost to top row: " << cost << '\n';
    }
    std::cout << "This synthetic output is not a forecast or evacuation guidance.\n";
}
