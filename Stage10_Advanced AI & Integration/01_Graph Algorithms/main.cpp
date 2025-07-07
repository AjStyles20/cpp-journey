#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
#include <cmath>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Graph node structure
struct Node {
    int id;
    double x, y; // Coordinates for heuristic calculation
    Node(int id, double x, double y) : id(id), x(x), y(y) {}
};

// Graph edge structure
struct Edge {
    int target;
    double weight;
    Edge(int target, double weight) : target(target), weight(weight) {}
};

// Graph class
class WeightedGraph {
private:
    vector<Node> nodes;
    vector<vector<Edge>> adjacencyList;
    
public:
    WeightedGraph() = default;
    
    void addNode(int id, double x, double y) {
        nodes.emplace_back(id, x, y);
        adjacencyList.resize(nodes.size());
    }
    
    void addEdge(int from, int to, double weight) {
        adjacencyList[from].emplace_back(to, weight);
        adjacencyList[to].emplace_back(from, weight); // Undirected graph
    }
    
    const vector<Node>& getNodes() const { return nodes; }
    const vector<vector<Edge>>& getAdjacencyList() const { return adjacencyList; }
    
    // Find node by ID (simple linear search for small graphs)
    const Node& getNode(int id) const {
        for (const auto& node : nodes) {
            if (node.id == id) return node;
        }
        throw runtime_error("Node not found");
    }
};

// Path result structure
struct PathResult {
    vector<int> path;
    double distance;
    double timeMs;
    
    PathResult() : distance(numeric_limits<double>::max()), timeMs(0) {}
};

// Dijkstra's algorithm implementation
PathResult dijkstra(const WeightedGraph& graph, int start, int goal) {
    PathResult result;
    auto startTime = high_resolution_clock::now();
    
    const auto& nodes = graph.getNodes();
    const auto& adj = graph.getAdjacencyList();
    
    // Priority queue: (distance, node)
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    unordered_map<int, double> dist;
    unordered_map<int, int> prev;
    
    // Initialize distances
    for (const auto& node : nodes) {
        dist[node.id] = numeric_limits<double>::max();
    }
    dist[start] = 0;
    pq.emplace(0, start);
    
    while (!pq.empty()) {
        auto top = pq.top();
        double currentDist = top.first;
        int u = top.second;
        pq.pop();

        // Early exit if we reach the goal
        if (u == goal) break;

        // Skip if we found a better path already
        if (currentDist > dist[u]) continue;
        
        // Explore neighbors
        for (const auto& edge : adj[u]) {
            int v = edge.target;
            double alt = dist[u] + edge.weight;
            
            if (alt < dist[v]) {
                dist[v] = alt;
                prev[v] = u;
                pq.emplace(alt, v);
            }
        }
    }
    
    // Reconstruct path if we found one
    if (dist[goal] < numeric_limits<double>::max()) {
        result.distance = dist[goal];
        
        // Backtrack from goal to start
        int current = goal;
        while (current != start) {
            result.path.push_back(current);
            current = prev[current];
        }
        result.path.push_back(start);
        reverse(result.path.begin(), result.path.end());
    }
    
    auto endTime = high_resolution_clock::now();
    result.timeMs = duration_cast<microseconds>(endTime - startTime).count() / 1000.0;
    
    return result;
}

