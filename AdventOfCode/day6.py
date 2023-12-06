import functools

def calcDistance(time, hold_time):
    new_time = time - hold_time
    if new_time < 0: 
        new_time = 0
    return (new_time * hold_time)

# print(calcDistance(7, 1))

def game_margin(time, distance):
    output = []
    sol = []
    for i in range(0, distance):
        print(calcDistance(time,i))
        if(calcDistance(time,i) == 0 and i > 10):
            break
        output.append(calcDistance(time, i))
    for i in range(0, len(output)):
        if output[i] > distance:
            sol.append(i)
    # print(sol)
    return len(sol)

def solution(times, distances):
    solution = []
    for i in range (0, len(distances)):
        solution.append(game_margin(times[i], distances[i]))
    sol1 = functools.reduce((lambda x, y: x * y), solution)
    return(sol1)

# times = [7, 15, 30]
# distances = [9, 40, 200]

# times = [50, 74, 86, 85]
# distances = [242, 1017, 1691, 1252]

times = [50748685]
distances = [242101716911252]

print(solution(times,distances))
