"""
ID: garrett2
TASK: barn1
LANG: PYTHON3
"""

def main():
  fin = open('barn1.in', 'r')
  (max_boards, _, num_cows) = (int(s) for s in fin.readline().strip().split(' '))

  stalls = []
  for i in range(num_cows):
    stalls.append(int(fin.readline().strip()))

  stalls.sort()

  gaps = []
  for i in range(num_cows - 1):
    if stalls[i + 1] - stalls[i] > 1:
      gaps.append(stalls[i + 1] - stalls[i] - 1)

  gaps.sort()

  bought = 1
  num_covered = stalls[num_cows - 1] - stalls[0] + 1

  while bought < max_boards and len(gaps) > 0:
    num_covered -= gaps.pop()
    bought += 1

  fout = open('barn1.out', 'w')
  fout.write(f'{num_covered}\n')

if __name__ == '__main__':
  main()