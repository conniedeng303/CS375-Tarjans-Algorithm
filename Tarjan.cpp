#include <iostream>
#include <vector>
#include <stack>
#include <fstream>


using namespace std;

//NOTE: size of vectors dependant on number in first line of graph
vector<vector<int>> graph; //[i][j] where i is node num, and j is whether node is adjacent
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
	if(graph[v][w]){
		if(!discoveryTime[w]){ //then v shares an edge with an undiscovered node
			strongConnect(w);
			LOWLINK[v] = min(LOWLINK[v],LOWLINK[w]);
		}
		else if(discoveryTime[w] < discoveryTime[v]){ //then v to w is a back edge or a cross edge
			LOWLINK[v] = min(LOWLINK[v], discoveryTime[w]);
		}
	}
	/* Connie's
        if (!discoveryTime[w]) {
            strongConnect(w)
            LOWLINK[v] = min(LOWLINK[v],LOWLINK[w]);
        }
        else if (isonStack[w] == 1){
            LOWLINK[v] = min(LOWLINK[v],indexv[w]);
        }*/
    }
    // If v is a root node, pop the stack and generate an SCC
    if (LOWLINK[v] == discoveryTime[v]) {
        vector<int> SCC;
        
	    //cout << "TarjanStack.top(): " << TarjanStack.top() << endl;
	     //cout << "discoveryTime[v]: " << discoveryTime[v] << endl;
	    //cout << "discoveryTime.size(): " << discoveryTime.size() << endl;
	    //cout << "TarjanStack.size(): " << TarjanStack.size() << endl;
	while(discoveryTime[TarjanStack.top()] >= discoveryTime[v]){
		SCC.push_back(TarjanStack.top());
		isOnStack[TarjanStack.top()] = false;
		TarjanStack.pop();
		//cout << "TarjanStack.top(): " << TarjanStack.top() << endl;
	}	
	int currSCCResultRow = SCCResults.size();
	SCCResults.push_back(vector<int>());
	for(int i = 0; i < SCC.size(); i++){
		SCCResults[currSCCResultRow].push_back(SCC[i]);
	}

	/* Connie's
	while (true) {
            int node = TarjanStack.pop();
            isOnStack[w] = false;
            SCC.push_back(w);
            if (w == v) {
                break;
            }
        }
        SCC.push_back(component);*/
    }
}

//seprate function here so its easier to feed it different adjacency lists

/*vector<vector<int>>tarjan(vector<vector<int>>& g) { //no clue what this is doing
    int n = graph.size();
    LOWLINK
}*/


int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: ./submission <input.txt> <output.txt>\n";
        return 1;
    }
    
	graph = vector<vector<int>>(); //[i][j] where i is node num, and j is whether node is adjacent
	discoveryTime = vector<int>();
	LOWLINK = vector<int>();
	isOnStack = vector<bool>(); //for quick a quick look
	TarjanStack = stack<int>(); 
	index = 1;
	SCCResults = vector<vector<int>>();
    
	ifstream inputFile(argv[1]);
	ofstream outputFile(argv[2]);
	string line;
	while(getline(inputFile, line)){ //if graph array does not have enough rows, loop and add rows until satisfactory
		//cout << "HERE\n";
		if(line.empty()){ //end of a graph. Run Tarjans then clear
			cout << "if\n";
			//strongConnect(0);
			for(int i = 0; i < graph.size(); i++){ //print adjaceny matrix
				for(int j = 0; j < graph[i].size(); j++){
					//cout << "HELLO\n";
					cout << graph[i][j] << " ";
				}
				cout << endl;
			} 
			for(int i = 0; i < discoveryTime.size(); i++){
				if(discoveryTime[i] == 0){
					strongConnect(i);
					cout << "HERE\n";
				}
			}
			graph.clear();
			LOWLINK.clear();
			isOnStack.clear();
			while(!TarjanStack.empty())
				TarjanStack.pop();
			//TarjanStack.clear();
			index = 1;
			for(int i = 0; i < SCCResults.size(); i++){
				for(int j = 0; j < SCCResults[i].size(); j++){
					//cout << "HELLO\n";
					cout << SCCResults[i][j] << " ";
				}
				cout << endl;
			}
			SCCResults.clear();
		}
		else if(line.at(0) == '/'){ //comment
			cout << "else if1\n";
			continue;
		}
		else if(line.find(' ') == string::npos){ //no space means line indicating number of nodes. Should be the first line of a graph, line should consist of only a number, and should only be one per graph
			cout << "else if2\n";
			int maxVertex = stoi(line);
			graph.resize(maxVertex);
			for(int i = 0; i < graph.size(); i++){
				graph[i].resize(maxVertex);
			}
			//for(int i: graph)
			//	graph[i].resize(maxVertex);
			discoveryTime.resize(maxVertex);
			LOWLINK.resize(maxVertex);
			isOnStack.resize(maxVertex);
			index = 1;
		}
		else{
			cout << "else\n";
			int spaceIndex = line.find(' ');
			int sourceNode = stoi(line.substr(0, spaceIndex));
			int destNode = stoi(line.substr(spaceIndex+1));
			graph[sourceNode-1][destNode-1] = 1; //dont forget to ouput nodes + 1 I think
		}
	}
	
    
    //TEST 1 ~ TREE
    printf("-----TEST 1 ~ TREE STRUCTURE----");
    vector<vector<int>> adjListTreeTest = {
        {1,2},
        {3,4},
        {5,6}
    };

    //auto s2 = tarjan
	return 0;
}