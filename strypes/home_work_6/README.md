# Structure

The exercises for arrays are in the `Array.h` file, similarly for the matrix
problems.

For the anagram exercise, see the file `Text.cpp`.

Tests are available in `test.cpp`.

# Run

## Posix

### Option easy

```bash
chmod +x ./test.cpp
./test.cpp
```

### Option manual

1. Using gcc

```bash
# gcc
g++ test.cpp
```

2. Using clang

```bash
clang++ test.cpp
./a.out
```

## Windows

Try this:

1. Go to this
   page[Git page](https://github.com/delyan-kirov/public/tree/master/strypes/home_work_6)
   and download the git repo
2. Open terminal inside `GameOs`
3. Run test.exe

# Expected results

```
--- ex 1: Merge Sorted Arrays ---

First Array:
[ 1 3 5 ]

Second Array:
[ 2 4 6 11 ]

Merged Array:
[ 1 2 3 4 5 6 11 ]

--- ex 2: Find Majority Element ---

Example 1
Array:
[ 1 2 3 1 1 1 4 ]

The majority element is: 1

Example 2
Array:
[ 1 2 3 4 5 6 7 ]

There is no majority element.

--- ex 3: Check Anagrams ---

"listen" and "silent" are anagrams.
"abc" and "xyz" are not anagrams.

--- ex 4: Rotate Matrix ---

Example 1
Original Matrix:
1 2 3
4 5 6
7 8 9
Rotated Matrix:
7 4 1
8 5 2
9 6 3

Example 2
Original Matrix:
1 2
3 4
Rotated Matrix:
3 1
4 2

--- ex 5: Multiply Matrices ---

Example 1:
Matrix 1:
1 2
3 4
Matrix 2:
5 6
7 8
Result Matrix:
19 22
43 50

Example 2:
Matrix 1:
1 0
0 1
Matrix 2:
1 1
1 1
Result Matrix:
1 1
1 1
```
