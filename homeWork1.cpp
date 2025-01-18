#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// Graph representations
const int MAX_NODES = 100;
bool adjMatrix[MAX_NODES][MAX_NODES];
vector<int> adjList[MAX_NODES];
vector<pair<int, int>> adjArray;

// Variables for DFS
int dfs_counter = 0, finish_counter = 0;
vector<int> state(MAX_NODES, 0); // 0: new, 1: active, 2: finished
vector<int> dfs_num(MAX_NODES, -1);
vector<int> fin_num(MAX_NODES, -1);

// Initialize the graph and reset variables
void initGraph(int nodes) {
    for (int i = 0; i < nodes; ++i) {
        for (int j = 0; j < nodes; ++j) {
            adjMatrix[i][j] = false;
        }
        adjList[i].clear();
    }
    adjArray.clear();
    dfs_counter = 0;
    finish_counter = 0;
    fill(state.begin(), state.end(), 0);
    fill(dfs_num.begin(), dfs_num.end(), -1);
    fill(fin_num.begin(), fin_num.end(), -1);
}

// Add edge to all representations
void addEdge(int u, int v) {
    adjMatrix[u][v] = true;
    adjList[u].push_back(v);
    adjArray.push_back({u, v});
}

// Initialization function
void init(int nodes) {
    dfs_counter = 0;
    finish_counter = 0;
    for (int v = 0; v < nodes; ++v) {
        state[v] = 0; // new
    }
}

// DFS
void dfs(int w) {
    state[w] = 1; // active
    dfs_num[w] = dfs_counter++;
    
    // Explore neighbors
    for (int u : adjList[w]) {
        if (state[u] == 0) {
            dfs(u);
        }
    }

    fin_num[w] = finish_counter++;
    state[w] = 2; // finished
}

// DepthFirstSearch function
void DepthFirstSearch(int nodes) {
    init(nodes); // Reset variables
    for (int v = 0; v < nodes; ++v) {
        if (state[v] == 0) {
            dfs(v);
        }
    }
}

// Reverse the edges of the graph
void reverseEdges(int nodes) {
    vector<int> reversedAdjList[MAX_NODES];
    for (int u = 0; u < nodes; ++u) {
        for (int v : adjList[u]) {
            reversedAdjList[v].push_back(u);
        }
    }
    for (int i = 0; i < nodes; ++i) {
        adjList[i] = reversedAdjList[i];
    }
}

// Check if the graph is strongly connected
bool isStronglyConnected(int nodes) {
    // Perform DFS on the original graph
    DepthFirstSearch(nodes);
    for (int i = 0; i < nodes; ++i) {
        if (state[i] == 0) return false;
    }

    // Reverse the graph
    reverseEdges(nodes);

    // Perform DFS on the reversed graph
    init(nodes);
    DepthFirstSearch(nodes);
    for (int i = 0; i < nodes; ++i) {
        if (state[i] == 0) return false;
    }

    return true;
}

// Create a random graph
void createRandomGraph(int nodes, int edges) {
    srand(time(0));
    initGraph(nodes);

    for (int i = 0; i < edges; ++i) {
        int u = rand() % nodes;
        int v = rand() % nodes;
        addEdge(u, v);
    }
}

// Print graph representations
void printGraph(int nodes) {
    cout << "Adjacency Matrix:\n";
    for (int i = 0; i < nodes; ++i) {
        for (int j = 0; j < nodes; ++j) {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nAdjacency List:\n";
    for (int i = 0; i < nodes; ++i) {
        cout << i << ": ";
        for (int v : adjList[i]) {
            cout << v << " ";
        }
        cout << endl;
    }

    cout << "\nAdjacency Array:\n";
    for (auto edge : adjArray) {
        cout << "(" << edge.first << ", " << edge.second << ") ";
    }
    cout << endl;
}

int main() {
    int nodes = 5, edges = 10;
    createRandomGraph(nodes, edges);

    printGraph(nodes);

    DepthFirstSearch(nodes);

    if (isStronglyConnected(nodes)) {
        cout << "\n\nThe graph is strongly connected.\n";
    } else {
        cout << "\n\nThe graph is not strongly connected.\n";
    }
    return 0;
}