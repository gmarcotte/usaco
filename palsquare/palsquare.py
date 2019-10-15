"""
ID: garrett2
LANG: PYTHON3
TASK: palsquare
"""
import math

def is_palindrome(s):
  j = len(s) - 1
  i = 0
  while True:
    if i >= j:
      return True
    if s[i] != s[j]:
      return False
    i += 1
    j -= 1

def convert_base(val, base):
  power = math.floor(math.log(val, base))
  chars = []
  while power >= 0:
    digit = math.floor(val / math.pow(base, power))
    val -= digit * math.pow(base, power)
    if digit >= 10:
      digit = chr(ord('A') + digit - 10)
    chars.append(str(digit))
    power -= 1
  return ''.join(chars)

def main():
  fin = open('palsquare.in', 'r')
  base = int(fin.readline().strip())

  fout = open('palsquare.out', 'w')
  for i in range(1, 301):
    square = convert_base(i*i, base)
    if is_palindrome(square):
      fout.write(f'{convert_base(i, base)} {square}\n')

if __name__ == '__main__':
  main()