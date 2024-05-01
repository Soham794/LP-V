#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>
using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adjList;

public:
    Graph(int V) {
        this->V = V;
        adjList.resize(V+1);
    }

    void addEdge(int src, int dest) {
        adjList[src].push_back(dest);
        adjList[dest].push_back(src); // For undirected graph
    }

    vector<int> getNeighbors(int vertex) {
        return adjList[vertex];
    }
};

void dfs(Graph &graph, vector<bool> &visited, int node) {
    stack<int> s;
    s.push(node);
    while (!s.empty()){
        int curr_node = s.top();
        s.pop();

        if (!visited[curr_node]) {
            visited[curr_node] = true;
            if (visited[curr_node]) {
                cout << "Visited: " << curr_node << endl;
            }
            vector<int> neighbhors = graph.getNeighbors(curr_node);
            #pragma omp parallel for
            for (int i = 0; i < neighbhors.size(); i++){
                int adj_node = neighbhors[i];
                if (!visited[adj_node]){
                    s.push(adj_node);
                }
            }
        }
    }
}


int main() {

    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;
    Graph graph(V);
    cout << "Enter the number of edges: ";
    cin >> E;

    vector<bool> visited(V, false);

    for (int i = 0; i < E; ++i) {
        int src, dest;
        cout << "Enter the edge " << i+1 << " (src dest):" << endl;
        cin >> src >> dest;
        graph.addEdge(src, dest);
    }

    int start;
    cout << "Enter the vertex to start from: ";
    cin >> start;

    dfs(graph, visited, start);

return 0;
}