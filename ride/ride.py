"""
ID: garrett2
LANG: PYTHON3
TASK: ride
"""

def compute_mod(s):
  prod = 1
  for char in s:
    prod *= (ord(char) - ord('A') + 1)
    prod %= 47
  return prod


def main():
  fin = open('ride.in', 'r')
  comet = fin.readline().strip()
  group = fin.readline().strip()

  fout = open('ride.out', 'w')
  if compute_mod(comet) == compute_mod(group):
    fout.write('GO\n')
  else:
    fout.write('STAY\n')

if __name__ == '__main__':
  main()