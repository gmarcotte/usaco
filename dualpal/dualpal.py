"""
ID: garrett2
TASK: dualpal
LANG: PYTHON3
"""
import math

def is_palindrome(s):
  i  = 0
  j = len(s) - 1
  while i < j:
    if s[i] != s[j]:
      return False
    i += 1
    j -= 1
  return True

def convert_base(val, base):
  power = math.floor(math.log(val, base))
  chars = []
  while power >= 0:
    pow_val = math.pow(base, power)
    digit = math.floor(val / pow_val)
    val -= digit * pow_val
    chars.append(str(digit))
    power -= 1
  return ''.join(chars)

def is_dual_palindrome(val):
  num = 0
  for base in range(2, 11):
    if is_palindrome(convert_base(val, base)):
      num += 1
    if num >= 2:
      return True
  return False

def main():
  fin = open('dualpal.in', 'r')
  (N, S) = (int(s) for s in fin.readline().strip().split(' '))

  fout = open('dualpal.out', 'w')
  found = 0
  val = S + 1
  while found < N:
    if is_dual_palindrome(val):
      fout.write(f'{val}\n')
      found += 1
    val += 1

if __name__ == '__main__':
  main()