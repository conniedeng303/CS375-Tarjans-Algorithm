# CS375-Tarjans-Algorithm
CS-375 Final Team Project - Kyle Sullivan, Connie Deng
This program produces strongly connected components from graphs in input.txt, and outputs them to output.txt

**Input and Ouput**
In input.txt, each graph consists of a series of sequential lines, followed by an empty line. The first line of a graph must contain the number of nodes in the graph. All following lines should contain the edges in the format "v w", where v is the number of the source node, and w is the destination node. This produces a directed edge. The final edge of a graph must be followed by an empty line. This file can be used to store multiple graphs. Additionally, this file can contain comments, in the form of lines starting with the '/' character.

In output.txt, each graph consists of a series of sequential lines, followed by an empty line. The first line will be the graph number, determined by the number of graphs placed into input.txt. Next will be 1 or more lines of sequences of numbers. Each line is a distinct component, and the elements in the format "x1 x2 ... xn" are the node numbers of nodes in a given component. Finally, each graph will show the runtime of the algorithm on that graph, followed by an empty line.

**Running the Program**
Within the makefile are rules for compiling, executing, and outputting the results of the program.
To simply compile the executable, enter "make", "make all" or "make Tarjan" into the command line. This will produce an executable called "Tarjan". To run the program using the provided files, enter into the command line "./Tarjan input.txt output.txt". input.txt and output.txt can be replaced with an input and output file of the user's choosing.
To both compile and execute the program, enter "make test" into the command line. This will compile the "Tarjan" executable and execute it. Unlike the previous scenario, the "test" rule is only compatible with an input file named "input.txt" and an output file named "output.txt".
To delete the executable and object file produced during compilation, enter "make clean" into the command line.
