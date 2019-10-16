"""
ID: garrett2
TASK: transform
LANG: PYTHON3
"""
import sys

def build_mat(n):
  mat = []
  for _ in range(n):
    row = []
    for _ in range(n):
      row.append(0)
    mat.append(row)
  return mat

def are_equal(mat1, mat2, n):
  for i in range(n):
    for j in range(n):
      if mat1[i][j] != mat2[i][j]:
        return False
  return True


def rot90(mat, n):
  out = build_mat(n)
  for i in range(n):
    for j in range(n):
      out[j][n - i - 1] = mat[i][j]
  return out

def reflect(mat, n):
  out = build_mat(n)
  for i in range(n):
    for j in range(n):
      out[i][n - j - 1] = mat[i][j]
  return out

def main():
  fin = open('transform.in', 'r')
  n = int(fin.readline().strip())

  val_map = {'@': 0, '-': 1}

  start = []
  for _ in range(n):
    row_raw = fin.readline().strip()
    row = [val_map[c] for c in row_raw]
    start.append(row)

  end = []
  for _ in range(n):
    row_raw = fin.readline().strip()
    row = [val_map[c] for c in row_raw]
    end.append(row)

  fout = open('transform.out', 'w')

  transformed = rot90(start, n)
  if are_equal(transformed, end, n):
    fout.write('1\n')
    return

  transformed = rot90(transformed, n)
  if are_equal(transformed, end, n):
    fout.write('2\n')
    return

  transformed = rot90(transformed, n)
  if are_equal(transformed, end, n):
    fout.write('3\n')
    return

  transformed = reflect(start, n)
  if are_equal(transformed, end, n):
    fout.write('4\n')
    return

  transformed = rot90(transformed, n)
  if are_equal(transformed, end, n):
    fout.write('5\n')
    return

  transformed = rot90(transformed, n)
  if are_equal(transformed, end, n):
    fout.write('5\n')
    return

  transformed = rot90(transformed, n)
  if are_equal(transformed, end, n):
    fout.write('5\n')
    return

  if are_equal(start, end, n):
    fout.write('6\n')
    return

  fout.write('7\n')

if __name__ == '__main__':
  main()