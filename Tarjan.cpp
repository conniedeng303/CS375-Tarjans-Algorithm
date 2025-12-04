#include <iostream>
#include <vector>


using namespace std;

vector<vector<int>> graph;
vector<int> discoveryTime;
vector<int> LOWLINK;
vector<bool> isOnStack; //for quick a quick look
stack<int> TarjanStack; 
int index;
vector<vector<int>> SCCResults;

//DFS FUNCTION
void strongConnect(int v) {
    // Set the depth index for v to the smallest unused index
    discoveryTime[v] = index;
    LOWLINK[v] = index;
    index = index + 1;
    TarjanStack.push(v);
    isOnStack[v] = 1;

    //Consider sucessors of v
    for (int w : graph[v]) {
        if (discoveryTime) {
            strongConnect(w)
            LOWLINK[v] = min(LOWLINK[v],LOWLINK[w]);
        }
        else if (isonStack[w] == 1){
            LOWLINK[v] = min(LOWLINK[v],indexv[w]);
        }
    }
    // If v is a root node, pop the stack and generate an SCC
    if (LOWLINK[v] == discoveryTime[v]) {
        vector<int> SCC;
        while (true) {
            int node = TarjanStack.pop();
            isOnStack[w] = false;
            SCC.push_back(w);
            if (w == v) {
                break;
            }
        }
        SCC.push_back(component);
    }
}

//seprate function here so its easier to feed it different adjacency lists

vector<vector<int>>tarjan(vector<vector<int>>& g) {
    int n = graph.size();
    LOWLINK
}


int main() {
    if (argc < 3) {
        cerr << "Usage: ./submission <input.txt> <output.txt>\n";
        return 1;
    }
    //TEST 1 ~ TREE
    printf("-----TEST 1 ~ TREE STRUCTURE----");
    vector<vector<int>> adjListTreeTest = {
        {1,2},
        {3,4},
        {5,6}
    }

    auto s2 = tarjan

}