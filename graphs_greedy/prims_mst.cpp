/*
 * Prim's (also alled Jarník's), is a greedy algorithm to find a minimum spanning tree for a weighted undirected graph
 * It finds a subset of the edges that forms a tree that includes every vertex, where the total weight of all the edges in the tree is minimized
 *
 * Generate a MST (minimum spanning tree), starting from an empty spanning tree.
 * At every step, it considers all the edges that connect the two sets, and picks the minimum weight edge from these edges. After picking the edge, it moves the other endpoint of the edge to the set containing MST.
 *
 * Running Time: O(V^2), can be reduced to O(E log V) with the help of binary heap.
 *
 * References:
 * - https://www.geeksforgeeks.org/prims-minimum-spanning-tree-mst-greedy-algo-5/
 * - https://www.geeksforgeeks.org/prims-mst-for-adjacency-list-representation-greedy-algo-6/
 */
#include <iostream>

using namespace std;

/**
 * Find the vertex with minimum key value, from the set of vertices not yet included in MST
 */
int minKey(int key[], bool mstSet[]) {
    int V = 5;
    // Initialize min value
    int min = INT_MAX;
    int min_index;

    for(int v = 0; v < V; v++) {
        if(mstSet[v] == false && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }

    return min_index;
}

/**
 * Print MST stored in parent
 */
void printMST(int parent[], int graph[5][5]) {
    cout << "Edge Weight" << endl;

    for(int i = 1; i < 5; i++) {
        cout << parent[i] << " - " << i << " : " << graph[i][parent[i]] << endl;
    }
}

/**
 * Construct MST for a graph represented using adjacency matrix representation
 */
void primMST(int graph[5][5]) {

    int V = 5;
    int parent[V];  // Array to store constructed MST
    int key[V];     // Key values used to pick minimum weight edge in cut
    bool mstSet[V]; // To represent set of vertices not yet included in MST

    // Initialize all keys as INFINITE
    for(int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    // Include first vertex in MST
    key[0] = 0;	    // Making key 0 so that this vertex is picked as first vertex
    parent[0] = -1; // First node is always root of MST

    // A min spanning tree has V - 1 edges
    for(int count = 0; count < V-1; count++) {
        // Pick the minimum key vertex from the set of vertices not yet included in MST
        int u = minKey(key, mstSet);

        // Add the picked vertex to the MST Set
        mstSet[u] = true;

        // Update key value and parent index of the adjacent vertices of the picked vertex
        // Consider only those vertices which are not yet included in MST
        for(int v = 0; v < V; v++) {
            // graph[u][v] is non zero only for adjacent vertices of m
            // mstSet[v] is false for vertices not yet included in MST
            // Update the key only if graph[u][v] is smaller than key[v]
            if(graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
	}

    // print the constructed MST
    printMST(parent, graph);
}

int main() {

    /*
     *       2      3
     *  (0) -- (1) -- (2)
     *   |    /   \    |
     * 6 | 8 /     \ 5 | 7
     *   | /         \ |
     *   (3) -------- (4)
     *          9
     */
    int graph[5][5] = { {0, 2, 0, 6, 0},
                        {2, 0, 3, 8, 5},
                        {0, 3, 0, 0, 7},
                        {6, 8, 0, 0, 9},
                        {0, 5, 7, 9, 0},
                      };

    // Print the solution
    primMST(graph);

    return 0;
}

