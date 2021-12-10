#!/usr/bin/env python3

import numpy as np
import argparse
import os
from matplotlib import pyplot as plt

# Usgae case
# python3 visualizer.py -f output/test.tsp 

#Solution starts from line 3
data_line = 3

model_map = {0 : "Sequential ACO", 
             1 : "OpenMp ACO", 
             2 : "OpenMPI ACO", 
             3 : "Multi-colony ACO (Ring)"}

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("-f", "--file", help="Specify the ACO output file")
    return parser.parse_args()


def extract(lines, dimension):
    positions = np.zeros((dimension, 2))
    for i in range(dimension):
        coord = lines[data_line + i].split()
        positions[i][0] = int(coord[0])
        positions[i][1] = int(coord[1])
    return positions


def save_image(dataset, filename):
    path = 'image/' + dataset + '/'
    if not os.path.exists(path):
        os.makedirs(path)
    plt.savefig(path + filename + '.png', dpi=200)


def plot(positions, dimension, distance, filename):
    tokens = filename.split('_')
    dataset = tokens[0]
    m_idx = int(tokens[1])
    cores = int(tokens[2])
    model = model_map[m_idx]

    fig, ax = plt.subplots(2, sharex=True, sharey=True)         # Prepare 2 plots
    fig.set_size_inches(25, 16)
    ax[0].set_title(dataset + ' Raw nodes')
    ax[1].set_title(model + ' Optimized tour')
    ax[0].scatter(positions[:, 0], positions[:, 1], s=1, c='r')             # plot A
    ax[1].scatter(positions[:, 0], positions[:, 1], s=1, c='r')             # plot B
    start_node = 0
    for i in range(dimension):
        start_pos = positions[i]
        end_pos = positions[(i + 1) % dimension]
        ax[1].annotate("",
                xy=start_pos, xycoords='data',
                xytext=end_pos, textcoords='data',
                arrowprops=dict(arrowstyle="-",
                                connectionstyle="arc3",lw=1))

    textstr = "N nodes: %d\nTotal length: %.3f" % (dimension, distance)
    props = dict(boxstyle='round', facecolor='wheat', alpha=0.5)
    ax[1].text(0.05, 0.95, textstr, transform=ax[1].transAxes, fontsize=10, # Textbox
            verticalalignment='center', bbox=props)
    plt.tight_layout()
    plt.show()
    save_image(dataset, filename)

def main(args):
    filepath = args.file
    filename = filepath.strip().split('/')[-1]
    output_file = open(args.file, 'r')
    lines = output_file.readlines()

    # read metadata from the header
    name = lines[0].split()[-1]
    distance = float(lines[1].split()[-1])
    dimension = int(lines[2].split()[-1])
    
    # Plot the TSP
    positions = extract(lines, dimension)
    plot(positions, dimension, distance, filename)


if __name__ == "__main__":
    args = parse_args()
    main(args)
