#include <iostream>
#include <vector>
#include <cstdio>
#include <queue>
#include <limits>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct Edge {
    int v; 
    int flow; 
    int capacity; 

};

int fordFulkerson(vector<vector<Edge>>& graph, int source, int sink) 
{
    int maxFlow = 0;
    vector<vector<Edge>> residualGraph(graph);

    while (true) 
    {
        vector<int> parent(graph.size(), -1); 
        queue<int> q;
        q.push(source);
        while (!q.empty()) 
        {
            int u = q.front();
            q.pop();

            for (Edge& edge : residualGraph[u]) 
            {
                if (parent[edge.v] == -1 && edge.capacity > 0) 
                {
                    q.push(edge.v);
                    parent[edge.v] = u;
                }
            }
        }

        if (parent[sink] == -1)
        {
            break;
        }

        int pathFlow = INT_MAX; 
        for (int v = sink; v != source; v = parent[v]) 
        {
            int u = parent[v];
            for (Edge& edge : residualGraph[u]) 
            {
                if (edge.v == v)
                {
                    pathFlow = min(pathFlow, edge.capacity);
                    break;
                }
            }
        }

        maxFlow += pathFlow;

        for (int v = sink; v != source; v = parent[v]) 
        {
            int u = parent[v];
            for (Edge& edge : residualGraph[u]) 
            {
                if (edge.v == v) 
                {
                    edge.capacity -= pathFlow;
                    for (Edge& revEdge : residualGraph[v]) 
                    {
                        if (revEdge.v == u) 
                        {
                            revEdge.capacity += pathFlow;
                            break;
                        }
                    }
                    break;
                }
            }
        }
    }

    return maxFlow;
}

int main()
{

    int numVertices, numEdges;
    int source, sink;
    ifstream file;
    file.open("input.txt");

    file >> numVertices >> numEdges;
    file >> source >> sink;
    cout << "Vertices: " << numVertices << endl << "Edges: " << numEdges<< endl;
    vector<vector<Edge>> graph(numVertices);

    for (int i = 0; i < numEdges; i++) {
        int source, destination, capacity;
        file >> source >> destination >> capacity; 
        graph[source - 1].push_back({ destination - 1, capacity, capacity });
        cout << "Edge " << i + 1 << " (" << source << "," << destination << ") = " << capacity << endl;
    }

    int maxflow = fordFulkerson(graph, source, sink);
    cout << "Maximum flow: " << maxflow << endl;
    
    return 0;
}