#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
#include <chrono>


using namespace std;

//NOTE: size of vectors dependant on number in first line of graph
vector<vector<int>> graph; //[i][j] where i is node num, and j is whether node is adjacent
vector<int> discoveryTime;
vector<int> LOWLINK;
vector<bool> isOnStack; //for quick a quick look
stack<int> TarjanStack; 
int index = 1;
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
    for(size_t w = 0; w < graph[v].size(); w++){//for (int w : graph[v]) {
	if(graph[v][w]){
		if(!discoveryTime[w]){ //then v shares an edge with an undiscovered node
			strongConnect(w);
			LOWLINK[v] = min(LOWLINK[v],LOWLINK[w]);
		}
		else if(discoveryTime[w] < discoveryTime[v]){ //then v to w is a back edge or a cross edge
			if(isOnStack[w])
				LOWLINK[v] = min(LOWLINK[v], discoveryTime[w]);
		}
	}
    }
    // If v is a root node, pop the stack and generate an SCC
    if (LOWLINK[v] == discoveryTime[v]) {
        vector<int> SCC;
        
	while(!TarjanStack.empty() && discoveryTime[TarjanStack.top()] >= discoveryTime[v]){
		SCC.push_back(TarjanStack.top());
		isOnStack[TarjanStack.top()] = false;
		TarjanStack.pop();
	}	
	int currSCCResultRow = SCCResults.size();
	SCCResults.push_back(vector<int>());
	for(size_t i = 0; i < SCC.size(); i++){
		SCCResults[currSCCResultRow].push_back(SCC[i]);
	}

    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: ./submission <input.txt> <output.txt>\n";
        return 1;
    }
    
	int graphNum = 1; //used for labeling outputs

	graph = vector<vector<int>>(); //[i][j] where i is node num, and j is whether node is adjacent
	discoveryTime = vector<int>();
	LOWLINK = vector<int>();
	isOnStack = vector<bool>(); //for quick a quick look
	TarjanStack = stack<int>(); 
	SCCResults = vector<vector<int>>();
    
	ifstream inputFile(argv[1]);
	ofstream outputFile(argv[2]);
	string line;
	while(getline(inputFile, line)){ //if graph array does not have enough rows, loop and add rows until satisfactory
		if(line.empty()){ //end of a graph. Run Tarjans, ouput, then clear
			auto start = chrono::high_resolution_clock::now();
			for(size_t i = 0; i < discoveryTime.size(); i++){
				if(discoveryTime[i] == 0){
					strongConnect(i);
				}
			}
			auto end = chrono::high_resolution_clock::now(); //Algorithm end time
			auto duration = chrono::duration_cast<std::chrono::nanoseconds>(end - start);
			discoveryTime.clear();
			graph.clear();
			LOWLINK.clear();
			isOnStack.clear();
			while(!TarjanStack.empty())
				TarjanStack.pop();
			index = 1;
			outputFile << "Graph " << graphNum++ << ":\n";
			for(size_t i = 0; i < SCCResults.size(); i++){
				for(size_t j = SCCResults[i].size()-1; (int)j > -1; j--){
					outputFile << SCCResults[i][j] + 1 << " ";
				}
				outputFile << endl;
			}
			outputFile << "Runtime: " << duration.count() << " nanoseconds\n\n";
			SCCResults.clear();
		}
		else if(line.at(0) == '/'){ //comment
			continue;
		}
		else if(line.find(' ') == string::npos){ //no space means line indicating number of nodes. Should be the first line of a graph, line should consist of only a number, and should only be one per graph
			int maxVertex = stoi(line);
			graph.resize(maxVertex);
			for(size_t i = 0; i < graph.size(); i++){
				graph[i].resize(maxVertex);
			}
			discoveryTime.resize(maxVertex);
			LOWLINK.resize(maxVertex);
			isOnStack.resize(maxVertex);
			index = 1;
		}
		else{ //line containing an edge
			int spaceIndex = line.find(' ');
			int sourceNode = stoi(line.substr(0, spaceIndex));
			int destNode = stoi(line.substr(spaceIndex+1));
			graph[sourceNode-1][destNode-1] = 1; //dont forget to ouput nodes + 1 I think
		}
	}

	return 0;
}