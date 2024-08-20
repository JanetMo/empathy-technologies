from graphviz import Source
import os
os.environ["PATH"] += os.pathsep + 'C:/ProgramData/Anaconda3/Library/bin/graphviz/' # here is the path to the graphviz package


def matrix_to_dot(matrix):
    """
    this function should be the logic how to convert a matrix to graph, I just give an example. Please adjust
    :param matrix: input matrix
    :return:
    """
    n = len(matrix)
    dot_str = "digraph G {\n"
    for i in range(n):
        for j in range(n):
            if matrix[i][j] != 0:
                dot_str += f"    {chr(65+i)} -> {chr(65+j)};\n"
    dot_str += "}"
    return dot_str




def generate_graph(graph_code):
    # Render the graph
    src = Source(graph_code)
    src.render('graph', format='png', view=True)



if __name__ == "__main__":
    # here the grapha_code below is just an example how the data should be formatted. it should be replaced by matrix and matrix_to_dot function
    graph_code = """
    digraph G {
    // Define the first type of nodes
    node [shape=circle, style=filled, color=lightblue];
    Emily; Johan;

    // Define the second type of nodes
    node [shape=box, style=not, color=lightgreen];
    1; 2; 3; 4; 5; 6; 7;

    // Define edges with varying thickness
    Emily -> 1 [label="", penwidth=2];
    Emily -> 2 [label="", penwidth=5];
    Emily -> 3 [label="", penwidth=3];
    Emily -> 4 [label="", penwidth=4];
    Emily -> 5 [label="", penwidth=6];
    Emily -> 6 [label="", penwidth=3];
    Emily -> 7 [label="", penwidth=1];

    Johan -> 1 [label="", penwidth=4];
    Johan -> 2 [label="", penwidth=5];
    Johan -> 3 [label="", penwidth=6];
    Johan -> 4 [label="", penwidth=3];
    Johan -> 5 [label="", penwidth=2];
    Johan -> 6 [label="", penwidth=4];
    Johan -> 7 [label="", penwidth=2];
}
"""
    matrix = [
        [0, 1, 0],
        [1, 0, 1],
        [0, 1, 0]
    ]
    #graph_code = matrix_to_dot(matrix) # this should be used once the function is completed
    generate_graph(graph_code)
