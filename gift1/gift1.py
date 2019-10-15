"""
ID: garrett2
TASK: gift1
LANG: PYTHON3
"""
import math
import sys

def main():
  fin = open('gift1.in', 'r')
  num_people = int(fin.readline().strip())
  accounts = {}
  for _ in range(num_people):
    name = fin.readline().strip()
    accounts[name] = 0

  for _ in range(num_people):
    name = fin.readline().strip()
    (amount, num_recipients) = (int(s) for s in fin.readline().strip().split(' '))
    if num_recipients > 0:
      gift_size = math.floor(amount / num_recipients)
    else:
      gift_size = 0
    accounts[name] += -1 * gift_size * num_recipients
    for _ in range(num_recipients):
      recipient = fin.readline().strip()
      accounts[recipient] += gift_size

  fout = open('gift1.out', 'w')
  for name in accounts:
    fout.write(f'{name} {accounts[name]}\n')
  
if __name__ == '__main__':
  main()