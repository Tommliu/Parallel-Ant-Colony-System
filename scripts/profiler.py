#!/usr/bin/env python3

# This script is used to plot the speedup and best tour length

import numpy as np
import argparse
import os
from matplotlib import pyplot as plt

n_cores = []
n_cores_chars = []
batch_size = 2
speedup_offset = 0
tour_length_offset = 1

model_map = {0 : "Sequential ACO", 
             1 : "OpenMp ACO", 
             2 : "OpenMPI ACO", 
             3 : "Multi-colony ACO (Ring)"}


def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("-f", "--file", help="Specify the ACO output profile")
    return parser.parse_args()


def save_image(dataset, filename, profile_type='sp'):
    path = 'image/' + dataset + '/'
    if not os.path.exists(path):
        os.makedirs(path)
    plt.savefig(path + filename + '_' + profile_type + '.png', dpi=200)


def plot_profile(lines, filename):
    tokens = filename.split('_')
    dataset = tokens[0]
    m_idx = int(token[1])
    model = model_map[m_idx]

    baseline = float(lines[speedup_offset].split()[-1])
    speedups = []
    tour_lengths = []
    N = len(lines) // 2
    for i in range(N):
        cores = int(lines[i * batch_size + speedup_offset].split()[2][1:-1])
        n_cores.append(cores)
        n_cores_chars.append(str(cores))
        speedups.append(baseline / float(lines[i * batch_size + speedup_offset].split()[-1]))
        tour_lengths.append(float(lines[i * batch_size + tour_length_offset].split()[-1]))
    
    # Speedup iamge
    plt.figure()
    plt.plot(n_cores, speedups, 'r')
    plt.xlabel('Cores')
    plt.ylabel('Speedup')
    plt.grid(True)
    plt.title(model + ' Speedup' + '(' + dataset + ')')
    for x_value, y_value in zip(n_cores, speedups):
        label = "{:.2f}".format(y_value)
        plt.annotate(label,(x_value, y_value), xytext=(0, 5), \
            textcoords="offset points", ha='center', va='bottom') 
    plt.show()
    # save speedup image
    save_image(dataset, filename, 'sp')
    plt.close()
    
    # Tour Length Image
    plt.figure()
    plt.bar(n_cores_chars, tour_lengths)
    plt.xlabel('Cores')
    plt.ylabel('Best Tour Length')
    plt.title(model + ' Tour Length' + '(' + dataset + ')')
    for x_value, y_value in zip(n_cores_chars, tour_lengths):
        label = "{:.2f}".format(y_value)
        plt.annotate(label,(x_value, y_value), xytext=(0, 5), \
            textcoords="offset points", ha='center', va='bottom') 
    plt.show()
    # save Tour Length image
    save_image(dataset, filename, 'tl')
    plt.close()


def main(args):
    filepath = args.file
    filename = filepath.strip().split('/')[-1]
    # dataset = filepath.strip().split('/')[-2]
    profile = open(filepath, 'r')
    lines = profile.readlines()
    
    # plot profile
    plot_profile(lines, filename)


if __name__ == '__main__':
    args = parse_args()
    main(args)
