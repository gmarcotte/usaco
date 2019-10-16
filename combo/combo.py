"""
ID: garrett2 
TASK: combo
LANG: PYTHON3
"""

def iterate_combos(combo, N):
  for i in range(-2, 3):
    for j in range(-2, 3):
      for k in range(-2, 3):
        yield f'{(combo[0] + i) % N}-{(combo[1] + j) % N}-{(combo[2] + k) % N}'

def main():
  fin = open('combo.in', 'r')
  N = int(fin.readline().strip())
  set_combo = [int(s) for s in fin.readline().strip().split(' ')]
  master_combo = [int(s) for s in fin.readline().strip().split(' ')]

  combos = set()
  for s in iterate_combos(set_combo, N):
    combos.add(s)
  for s in iterate_combos(master_combo, N):
    combos.add(s)

  fout = open('combo.out', 'w')
  fout.write(f'{len(combos)}\n')

if __name__ == '__main__':
  main()
