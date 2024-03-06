from functools import reduce

input_txt = ""
with open("./input.txt", "r") as f:
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

for i, row in enumerate(rows):
    row += 1

print("")
print(rows)
print(cols)

# part 2

