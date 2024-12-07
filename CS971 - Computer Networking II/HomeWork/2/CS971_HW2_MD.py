"""CS971: HW-2: Implementation of Djikstra's algorithm for finding the shortest
path between nodes in a graph..
uses: python CS971_HW2_MD.py
------------ OutPut: -----------------------
Enter source vertex (A-K, except I or enter 'END' to END this program)): B
Enter destination vertex (A-K, except I or enter 'END' to END this program)): D
      Source -> Destination: B -> D
        Shortest path: B --> C --> G --> H --> D
       Total cost: 4
-------------------------------------------
"""
from collections import deque

INFINITY = float("inf")

# ANSI color codes for terminal output
class Color:
    HEADER = '\033[95m'
    BLUE = '\033[94m'
    GREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'

class Graph:
    def __init__(self):
        self.graph_edges = [
            ('A', 'B', 1),
            ('A', 'E', 1),
            ('B', 'A', 1),
            ('B', 'C', 1),
            ('C', 'G', 1),
            ('C', 'F', 3),
            ('C', 'J', 4),
            ('D', 'E', 5),
            ('D', 'H', 1),
            ('D', 'J', 2),
            ('D', 'K', 1),
            ('E', 'A', 1),
            ('E', 'G', 1),
            ('E', 'D', 5),
            ('F', 'C', 3),
            ('F', 'K', 1),
            ('G', 'C', 1),
            ('G', 'E', 1),
            ('G', 'H', 1),
            ('H', 'G', 1),
            ('H', 'D', 1),
            ('J', 'C', 4),
            ('J', 'D', 2),
            ('K', 'D', 1),
            ('K', 'F', 1)
        ]

        self.nodes = set()
        for edge in self.graph_edges:
            self.nodes.update([edge[0], edge[1]])

        self.adjacency_list = {node: set() for node in self.nodes}
        for edge in self.graph_edges:
            self.adjacency_list[edge[0]].add((edge[1], edge[2]))

        distinct_nodes = set()
        for edge in self.graph_edges:
            distinct_nodes.update([edge[0], edge[1]])

        self.distinct_nodes_array = sorted(list(distinct_nodes))

    def shortest_path(self, start_node, end_node):
        unvisited_nodes = self.nodes.copy()  # All nodes are initially unvisited.

        # Create a dictionary of each node's distance from start_node. We will
        # update each node's distance whenever we find a shorter path.
        distance_from_start = {
            node: (0 if node == start_node else INFINITY) for node in self.nodes
        }

        # Initialize previous_node, the dictionary that maps each node to the
        # node it was visited from when the the shortest path to it was found.
        previous_node = {node: None for node in self.nodes}

        while unvisited_nodes:
            # Set current_node to the unvisited node with shortest distance
            # calculated so far.
            current_node = min(
                unvisited_nodes, key=lambda node: distance_from_start[node]
            )
            unvisited_nodes.remove(current_node)

            # If current_node's distance is INFINITY, the remaining unvisited
            # nodes are not connected to start_node, so we're done.
            if distance_from_start[current_node] == INFINITY:
                break

            # For each neighbor of current_node, check whether the total distance
            # to the neighbor via current_node is shorter than the distance we
            # currently have for that node. 
            for neighbor, distance in self.adjacency_list[current_node]:
                new_path = distance_from_start[current_node] + distance
                if new_path < distance_from_start[neighbor]:
                    distance_from_start[neighbor] = new_path
                    previous_node[neighbor] = current_node

            if current_node == end_node:
                break # we've visited the destination node, so we're done

      
        path = deque()
        current_node = end_node
        while previous_node[current_node] is not None:
            path.appendleft(current_node)
            current_node = previous_node[current_node]
        path.appendleft(start_node)

        return path, distance_from_start[end_node]


if __name__ == "__main__":
    graph = Graph()
    #print(graph.adjacency_list)
    while True:
        src_node = input("Enter source node (A-K, except I or enter 'END' to END this program)): ").upper()
        # Check if the user wants to quit
        if src_node == 'END':
            print("Exiting the program.")
            break
        dest_node = input("Enter destination node (A-K, except I or enter 'END' to END this program)): ").upper()
         # Check if the user wants to quit
        if dest_node == 'END':
            print("Exiting the program.")
            break

        if src_node not in graph.distinct_nodes_array or dest_node not in graph.distinct_nodes_array:
            print("Invalid node name. Please enter a valid vertex label (A-K, except I).")
        else:
            returned_path, returned_distance = graph.shortest_path(src_node, dest_node)
            formatted_path = " --> ".join(list(returned_path))
            # Print OutPut with different colors
            print('{0}      Source -> Destination node: {1} -> {2}{3}'.format(Color.HEADER, src_node, dest_node, Color.ENDC))
            print('{0}        Shortest path: {1} {2}'.format(Color.BLUE, formatted_path, Color.ENDC))
            print('{0}       Total cost: {1}{2}'.format(Color.GREEN, returned_distance, Color.ENDC))
            break   
