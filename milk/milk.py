"""
ID: garrett2
TASK: milk
LANG: PYTHON3
"""

def main():
  fin = open('milk.in', 'r')
  (num_units, num_farmers) = (int(s) for s in fin.readline().strip().split(' '))
  market = {}
  for _ in range(num_farmers):
    (price, amt) = (int(s) for s in fin.readline().strip().split(' '))
    market.setdefault(price, 0)
    market[price] += amt

  bought = 0
  cost = 0
  for price in sorted(market.keys()):
    if market[price] <= num_units - bought:
      bought += market[price]
      cost += market[price] * price
    else:
      cost += (num_units - bought) * price
      bought = num_units
    if bought >= num_units:
      break
  
  fout = open('milk.out', 'w')
  fout.write(f'{cost}\n')

if __name__ == '__main__':
  main()