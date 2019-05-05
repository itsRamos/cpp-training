//**********************************************************************************
/// Graph DFS and BFS Traversal
/// Author: Erick Ramos
/// Date: April 9, 2018
///***********************************************************************************
#include <list>
#include <iostream>
using namespace std;

#define ii pair<int,int>
enum GRAPH_TYPE {DI, BI};

class Graph {
    int V, E;     // No. of vertices
    list<ii> *adj; // An array of adjacency lists adj[]
public:
//  Graph(int v_num) : V(v_num), E(0) {adj = new list<ii>[V];}
    Graph(int v_num) {V = v_num; E=0; adj = new list<ii>[V];}
    void addEdge(int u, int v, int w, int type = DI) {
        adj[u].push_back( ii(v,w) );
        E++;
        if(type != DI) {
            adj[v].push_back( ii(u,w) );
            E++;
        }
    }
    void BFS(int v);
	void DFS(int v);
	void DFS(int v, bool visited[]);
    void print();
};

void Graph::BFS(int v) {
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++) {
        visited[i] = false;
    }

    list<int> queue;  // Vertices in progress
    // list<int, int> queue;  // Vertices in progress
    visited[v] = true;
    queue.push_back(v);

    while(!queue.empty())
    {
        v = queue.front();
        cout << v << " ";
        queue.pop_front();

        for (list<ii>::iterator it = adj[v].begin(); it != adj[v].end(); ++it) {
          if(!visited[(*it).first]) {
              visited[(*it).first] = true;
              queue.push_back((*it).first);
          }
        }
    }
    cout << endl;
}

void Graph::DFS(int v) {
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++) {
        visited[i] = false;
    }
    
    DFS(v, visited);
    cout << endl;
}

void Graph::DFS(int v, bool visited[]) {
    visited[v] = true;
    cout << v << " ";

    for(list<ii>::iterator it = adj[v].begin(); it != adj[v].end(); ++it) {
        if(!visited[(*it).first]) {
            DFS((*it).first, visited);
        }
    }
}


// print format: Node-0 with 0->1, 0->2,
void Graph::print() {
    for(int i=0;  i<V; i++) {
        cout << "Node-" << i << " with";
        for(list<ii>::iterator it = adj[i].begin(); it != adj[i].end(); it++) {
            cout << (it != adj[i].begin() ? "," : "") << " " << i << "-> (" << (*it).first << ", " << (*it).second << ")";
        }
        cout << endl;
    }
}

// Driver program to test methods of graph class
int main()
{
    // Creating a directed graph given in the diagram below
    Graph G1(5);
    G1.addEdge(0, 1, 5);
	G1.addEdge(0, 2, 4);
	G1.addEdge(1, 2, 4);
	G1.addEdge(1, 4, 6);
	G1.addEdge(2, 3, 3);
	G1.addEdge(3, 4, 4);
	
	// turn the commented code below back on, after BFS and DFS is defined
	
    cout << "\nBFS digraph G1 (starting from 2)" << endl;
    G1.BFS(0);
    cout << "DFS digraph G1 (starting from 2)" << endl;
    G1.DFS(2);
    G1.print();
    
    cout << endl << "SECOND GRAPH G1B" << endl;
    Graph G1B(5);
    G1B.addEdge(0, 1, 5, BI);
	G1B.addEdge(0, 2, 4, BI);
	G1B.addEdge(1, 2, 4, BI);
	G1B.addEdge(1, 4, 6, BI);
	G1B.addEdge(2, 3, 3, BI);
	G1B.addEdge(3, 4, 4, BI);

    cout << "\nBFS digraph G1B (starting from 2)" << endl;
    G1B.BFS(2);
    cout << "DFS digraph G1B (starting from 2)" << endl;
    G1B.DFS(2);
    G1B.print();
    
    return 0;
}
