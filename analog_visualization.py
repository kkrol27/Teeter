"""
Source: inspired by https://gist.github.com/electronut/d5e5f68c610821e311b0
"""

import sys, serial, argparse
import numpy as np
from time import sleep
from collections import deque

import matplotlib.pyplot as plt
import matplotlib.animation as animation

