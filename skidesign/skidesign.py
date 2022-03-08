"""
ID: garrett2
TASK: skidesign
LANG: PYTHON3
"""

import math

MAX_DELTA = 17
MAX_HEIGHT = 100

def main():
  fin = open('skidesign.in', 'r')

  num_hills = int(fin.readline().strip())
  heights = []
  for i in range(num_hills):
    heights.append(int(fin.readline().strip()))

  min_cost = math.inf
  for low in range(MAX_HEIGHT - MAX_DELTA + 1):
    cost = 0
    high = low + MAX_DELTA
    for height in heights:
      if height < low:
        cost += (low - height) * (low - height)
      elif height > high:
        cost += (height - high) * (height - high)
    if cost < min_cost:
      min_cost = cost

  fout = open('skidesign.out', 'w')
  fout.write("%d\n" % min_cost)


if __name__ == '__main__':
  main()