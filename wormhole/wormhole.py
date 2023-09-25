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

  def __str__(self):
    return "%d: (%d, %d) <-> %s --> %s" % (self.id, self.x, self.y, self.paired_to, self.next_x)

class WormholeNetwork:
  def __init__(self):
    self.wormholes = {}

  def __str__(self):
    return "\n".join([str(self.wormholes[id]) for id in self.wormholes])

  def size(self):
    return len(self.wormholes)

  def addWormhole(self, x, y):
    new_id = len(self.wormholes)
    self.wormholes[new_id] = Wormhole(new_id, x, y)

  def finalize(self):
    by_y = {}
    for id in self.wormholes:
      wh = self.wormholes[id]
      by_y.setdefault(wh.y, [])
      by_y[wh.y].append(wh)

    for y_val in by_y:
      same_y = by_y[y_val]
      same_y.sort(key=lambda wh: wh.x)
      for i in range(len(same_y) - 1):
        same_y[i].next_x = same_y[i+1].id

  def clearPairings(self):
    for id in wormholes:
      self.wormholes[id].paired_to = None

  def pairWormholes(self, id1, id2):
    self.wormholes[id1].paired_to = id2
    self.wormholes[id2].paired_to = id1

  def updatePairings(self, pairing):
    for (id1, id2) in pairing:
      self.wormholes[id1].paired_to = id2
      self.wormholes[id2].paired_to = id1

  def hasCycleFrom(self, id):
    seen = set()
    curr = self.wormholes[id]
    use_paired = True
    while True:
      if use_paired:
        if curr.id in seen:
          return (True, seen)
        seen.add(curr.id)
        curr = self.wormholes[curr.paired_to]
        use_paired = False
      else:
        if curr.next_x is None:
          return (False, seen)
        else:
          curr = self.wormholes[curr.next_x]
          use_paired = True

  def hasCycle(self):
    seen = set()
    for id in self.wormholes:
      if id in seen:
        continue
      (res, new_seen) = self.hasCycleFrom(id)
      if res:
        return True
      else:
        seen = seen.union(new_seen)
    return False


def iterate_pairings_impl(unused, pairings):
#  print("u: %s" % unused)
#  print("p: %s" % pairings)
  if not unused:
    yield pairings
  else:
    first = unused.pop(0)
    #print("f: %s" % first)
    for i in range(len(unused)):
    #  print("i: %d" % i)
      second = unused.pop(i)
    #  print("s: %s" % second)
      pairings.append((first, second))
      yield from iterate_pairings_impl(unused, pairings)
      pairings.pop()
      unused.insert(i, second)
    unused.insert(0, first)

def iterate_pairings(wormholes):
  unused = [x for x in wormholes]
  yield from iterate_pairings_impl(unused, [])

def main():
  fin = open('wormhole.in', 'r')
  num_wormholes = int(fin.readline().strip())

  network = WormholeNetwork()
  for i in range(num_wormholes):
    (x, y) = (int(s) for s in fin.readline().split(' '))
    network.addWormhole(x, y)
  network.finalize()

  num_cycles = 0
  for pairing in iterate_pairings(range(network.size())):
    network.updatePairings(pairing)
    if network.hasCycle():
      #print("Cycle: %s" % pairing)
      #print("Network: %s" % network)
      num_cycles += 1

  fout = open('wormhole.out', 'w')
  fout.write(f'{num_cycles}\n')

if __name__ == '__main__':
  main()
