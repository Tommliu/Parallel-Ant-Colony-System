#! /usr/bin/python3
import numpy as np
import argparse
import os
from matplotlib import pyplot as plt

# This script is used to plot the speedup ...
n_cores = [1, 4, 16, 64 ,128]
speedup_offset = 1

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("-f", "--file", help="Specify the ACO output profile")
    return parser.parse_args()


def plot_speedup(lines, dataset):
    baseline = float(lines[speedup_offset])
    speedups = []
    N = len(n_cores)
    for i in range(N):
        speedups.append(baseline / float(lines[i + speedup_offset]))
    plt.figure()
    plt.plot(n_cores, speedups, 'r')
    plt.xlabel('Cores')
    plt.ylabel('Speedup')
    plt.grid(True)
    plt.title(dataset + ' speedup')
    for x_value, y_value in zip(n_cores, speedups):
        label = "{:.2f}".format(y_value)
        plt.annotate(label,(x_value, y_value), xytext=(0, 5), \
            textcoords="offset points", ha='center', va='bottom') 
    plt.show()


def save_image(dataset, filename):
    path = '../image/' + dataset + '/'
    if not os.path.exists(path):
        os.makedirs(path)
    plt.savefig(path + filename + '.png', dpi=200)


def main(args):
    filepath = args.file
    filename = filepath.strip().split('/')[-1]
    dataset = filename.split('_')[0]
    profile = open(filepath, 'r')
    lines = profile.readlines()
    
    # plot speedup
    plot_speedup(lines, dataset)

    # save speedup image
    save_image(dataset, filename)


if __name__ == '__main__':
    args = parse_args()
    main(args)