// A* algorithm implementation
PathResult aStar(const WeightedGraph& graph, int start, int goal) {
    PathResult result;
    auto startTime = high_resolution_clock::now();
    
    const auto& nodes = graph.getNodes();
    const auto& adj = graph.getAdjacencyList();
    const Node& goalNode = graph.getNode(goal);
    
    // Heuristic function (Euclidean distance)
    auto heuristic = [&](int nodeId) {
        const Node& node = graph.getNode(nodeId);
        double dx = node.x - goalNode.x;
        double dy = node.y - goalNode.y;
        return sqrt(dx*dx + dy*dy);
    };
    
    // Priority queue: (f_score, node)
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    unordered_map<int, double> gScore;
    unordered_map<int, double> fScore;
    unordered_map<int, int> prev;
    
    // Initialize scores
    for (const auto& node : nodes) {
        gScore[node.id] = numeric_limits<double>::max();
        fScore[node.id] = numeric_limits<double>::max();
    }
    
    gScore[start] = 0;
    fScore[start] = heuristic(start);
    pq.emplace(fScore[start], start);
    
    while (!pq.empty()) {
        auto top = pq.top();
        double currentFScore = top.first;
        int u = top.second;
        pq.pop();

        // Early exit if we reach the goal
        if (u == goal) break;

        // Skip if we found a better path already
        if (currentFScore > fScore[u]) continue;
        
        // Explore neighbors
        for (const auto& edge : adj[u]) {
            int v = edge.target;
            double tentativeGScore = gScore[u] + edge.weight;
            
            if (tentativeGScore < gScore[v]) {
                prev[v] = u;
                gScore[v] = tentativeGScore;
                fScore[v] = gScore[v] + heuristic(v);
                pq.emplace(fScore[v], v);
            }
        }
    }
    
    // Reconstruct path if we found one
    if (gScore[goal] < numeric_limits<double>::max()) {
        result.distance = gScore[goal];
        
        // Backtrack from goal to start
        int current = goal;
        while (current != start) {
            result.path.push_back(current);
            current = prev[current];
        }
        result.path.push_back(start);
        reverse(result.path.begin(), result.path.end());
    }
    
    auto endTime = high_resolution_clock::now();
    result.timeMs = duration_cast<microseconds>(endTime - startTime).count() / 1000.0;
    
    return result;
}

// Create a sample graph (road network)
WeightedGraph createSampleGraph() {
    WeightedGraph graph;
    
    // Add nodes (ID, X, Y coordinates)
    graph.addNode(0, 0, 0);   // A
    graph.addNode(1, 2, 2);   // B
    graph.addNode(2, 4, 1);   // C
    graph.addNode(3, 6, 3);   // D
    graph.addNode(4, 8, 0);   // E
    graph.addNode(5, 5, -1);  // F
    graph.addNode(6, 3, -2);  // G
    
    // Add edges (from, to, weight)
    graph.addEdge(0, 1, 3.0);  // A-B
    graph.addEdge(0, 6, 2.5);  // A-G
    graph.addEdge(1, 2, 2.2);  // B-C
    graph.addEdge(1, 3, 4.5);  // B-D
    graph.addEdge(2, 3, 2.8);  // C-D
    graph.addEdge(2, 4, 3.7);  // C-E
    graph.addEdge(2, 5, 2.1);  // C-F
    graph.addEdge(3, 4, 3.3);  // D-E
    graph.addEdge(4, 5, 3.8);  // E-F
    graph.addEdge(5, 6, 2.9);  // F-G
    
    return graph;
}

int main() {
    WeightedGraph roadNetwork = createSampleGraph();
    
    int start = 0; // Node A
    int goal = 4;  // Node E
    
    cout << "Comparing Dijkstra and A* algorithms\n";
    cout << "Start: Node " << start << ", Goal: Node " << goal << "\n\n";
    
    // Run Dijkstra's algorithm
    PathResult dijkstraResult = dijkstra(roadNetwork, start, goal);
    cout << "Dijkstra's Algorithm:\n";
    cout << "  Path: ";
    for (int node : dijkstraResult.path) {
        cout << node << " ";
    }
    cout << "\n";
    cout << "  Distance: " << dijkstraResult.distance << "\n";
    cout << "  Time: " << dijkstraResult.timeMs << " ms\n\n";
    
    // Run A* algorithm
    PathResult aStarResult = aStar(roadNetwork, start, goal);
    cout << "A* Algorithm:\n";
    cout << "  Path: ";
    for (int node : aStarResult.path) {
        cout << node << " ";
    }
    cout << "\n";
    cout << "  Distance: " << aStarResult.distance << "\n";
    cout << "  Time: " << aStarResult.timeMs << " ms\n\n";
    
    // Comparison
    cout << "Comparison:\n";
    cout << "  Both algorithms found paths with the same distance: " 
         << (abs(dijkstraResult.distance - aStarResult.distance) < 0.001 ? "Yes" : "No") << "\n";
    cout << "  A* was " << dijkstraResult.timeMs / aStarResult.timeMs << "x faster\n";
    
    return 0;
}