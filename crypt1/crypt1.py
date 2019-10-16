"""
ID: garrett2
TASK: crypt1
LANG: PYTHON3
"""
import math

def is_solution(a, b, c, d, e, digits):
  ec = e * c
  if ec % 10 not in digits:
    return False
  ec_carry = math.floor(ec / 10)
  eb = e * b + ec_carry
  if eb % 10 not in digits:
    return False
  eb_carry = math.floor(eb / 10)
  ea = e * a + eb_carry
  if ea not in digits:
    return False

  dc = d * c
  if dc % 10 not in digits:
    return False
  dc_carry = math.floor(dc / 10)
  db = d * b + dc_carry
  if db % 10 not in digits:
    return False
  db_carry = math.floor(db / 10)
  da = d * a + db_carry
  if da not in digits:
    return False

  p3 = eb % 10 + dc % 10
  if p3 % 10 not in digits:
    return False
  p3_carry = math.floor(p3 / 10)
  p2 = ea + db % 10 + p3_carry
  if p2 % 10 not in digits:
    return False
  p2_carry = math.floor(p2 / 10)
  p1 = da + p2_carry
  if p1 not in digits:
    return False
  
  return True
  

  

def main():
  fin = open('crypt1.in', 'r')
  fin.readline() # skip num digits
  digits = set([int(s) for s in fin.readline().strip().split(' ')])

  num_solutions = 0
  for c in digits:
    for e in digits:
      for d in digits:
        for b in digits:
          for a in digits:
            if is_solution(a, b, c, d, e, digits):
              print(f'Solution: {a}{b}{c} x {d}{e}\n')
              num_solutions += 1

  fout = open('crypt1.out', 'w')
  fout.write(f'{num_solutions}\n')

if __name__ == '__main__':
  main()
