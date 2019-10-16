"""
ID: garrett2
TASK: namenum
LANG: PYTHON3
"""

MAPPING = {
  '2': ['A', 'B', 'C'],
  '3': ['D', 'E', 'F'],
  '4': ['G', 'H', 'I'],
  '5': ['J', 'K', 'L'],
  '6': ['M', 'N', 'O'],
  '7': ['P', 'R', 'S'],
  '8': ['T', 'U', 'V'],
  '9': ['W', 'X', 'Y'],
}

def iterate(chars, i, s):
  if len(s) == len(chars):
    yield ''.join(chars)
  else:
    for c in MAPPING[s[i]]:
      chars.append(c)
      for res in iterate(chars, i+1, s):
        yield res
      chars.pop()
  

def main():
  fin = open('namenum.in', 'r')
  s = fin.readline().strip()
  fout = open('namenum.out', 'w')

  for c in s:
    if MAPPING.get(c) is None:
      fout.write('NONE\n')
      return

  fdict = open('dict.txt', 'r')
  all_names = set([l.strip() for l in fdict.readlines()])

  valid_names = []
  for name in iterate([], 0, s):
    if name in all_names:
      valid_names.append(name)

  valid_names.sort()

  if valid_names:
    fout.write('\n'.join(valid_names))
    fout.write('\n')
  else:
    fout.write('NONE\n')






if __name__ == '__main__':
  main()