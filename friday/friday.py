"""
ID: garrett2
TASK: friday
LANG: PYTHON3
"""

def days_per_month(month, year):
  if month in {1, 3, 5, 7, 8, 10, 12}:
    return 31
  elif month in {4, 6, 9, 11}:
    return 30
  elif year % 4 == 0 and (year % 100 != 0 or year % 400 == 0):
    return 29
  else:
    return 28

def main():
  fin = open('friday.in', 'r')
  N = int(fin.readline().strip())

  freq = [0, 0, 0, 0, 0, 0, 0]

  # Monday
  first_day = 2

  for year in range(N):
    for month in range(1, 13):
      thirteenth_day = (first_day + 12) % 7
      freq[thirteenth_day] += 1
      first_day = (first_day + days_per_month(month, 1900 + year)) % 7

  fout = open('friday.out', 'w')
  fout.write(' '.join([str(x) for x in freq]))
  fout.write('\n')


if __name__ == '__main__':
  main()