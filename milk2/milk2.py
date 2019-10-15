"""
ID: garrett2
TASK: milk2
LANG: PYTHON3
"""

def main():
  fin = open('milk2.in', 'r')
  N = int(fin.readline().strip())
  starts = []
  ends = []
  for _ in range(N):
    (start, end) = (int(x) for x in fin.readline().strip().split(' '))
    starts.append(start)
    ends.append(end)
  starts.sort()
  ends.sort()

  max_milking = 0
  max_no_milking = 0

  start_i = 0
  end_i = 0

  curr_start = None
  num_milking = 0

  while start_i < N or end_i < N:
    if start_i >= N or starts[start_i] > ends[end_i]:
      num_milking -= 1
      if num_milking == 0:
        milking = ends[end_i] - curr_start
        if milking > max_milking:
          max_milking = milking
        curr_start = ends[end_i]
      end_i += 1
    elif starts[start_i] < ends[end_i]:
      if num_milking == 0:
        if curr_start is not None:
          no_milking = starts[start_i] - curr_start
          if no_milking > max_no_milking:
            max_no_milking = no_milking
        curr_start = starts[start_i]
      num_milking += 1
      start_i += 1
    else:
      start_i += 1
      end_i += 1

  fout = open('milk2.out', 'w')
  fout.write(f'{max_milking} {max_no_milking}\n')


if __name__ == '__main__':
  main()