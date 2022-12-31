import random
from collections import defaultdict

my_nodes = list(random.choices(range(0, 2 * 32), k=10 ** 6))

my_values = dict()

while (len(my_values)) < 10 ** 6 * 5:
    if (len(my_values) % 100 == 0):
        print(len(my_values))
    my_values[tuple(random.choices(my_nodes, k=2))] = random.randint(0, 2 ** 8 - 1)

with open("input.txt", 'w') as file:
    for nodes, value in my_values.items():
        file.write(f"{nodes[0]}\t{nodes[1]}\t{value}\n")
