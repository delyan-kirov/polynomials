#    [1] 
#   [1 1]
#  [1 2 1]
# [1 3 3 1]

# import sys

# Set the new recursion limit
# sys.setrecursionlimit(5000000)

from typing import List


def pascal(n: int):
    if n == 0:
        return [1]
    if n == 1:
        return [1, 1]
    nums = (n - 1) * [1]
    pascal_prev = pascal((n-1))
    for ind, _ in enumerate(nums):
        nums[ind] = pascal_prev[ind + 1] + pascal_prev[ind]
    return [1] + nums + [1]

# print(pascal(10000))

for i in range(10):
    print(*pascal(i))

def gcd(m: int, n: int):
    if m == 0:
        return n
    else:
        return gcd(n % m, m)

print(gcd(18, 42))  # Example usage

print(gcd(2, 3))

# ***

