"""
ID: garrett2
TASK: wormhole
LANG: PYTHON3
"""

class Wormhole:

  def __init__(self, id, x, y):
    self.id = id
    self.x = x
    self.y = y
    self.paired_to = None
    self.next_x = None

def clear_pairings(wormholes):
  for i in wormholes.keys():
    wh[i].paired_to = None

def has_cycle_from(wh):
  seen = set()
  curr = wh
  use_paired = True
  while curr.id not in seen:
    seen.add(curr.id)
    if use_paired:
      curr = curr.paired_to
      use_paired = False
    else:
      if curr.next_x is None:
        return False
      else:
        curr = curr.next_x
        use_paired = True
  return True

def iterate_pairings(wormholes_remaining, pairs):
  pairs.append(wormholes_remaining.pop())
  for i in range()


def main():
  fin = open('wormhole.in', 'r')
  num_wormholes = int(fin.readline().strip())

  wormholes = {}
  for i in range(num_wormholes):
    (x, y) = (int(s) for s in fin.readline().split(' '))
    wormholes[i] = Wormhole(i, x, y)

  by_y = {}
  for i in wormholes.keys():
    by_y.setdefault(by_y, wh[i].y, {})
    by_y[wh[i].y][wh[i].x] = wh[i]

  for y_val in by_y:
    x_vals = by_y[y_val].keys()
    x_vals.sort()
    for i in range(len(x_vals) - 1):
      by_y[y_val][x_vals[i]].next_x = by_y[y_val][x_vals[i+1]]

  num_cycles = 0
  for pairing in iterate_pairings(num_wormholes):
    for i in range(0, num_wormholes, 2):
      wormholes[pairing[i]].paired_to = wormholes[pairing[i+1]]
      wormholes[pairing[i+1]].paired_to = wormholes[pairing[i]]
    for i in wormholes.keys():
      if has_cycle_from(wh[i]):
        num_cycles += 1
        break
    clear_pairings(wormholes)

  fout = open('wormhole.out', 'w')
  fout.write(f'{num_cycles}\n')

if __name__ == '__main__':
  main()
