from itertools import combinations
from itertools import permutations

import time
import random

def generate_distance_matrix(num_cities, min_distance=1, max_distance=100):
    distance_matrix = [[0 if i == j else random.randint(min_distance, max_distance) 
                        for j in range(num_cities)] for i in range(num_cities)]
    return distance_matrix


def calculate_total_distance(permutation, distance_matrix):
    total_distance = 0
    for i in range(len(permutation)):
        total_distance += distance_matrix[permutation[i-1]][permutation[i]]
    return total_distance

def tsp_brute_force(distance_matrix):
    cities = range(len(distance_matrix))
    min_distance = float('inf')
    shortest_path = []
    
    for permutation in permutations(cities):
        current_distance = calculate_total_distance(permutation, distance_matrix)
        if current_distance < min_distance:
            min_distance = current_distance
            shortest_path = permutation

    return shortest_path, min_distance


def bellman_held_karp(distance_matrix):
    n = len(distance_matrix)
    # memoization table, where key is a tuple (subset, i) 
    # with subset represented as bitmask and i as endpoint
    memo = {}

    # base case: only the first city is in the subset
    for i in range(1, n):
        memo[(1 << i, i)] = (distance_matrix[0][i], [0, i])

    # iterate over all subsets of cities and calculate min distance for the paths
    for subset_size in range(2, n):
        for subset in combinations(range(1, n), subset_size):
            # set bits for all cities in this subset
            bits = sum([1 << city for city in subset])
            # initialize this entry as not visited
            for city in subset:
                prev = bits & ~(1 << city)
                min_dist = float('inf')
                for k in subset:
                    if k == city or not (prev & (1 << k)):
                        continue
                    current_dist = memo[(prev, k)][0] + distance_matrix[k][city]
                    if current_dist < min_dist:
                        min_dist = current_dist
                        memo[(bits, city)] = (min_dist, memo[(prev, k)][1] + [city])
    
    # include the last leg returning to the starting city
    all_cities = (1 << n) - 1  # all cities visited
    min_dist = float('inf')
    for k in range(1, n):
        current_dist = memo[(all_cities & ~1, k)][0] + distance_matrix[k][0]
        if current_dist < min_dist:
            min_dist = current_dist
            shortest_path = memo[(all_cities & ~1, k)][1] + [0]

    return shortest_path, min_dist


for num_cities in range(2, 30):
    distance_matrix = generate_distance_matrix(num_cities)
    # start = time.time()
    # shortest_path1, min_distance1 = tsp_brute_force(distance_matrix)
    # delta1 = time.time() - start
    start = time.time()
    shortest_path2, min_distance3 = bellman_held_karp(distance_matrix)
    delta2 = time.time() - start
    # print(f"Time taken for brute force algorithm and num_cities={num_cities}: {delta1}")
    print(f"Time taken for bellman-held-karp algorithm and num_cities={num_cities}: {delta2}\n")
    # print(f"Shortest path of brute force: {shortest_path1}")
    # print(f"Total distance of brute force: {min_distance1}\n")
    print(f"Shortest path of bellman-held-karp: {shortest_path2}")
    print(f"Total distance of bellman-held-karp: {min_distance3}\n\n")