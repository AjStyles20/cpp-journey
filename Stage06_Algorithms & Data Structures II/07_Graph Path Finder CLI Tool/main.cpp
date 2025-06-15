#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
#include <algorithm>
#include <sstream>
#include <chrono>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    string destination;
    int weight;
};

class Graph {
private:
    unordered_map<string, vector<Edge>> adjList;

public:
    void addEdge(const string& src, const string& dest, int weight = 1) {
        adjList[src].push_back({dest, weight});
        // For undirected graphs, add the reverse edge
        // adjList[dest].push_back({src, weight});
    }

    // Dijkstra's algorithm for weighted graphs
    vector<string> shortestPathDijkstra(const string& start, const string& end) {
        unordered_map<string, int> dist;
        unordered_map<string, string> prev;
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;

        // Initialize distances
        for (const auto& node : adjList) {
            dist[node.first] = INF;
        }
        dist[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            string current = pq.top().second;
            int currentDist = pq.top().first;
            pq.pop();

            if (current == end) break;
            if (currentDist > dist[current]) continue;

            for (const Edge& edge : adjList[current]) {
                int newDist = dist[current] + edge.weight;
                if (newDist < dist[edge.destination]) {
                    dist[edge.destination] = newDist;
                    prev[edge.destination] = current;
                    pq.push({newDist, edge.destination});
                }
            }
        }

        // Reconstruct path
        vector<string> path;
        if (dist[end] == INF) return path; // No path exists

        for (string at = end; at != start; at = prev[at]) {
            path.push_back(at);
        }
        path.push_back(start);
        reverse(path.begin(), path.end());

        return path;
    }

    // BFS for unweighted graphs
    vector<string> shortestPathBFS(const string& start, const string& end) {
        queue<string> q;
        unordered_map<string, string> prev;
        unordered_map<string, bool> visited;

        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            string current = q.front();
            q.pop();

            if (current == end) break;

            for (const Edge& edge : adjList[current]) {
                if (!visited[edge.destination]) {
                    visited[edge.destination] = true;
                    prev[edge.destination] = current;
                    q.push(edge.destination);
                }
            }
        }

        // Reconstruct path
        vector<string> path;
        if (prev.find(end) == prev.end()) return path; // No path exists

        for (string at = end; at != start; at = prev[at]) {
            path.push_back(at);
        }
        path.push_back(start);
        reverse(path.begin(), path.end());

        return path;
    }

    int getPathCost(const vector<string>& path) {
        if (path.empty()) return -1;

        int totalCost = 0;
        for (size_t i = 0; i < path.size() - 1; i++) {
            for (const Edge& edge : adjList[path[i]]) {
                if (edge.destination == path[i + 1]) {
                    totalCost += edge.weight;
                    break;
                }
            }
        }
        return totalCost;
    }
};

void showUsage() {
    cout << "Graph Path Finder CLI Tool\n"
         << "Usage: ./graph_path_finder <graph_file> <start_node> <end_node> [--weighted]\n"
         << "Options:\n"
         << "  --weighted   Use Dijkstra's algorithm (default: BFS for unweighted)\n\n"
         << "Input File Format:\n"
         << "  Each line represents an edge: source destination [weight]\n"
         << "  Example (unweighted):\n"
         << "    A B\n"
         << "    B C\n"
         << "  Example (weighted):\n"
         << "    A B 5\n"
         << "    B C 3\n";
}

Graph readGraphFromFile(const string& filename, bool weighted) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Could not open file: " + filename);
    }

    Graph graph;
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string src, dest;
        int weight = 1;

        if (weighted) {
            if (!(iss >> src >> dest >> weight)) {
                throw runtime_error("Invalid weighted graph format in line: " + line);
            }
        } else {
            if (!(iss >> src >> dest)) {
                throw runtime_error("Invalid unweighted graph format in line: " + line);
            }
        }

        graph.addEdge(src, dest, weight);
    }

    return graph;
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        showUsage();
        return 1;
    }

    try {
        string filename = argv[1];
        string start = argv[2];
        string end = argv[3];
        bool weighted = (argc > 4 && string(argv[4]) == "--weighted");

        Graph graph = readGraphFromFile(filename, weighted);
        vector<string> path;

        auto startTime = chrono::high_resolution_clock::now();

        if (weighted) {
            path = graph.shortestPathDijkstra(start, end);
        } else {
            path = graph.shortestPathBFS(start, end);
        }

        auto endTime = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);

        if (path.empty()) {
            cout << "No path exists between " << start << " and " << end << "\n";
        } else {
            cout << "Shortest path (" << path.size() << " nodes): ";
            for (size_t i = 0; i < path.size(); i++) {
                if (i != 0) cout << " -> ";
                cout << path[i];
            }
            cout << "\nTotal cost: " << graph.getPathCost(path) << "\n";
        }

        cout << "Computation time: " << duration.count() << " ms\n";

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}