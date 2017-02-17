import matplotlib.pyplot as plt
import random

SIZE = 40
with open('input.txt') as f:
    n = [int(x) for x in next(f).split()]
    edges = []
    for line in f:
        edges.append([int(x) for x in line.split()])

points = dict()

for edge in edges:
    if edge[0] not in points:
        points[edge[0]] = (random.randint(1, SIZE), random.randint(1, SIZE))
    if edge[1] not in points:
        points[edge[1]] = (random.randint(1, SIZE), random.randint(1, SIZE))

output = open("output.txt", "w")
print(len(points), file=output)
for value in points.keys():
    plt.plot(points[value][0], points[value][1], "ro")
    print(value, points[value][0], points[value][1], file=output)
output.close()

for edge in edges:
    x, y = points[edge[0]][0], points[edge[0]][1]
    x1, y1 = points[edge[1]][0], points[edge[1]][1]
    plt.plot([x, x1], [y, y1], 'k-', lw=2)
plt.show()
