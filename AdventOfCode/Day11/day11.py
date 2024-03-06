from functools import reduce

input_txt = ""
with open("./input1.txt", "r") as f:
    input_txt = f.read()
    f.close()

input_txt = list(map(lambda x: [char for char in x], input_txt.splitlines()))
input1 = []

cols = []
rows = []

# go through rows
for i, row in enumerate(input_txt):
    input1.append(row)
    if reduce(lambda x, y: x and y, map(lambda x: x != "#", row)):
        rows.append(i)
        input1.append(list(map(lambda x: "!", row.copy())))
        
# go through cols

columns = list(zip(*input1))  # Transpose the grid to get the columns

print("")
    
for row in input1:
    print(row)

offset = 0

for i in range(len(columns)):
    print(i)
    if all(column != "#" for column in columns[i]):
        cols.append(i)
        for row in input1:
            row.insert(offset + i, '!')
        offset += 1

print("")
    
for row in input1:
    print(row)

# find galaxies
galaxies = []

for i in range(len(input1)):
    for j in range(len(input1[i])):
        if input1[i][j] ==  '#':
            galaxies.append((i,j))

print(galaxies)

paths = [(x, y) for x in galaxies for y in galaxies if x > y]
paths = list((map(lambda x: abs(x[1][0] - x[0][0]) + abs(x[1][1] - x[0][1]), paths)))
print(paths)
print(sum(paths))

newrow = []
offset = 0

for i, row in enumerate(rows):
    newrow.append(row + 1 + offset)
    offset += 1

# part 2

rows = newrow

print("")
print(rows)
print(cols)

newgals = []

for (row, col) in galaxies:
    off_row = 0
    off_col = 0
    for el in cols:
        if el < col:
            off_col += 10 ** 6 - 1
    for el in rows:
        if el < row:
            off_row += 10 ** 6 - 1
            print("here", off_row)
    row += off_row
    col += off_col
    print("this is row: ", off_row)
    print((row, col))
    newgals.append((row, col))

galaxies = newgals 
print(galaxies)

paths = [(x, y) for x in galaxies for y in galaxies if x > y]
paths = list((map(lambda x: abs(x[1][0] - x[0][0]) + abs(x[1][1] - x[0][1]), paths)))
print(paths)
print(sum(paths))


print("--------------")
'''
2023 Advent of Code - Day 11 (https://adventofcode.com/2023/day/11)
Solution by Sav Bell (https://github.com/savbell)
Challenge: Solve every day in a single line of Python code.
           See full progress at https://github.com/savbell/advent-of-code-one-liners
'''

# Input files not included in repo per copyright & Eric Wastl's request.
# https://www.reddit.com/r/adventofcode/wiki/faqs/copyright/inputs/
# Replace with path to your personal input file if you would like to run the code.
input_file = 'input1.txt'

# To match the format of input files for the Basilisk.
q = { 11: open(input_file).read() }

######################### PART 1: MULTI-LINE SOLUTION #########################
galaxies = [(x, y) for y, row in enumerate(q[11].strip().split()) for x, col in enumerate(row) if col == '#']

max_x = max(galaxies, key=lambda x: x[0])[0]
max_y = max(galaxies, key=lambda x: x[1])[1]

empty_rows = [y for y in range(max_y+1) if not any([y == g[1] for g in galaxies])]
empty_cols = [x for x in range(max_x+1) if not any([x == g[0] for g in galaxies])]

galaxies = [(g[0] + len([x for x in empty_cols if x < g[0]]), g[1] + len([y for y in empty_rows if y < g[1]])) for g in galaxies]

shortest_paths = {}
for g1 in galaxies:
    for g2 in galaxies:
        if g1 != g2 and (g2, g1) not in shortest_paths:
            shortest_paths[(g1, g2)] = abs(g1[0] - g2[0]) + abs(g1[1] - g2[1])
            
print('Day 11 Part 1:',sum(shortest_paths.values()))

########################## PART 1: ONE-LINE SOLUTION ##########################


######################## PART 2: MULTI-LINE SOLUTION ##########################
galaxies = [(x, y) for y, row in enumerate(q[11].strip().split()) for x, col in enumerate(row) if col == '#']

max_x = max(galaxies, key=lambda x: x[0])[0]
max_y = max(galaxies, key=lambda x: x[1])[1]

empty_rows = [y for y in range(max_y+1) if not any([y == g[1] for g in galaxies])]
empty_cols = [x for x in range(max_x+1) if not any([x == g[0] for g in galaxies])]

galaxies = [(g[0] + (len([x for x in empty_cols if x < g[0]]) * 999999), g[1] + (len([y for y in empty_rows if y < g[1]]) * 999999)) for g in galaxies]

shortest_paths = {}
for g1 in galaxies:
    for g2 in galaxies:
        if g1 != g2 and (g2, g1) not in shortest_paths:
            shortest_paths[(g1, g2)] = abs(g1[0] - g2[0]) + abs(g1[1] - g2[1])
print('Day 11 Part 2:',sum(shortest_paths.values()))

