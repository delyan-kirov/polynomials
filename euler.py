# %% Problem 1

# summa = 0
# for i in range(1000):
#     if i % 3 == 0 or i % 5 == 0:
#         summa += i
#
# print(summa)

# %% Problem 2

# def fibs(num: int):
#     if num == 0:
#         return 1
#     elif num == 1:
#         return 2
#     else:
#         return (fibs(num - 1) + fibs(num - 2))
#
# summa = 0
#
# for i in range(100):
#     curr = fibs(i)
#     if curr % 2 == 0:
#         summa += curr
#     if curr >= 4 * 10 ** 6:
#         break
#
# print("result is: ", summa)

# %% Problem 3

# num = 13195
# num = 600851475143
# factors: List[int] = []
#
# def is_prime(n: int):
#     match n:
#         case 2:
#             return True
#         case 3:
#             return True
#         case _:
#             for i in range(2, int(n ** 0.5 + 1)):
#                 if (n / i) % 1 == 0:
#                     return False
#             return True
#
# for i in range(2, int(num ** 0.5) + 1):
#     if (num / i) % 1 == 0:
#         if is_prime(i):
#             factors.append(i)
#
# print(max(factors))

# %% Problem 4


# def check_palindrome(n: int):
#     return str(n) == str(n)[::-1]
#
# palindromes = []
#
# for i in range(100, 1000):
#     for j in range(100, 1000):
#         prod = i * j
#         if check_palindrome(prod):
#             palindromes.append(prod)
#
# print(palindromes)
# print(max(palindromes))

# %% Problem 5

# def is_div_1_20(n: int):
#     if (n % 9 == 0 and
#         n % 5 == 0 and
#         n % 7 == 0 and
#         n % 11 == 0 and
#         n % 13 == 0 and
#         n % 16 == 0 and
#         n % 17 == 0 and
#         n % 19 == 0):
#         return True
#     else:
#         return False
# i = 2
# while True:
#     if is_div_1_20(i):
#         print(i)
#         exit()
#     else:
#         i += 1

# %% Problem 6

# sum_of_squares = sum(map(lambda x: x ** 2, range(1, 101)))
# square_of_sum = sum(range(1, 101)) ** 2
#
# print(sum_of_squares)
# print(square_of_sum)
# print(square_of_sum - sum_of_squares)

# %% Problem 7

# def is_prime(n: int):
#     match n:
#         case 2:
#             return True
#         case 3:
#             return True
#         case _:
#             for i in range(2, int(n ** 0.5 + 1)):
#                 if (n / i) % 1 == 0:
#                     return False
#             return True
#
# i = 0
# prime_count = 0
#
# while prime_count != 10001 + 1:
#     i += 1
#     if is_prime(i):
#         prime_count += 1
#
# print(i)

# %% Problem 10

# def is_prime(n: int):
#     match n:
#         case 1:
#             return False
#         case 2:
#             return True
#         case 3:
#             return True
#         case _:
#             for i in range(2, int(n ** 0.5 + 1)):
#                 if (n / i) % 1 == 0:
#                     return False
#             return True
#
# primes = []
#
# for i in range(1, 2 * 10 ** 6 + 1):
#     if is_prime(i):
#         primes.append(i)
#
# print(sum(primes))


# %% Problem

# 1 2 3 4  5  6  7  8
# 1 3 6 10 15 21 28 36

# triags = [1]
#
# import subprocess
#
# def find_facs_len(num: int):
#     bash_command = "factor " + str(num)
#     output = subprocess.check_output(bash_command, shell=True, encoding="utf-8").strip()
#     output = output[output.find(":") + 2 :].split()
#     return len(output) + 1
#
#
# for i in range(1, 10**6):
#     triags.append(triags[-1] + i + 1)
#
# print("Finished finding triags")
#
# for i, num in enumerate(triags, start= 10 ** 5):
#     if find_facs_len(num) == 500:
#         print("Answer is: ", i)
#         exit()


# import concurrent.futures
# import subprocess
#
# triags = [1]
#
# def find_facs_len(num: int):
#     bash_command = "factor " + str(num)
#     output = subprocess.check_output(bash_command, shell=True, encoding="utf-8").strip()
#     output = output[output.find(":") + 2 :].split()
#     return len(output) + 1
#
# for i in range(1, 10**8):
#     triags.append(triags[-1] + i + 1)
#
# print("Finished finding triags")
#
# # Define a function to find the answer in a range of indices
# def find_answer_range(start, end):
#     for i, num in enumerate(triags[start:end], start=start):
#         if find_facs_len(num) == 500:
#             return i
#     return None
#
# # Split the list into chunks for parallel processing
# chunk_size = len(triags) // 4  # Split the list into 4 chunks
#
# # Define a function to process a chunk of the list
# def process_chunk(start, end):
#     return find_answer_range(start, end)
#
# # Create a ThreadPoolExecutor with a maximum of 4 worker threads
# with concurrent.futures.ThreadPoolExecutor(max_workers=4) as executor:
#     # Submit tasks to the executor
#     futures = [executor.submit(process_chunk, i, min(i + chunk_size, len(triags))) for i in range(0, len(triags), chunk_size)]
#
#     # Retrieve results from the futures
#     for future in concurrent.futures.as_completed(futures):
#         result = future.result()
#         if result is not None:
#             print("Answer is: ", result)
#             break


