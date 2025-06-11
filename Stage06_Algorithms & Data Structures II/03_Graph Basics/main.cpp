#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>

using namespace std;

class Graph {
private:
    int vertices;
    vector<vector<int>> adjList;

public:
    Graph(int v) : vertices(v), adjList(v) {}

    // Add edge to the graph (undirected)
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u); // Remove this for directed graph
    }

    // Breadth-First Search (iterative)
    void BFS(int start) {
        vector<bool> visited(vertices, false);
        queue<int> q;

        cout << "BFS starting from node " << start << ": ";
        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            cout << current << " ";

            for (int neighbor : adjList[current]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }

    // Depth-First Search (iterative)
    void DFS(int start) {
        vector<bool> visited(vertices, false);
        stack<int> s;

        cout << "DFS starting from node " << start << ": ";
        s.push(start);

        while (!s.empty()) {
            int current = s.top();
            s.pop();

            if (!visited[current]) {
                visited[current] = true;
                cout << current << " ";

                // Push neighbors in reverse order for proper traversal
                for (auto it = adjList[current].rbegin(); it != adjList[current].rend(); ++it) {
                    if (!visited[*it]) {
                        s.push(*it);
                    }
                }
            }
        }
        cout << endl;
    }

    // Recursive DFS implementation
    void DFSRecursive(int start) {
        vector<bool> visited(vertices, false);
        cout << "DFS (Recursive) starting from node " << start << ": ";
        DFSHelper(start, visited);
        cout << endl;
    }

private:
    void DFSHelper(int node, vector<bool>& visited) {
        visited[node] = true;
        cout << node << " ";

        for (int neighbor : adjList[node]) {
            if (!visited[neighbor]) {
                DFSHelper(neighbor, visited);
            }
        }
    }
};

int main() {
    // Create a graph with 7 vertices (0-6)
    Graph g(7);
    
    // Add edges
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(2, 6);
    g.addEdge(4, 5); // Creates a cycle

    // Perform traversals
    g.BFS(0);
    g.DFS(0);
    g.DFSRecursive(0);

    return 0;
}
