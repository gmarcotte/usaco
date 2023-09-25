"""
ID: garrett2
TASK: ariprog
LANG: PYTHON3
"""
from operator import itemgetter
import time

def main():
  init = time.time()
  fin = open('ariprog.in', 'r')
  n = int(fin.readline().strip())
  m = int(fin.readline().strip())

  S = {}
  for p in range(m + 1):
    for q in range(p, m + 1):
      S[p*p + q*q] = True

  print("Computed %d bisquares in %f" % (len(S), time.time() - init))

  keys = list(S.keys())
  keys.sort()
  max = keys[-1]
  print(max)

  seen = {}

  k = 0
  for i in range(len(keys)):
    k += 1

  print("Finished %d-length loop in %f" % (k, time.time() - init))

'''
  progs.sort(key=itemgetter(0))
  progs.sort(key=itemgetter(1))

  fout = open('ariprog.out', 'w')
  if not progs:
    fout.write("NONE\n")
  else:
    for prog in progs:
      fout.write("%d %d\n" % (prog[0], prog[1]))
'''

if __name__ == '__main__':
  main()