#! /usr/bin/python3
import numpy as np
import argparse
from matplotlib import pyplot as plt

# Usgae case
# python3 visualizer.py -f output/test.tsp 

# baseline measurement for n == 1
baseline_mp = {"vlsi_s": 1, "vsli_m": 1, "vlsi_l": 1,
               "Germany": 1, "USA": 1}

#Solution starts from line 6
data_line = 5

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("-n", help="number of processors", type=int, default=1)
    parser.add_argument("-f", "--file", help="Specify the ACO output file")
    # parser.add_argument("-ds", "--dataset", help="Specify the test dataset", default=None)
    return parser.parse_args()

def main(args):
    output_file = open(args.file, 'r')
    lines = output_file.readlines()
    # read metadata from the header
    name = lines[0].split()[-1]
    dataset= lines[1].split()[-1]
    tour_length = int(lines[2].split()[-1])
    computation_time = int(lines[3].split()[-1])
    dimension = int(lines[4].split()[-1])
    
    positions = extract(lines, dimension)
    plot(positions, dimension)
    # analyze(...)

def extract(lines, dimension):
    positions = np.zeros((dimension, 2))
    for i in range(dimension):
        coord = lines[data_line + i].split()
        positions[i][0] = int(coord[0])
        positions[i][1] = int(coord[1])
    return positions

def plot(positions, dimension):
    fig, ax = plt.subplots(2, sharex=True, sharey=True)         # Prepare 2 plots
    fig.set_size_inches(16, 8)
    ax[0].set_title('Raw nodes')
    ax[1].set_title('Optimized tour')
    ax[0].scatter(positions[:, 0], positions[:, 1])             # plot A
    ax[1].scatter(positions[:, 0], positions[:, 1])             # plot B
    start_node = 0
    distance = 0.
    for i in range(dimension):
        start_pos = positions[i]
        # next_node = positions[(i+1)%dimension] # needed because of MIP-approach used for TSP
        end_pos = positions[(i + 1) % dimension]
        ax[1].annotate("",
                xy=start_pos, xycoords='data',
                xytext=end_pos, textcoords='data',
                arrowprops=dict(arrowstyle="->",
                                connectionstyle="arc3"))
        distance += np.linalg.norm(end_pos - start_pos)
        # start_node = next_node

    textstr = "N nodes: %d\nTotal length: %.3f" % (dimension, distance)
    props = dict(boxstyle='round', facecolor='wheat', alpha=0.5)
    ax[1].text(0.05, 0.95, textstr, transform=ax[1].transAxes, fontsize=10, # Textbox
            verticalalignment='center', bbox=props)

    plt.tight_layout()
    plt.show()
    plt.savefig('output1.png', dpi=200)


# This function is used to compute the statistics
# def analyze():

if __name__ == "__main__":
    args = parse_args()
    print(args)
    main(args)
