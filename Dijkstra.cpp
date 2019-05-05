//**********************************************************************************
///Dijkstra Shortest Paths
// To implement dijkstra class method to the Graph class with built-in print utility. 
// program prinst out vertex selection sequence to show the shortest distance between the starting vertex and every vertices in the graph
/// Author: Erick Ramos
/// COMSC 210 Section (8304)
/// Date: April 18, 2018
/// Status : Complete
///***********************************************************************************
#include<iostream>
#include<vector>
#include<list>
#include<queue>
#include<algorithm> // remove()
#include<climits>    // INT_MAX
#define ii pair<int,int>

enum GRAPH_TYPE {DI, BI};
using namespace std;

// functor overloads the compare ii
class compareII {
public:
    bool operator()(const ii &j, const ii &k) {
        return j.second > k.second;}
};


class Graph
{
    int V, E;       // No. of vertices, edges
	list<ii> *adjList; // the djacensy List, alhead pointer to edge list
	list<ii> *edge; // The edge list from a specific vertex
	vector<int> distance; // distances (to starting point) container
	vector<int> pv; // picked vertices array
	priority_queue<ii, vector<ii>, compareII > Q; // type, container, comp

public:
    Graph(int v_num) : V(v_num), E(0) {
		edge = new list<ii>[V];
		distance = vector<int> (V, INT_MAX);
	}
    void addEdge(int u, int v, int w, int type = DI) {
        edge[u].push_back(ii(v, w)); E++;
	   if(type != DI) {
		   edge[v].push_back(ii(u, w)); E++; }
	}
    
    void dijkstra(int v);
    void print();
	void printGraph();
	void printAdjacency();
};

void Graph::printGraph() {
	cout << "\nPicked Node: ";
	for (auto p : pv) { cout << p << " "; }

	cout << "\n w/Distance:";
	for (auto p : pv) { cout << " (" << p << "," << distance[p] << ") ";}

	cout << "\nDistance Array:";
	for (int n=0; n<distance.size(); n++) { 
	   cout << " (" << n << "," << distance[n] << ") "; }
	cout << endl;
}

void Graph::printAdjacency()
{
	cout << "Graph of (" << V << ", " << E << ")\n";
	for (int n = 0; n < V; n++) {
		cout << "Vertex-" << n << " with: ";
		for (auto a : adjList[n]) 
			cout << n << "->(" << a.first << ", " << a.second << ") ";
		cout << endl;
	}
}

void Graph::dijkstra(int source) {
	distance = vector<int>(V, INT_MAX);
	distance[source] = 0;
	Q.push(ii(source, 0));
	adjList = new list<ii>[V];
	while (!Q.empty()) {
        // pop the vertex with smallest distance d of vertex v from Q 
		// smallest d of v from Q
		ii top = Q.top(); 
		Q.pop();
		int v = top.first, d = top.second;

        // push the selected vertex v into picked vertices array pv
        // cout << endl << "pushing selected vertex: " << v <<  endl;
        pv.push_back(v);

		if (d <= distance[v]) {  // If new distance is shorter than old distance
				// if the distance to new node is greater than distance from current node to this node
				// replace the distance
				// push the new node and distance into the queue
			for(list<ii>::iterator it = edge[v].begin(); it != edge[v].end(); ++it) {
			    if(distance[(*it).first] > distance[v] + (*it).second){
			        distance[(*it).first] = distance[v] + (*it).second;
			        Q.push(ii((*it).first, distance[(*it).first]));
			        adjList[v].push_back(ii((*it).first, distance[(*it).first]));
			    }
			}
		}
	}
}

// Driver program to test methods of graph class
int main()
{
    // Di-graph g(5,10)
    Graph g(5);
    g.addEdge(0,1,10,DI);
    g.addEdge(0,4,5,DI);
    g.addEdge(1,2,1,DI);
    g.addEdge(1,4,2,DI);
    g.addEdge(1,3,4,DI);
    g.addEdge(3,0,7,DI);
    g.addEdge(3,2,6,DI);
    g.addEdge(4,1,3,DI);
    g.addEdge(4,2,9,DI);
    g.addEdge(4,3,2,DI);
    
    cout << "\nDijkstra bidirectional graph g (starting from 0) \n";
	g.dijkstra(0);

	g.printGraph();
	cout << "\nAdjacency List for the g Graph\n";
	g.printAdjacency();
	
   // Bidirection G2B (9,28)
	Graph G2B(9);
	G2B.addEdge(0,1,4,BI);
	G2B.addEdge(0,7,8,BI);
	G2B.addEdge(1,2,8,BI);
	G2B.addEdge(1,7,11,BI);
	G2B.addEdge(2,3,7,BI);
	G2B.addEdge(2,5,4,BI);
	G2B.addEdge(2,8,2,BI);
	G2B.addEdge(3,4,9,BI);
	G2B.addEdge(3,5,14,BI);
	G2B.addEdge(4,5,10,BI);
	G2B.addEdge(5,6,2,BI);
	G2B.addEdge(6,7,1,BI);
	G2B.addEdge(6,8,6,BI);
	G2B.addEdge(7,8,7,BI);

	cout << "\nDijkstra bidirectional graph G2B (starting from 2) \n";
	G2B.dijkstra(2);

	G2B.printGraph();
	cout << "\nAdjacency List for the G2B Graph\n";
	G2B.printAdjacency();

	Graph G3B(6);

	G3B.addEdge(0,1,2,BI);
	G3B.addEdge(0,2,3,BI);
	G3B.addEdge(1,2,2,BI);
	G3B.addEdge(1,3,6,BI);
	G3B.addEdge(2,3,2,BI);
	G3B.addEdge(2,4,3,BI);
	G3B.addEdge(3,4,2,BI);
	G3B.addEdge(3,5,6,BI);
	G3B.addEdge(4,5,2,BI);

	cout << "\nDijkstra bidirectional graph G3B (starting from 2) \n";
	G3B.dijkstra(2);

	G3B.printGraph();

	cout << "\nAdjacency List for the G3B Graph\n";
	G3B.printAdjacency();
	
	

        //     2   3
        // (0)--(1)--(2)
        //  |    / \   |
        // 6| 8/    \5 |4
        //  | /  1   \ |
        // (3)-------(4)
        
	Graph G4B(5);

	G4B.addEdge(0,1,2,BI);
	G4B.addEdge(0,3,6,BI);
	G4B.addEdge(1,2,3,BI);
	G4B.addEdge(1,3,8,BI);
	G4B.addEdge(1,4,5,BI);
	G4B.addEdge(2,4,4,BI);
	G4B.addEdge(3,4,1,BI);

	cout << "\nDijkstra bidirectional graph G4B (starting from 0) \n";
	G4B.dijkstra(1);

	G4B.printGraph();

	cout << "\nAdjacency List for the G4B Graph\n";
	G4B.printAdjacency();

	return 0;
}
