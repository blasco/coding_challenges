#!/usr/bin/python

import math
import os
import random
import re
import sys

from collections import defaultdict

def get_next_geometric_progression_elements(array, ratio, index):
    base_index = index+1
    return [{'index': base_index + next_index, 'value': next_value} \
        for next_index, next_value in enumerate(array[base_index:]) if next_value == array[index]*ratio]

def count_triplets_at_index(array, ratio, index):
    first_element_value = array[index]

    if not (first_element_value == 1 or first_element_value % ratio == 0):
        return 0

    second_elements = get_next_geometric_progression_elements(array, ratio, index)
    triplet_count = 0
    for second_element in second_elements:
        third_elements = get_next_geometric_progression_elements(array, ratio, second_element['index'])
        triplet_count += len(third_elements)

    return triplet_count

# # Complete the countTriplets function below.
# def countTriplets(array, ratio):
#     candidates = array[0:-2]
#     number_of_triplets = 0
#     for index, value in enumerate(candidates):
#         number_of_triplets += count_triplets_at_index(array, ratio, index)
#     return number_of_triplets


# Better solution:

def countTriplets(arr, r):
    v2 = defaultdict(int)
    v3 = defaultdict(int)
    count = 0
    for k in arr:
        count += v3[k]
        v3[k*r] += v2[k]
        v2[k*r] += 1

    return count

if __name__ == '__main__':

    # result_file = open('result.txt', 'w')

    # nr = input().rstrip().split()
    # n = int(nr[0])
    # r = int(nr[1])
    # arr = list(map(int, input().rstrip().split()))

    # n = 4
    # r = 2
    # arr = [1,2,2,4]
    # answer = 2

    n = 6 
    r = 3
    arr = [1,9,3,9,27,81, 1]
    answer = 6

    # n = 5
    # r = 5
    # arr = [1,5,5,25,125]
    # answer = 4

    ans = countTriplets(arr, r)
    print("result: {0}".format(ans))

    # result_file.write(str(ans) + '\n')
    # result_file.close()

