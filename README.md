# Sahayatri

Sahayatri is a small C++ demonstration of flood-connectivity mapping and shortest-path algorithms, based on the code examples developed in this tracker.

**Planning aid only — NOT a flood forecast, warning system, or evacuation authority.** The grid in the demo is synthetic and must not be interpreted as real terrain or local flood risk. Always follow official warnings and instructions from Nepal's Department of Hydrology and Meteorology (DHM) and National Disaster Risk Reduction and Management Authority (NDRRMA), as well as local authorities. Do not use this demo to decide whether or when to evacuate.

## Included demos

- `src/flood_grid_demo.cpp`: generates a synthetic 10×10 elevation grid, finds cells connected to the bottom edge that are at or below a selected water level, prints flood counts and a map, and demonstrates a least-cost path through cells not marked flooded.
- `src/weighted_graph_demo.cpp`: runs Dijkstra's algorithm on a small undirected weighted graph.

These examples use simplified assumptions and are for learning and software development only. They are not calibrated against a digital elevation model, hydrological data, or validated local survey data.

## Build and run

Requires a C++17-compatible compiler.

```sh
g++ -std=c++17 -O2 -Wall -Wextra -pedantic src/flood_grid_demo.cpp -o flood_grid_demo
./flood_grid_demo

g++ -std=c++17 -O2 -Wall -Wextra -pedantic src/weighted_graph_demo.cpp -o weighted_graph_demo
./weighted_graph_demo
```
