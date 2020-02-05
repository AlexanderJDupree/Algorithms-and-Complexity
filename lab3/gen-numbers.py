#!/usr/bin/python3

"""
File  : gen-numbers.py
Brief : Generate random numbers within a range
Author: Alexander DuPree
"""

import random
import argparse
from os import sys

def validateInteger(arg, lbound, ubound):
    value = int(arg)
    if value < lbound or value > ubound:
        raise argparse.ArgumentTypeError(
                f'{arg} is not within range {lbound}..{ubound}'
                )
    return value

def validateSize(arg):
    return validateInteger(arg, 1, 1000000000)

def parse(argv):

    parser = argparse.ArgumentParser(
            description="Generate random numbers"
            )
    parser.add_argument(
            'size',
            type=validateSize,
            metavar='N',
            help="<N> Numbers to genereate"
            )
    parser.add_argument(
            '-r', '--range',
            nargs=2,
            metavar=('min', 'max'),
            default=(0, 100),
            help="<min> <max> Inclusive range to generate numbers"
            )
    parser.add_argument(
            '-n', '--newlines',
            metavar='',
            default=True,
            help="Display each generated number on a new line"
            )

    # Returns a dict object
    return vars(parser.parse_args(argv))

def gen_numbers(n, min, max):
    return [random.randint(int(min), int(max)) for _ in range(n)]

def display_nums(nums, newlines):
    if newlines:
        list(map(print, nums))
    else:
        print(nums)
 
def main():

    args = parse(sys.argv[1:]) 

    nums = gen_numbers(args['size'], args['range'][0], args['range'][1])

    print(args['size'])
    display_nums(nums, args['newlines'])

    return 0

if __name__ == "__main__":
    main()
