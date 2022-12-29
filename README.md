# Dijkstras-Graph-Sorting-Algorithm
# Usage: ./PJ3 <GraphType>(Directed or Undirected) <InputFile>(recommended network01.txt, network02.txt, and network03.txt)
#         Upon using the above command line type: Stop, SinglePair int int, SingleSource int, PrintPath int int, PrintLength int int
#         Stop ends the program
#         SinglePair followed by two integers finds the shortest path from the first int to the second int
#         SingleSource followed by an integer finds the shortest path from the integer to every other vertex
#         PrintPath followed by two integers prints the path from the first integer to the second. 
#               NOTE:   The first integer must correspond to the first integer of SinglePair or SingleSource 
#                       the second integer must correspond to the second integer of SinglePair
#         PrintLength followed by two integers prints the length of the shortest path between the first integer to the second
#               NOTE:   The first integer must correspond to the first integer of SinglePair or SingleSource 
#                       the second integer must correspond to the second integer of SinglePair
# Network Formatting:
#         The first integer is the number of vertexes
#         The second integer is the number of edges
#         The following sets of integers are the edges
#         The first integer in a set is the edge index
#         The second integer in a set is the source vertex
#         The third integer in a set is the destination vertex
#         The fourth integer in a set is the weight of the edge
