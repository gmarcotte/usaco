"""
ID: garrett2
TASK: beads
LANG: PYTHON3
"""

def read_inc(i, lace, N, inc):
  idx = i % N
  num = 0
  color = None
  while lace[idx] == 'w' or lace[idx] == color or color is None:
    num += 1
    if lace[idx] != 'w':
      color = lace[idx]
    idx = (idx + inc) % N
    if idx == i % N:
      break
  return num


def read_right(i, lace, N):
  return read_inc(i + 1, lace, N, 1)

def read_left(i, lace, N):
  return read_inc(i, lace, N, -1)

def main():
  fin = open('beads.in', 'r')
  N = int(fin.readline().strip())
  lace = fin.readline().strip()

  max_seen = 0
  for i in range(N):
    val = read_left(i, lace, N) + read_right(i, lace, N)
    val = min([val, N])
    if val > max_seen:
      max_seen = val
  fout = open('beads.out', 'w')
  fout.write(f'{max_seen}\n')

if __name__ == '__main__':
  main()