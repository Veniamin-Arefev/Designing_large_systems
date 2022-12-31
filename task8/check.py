input_file = []
output_file = []

with open("input.txt") as file:
    input_file = list(sorted(file.read().split('\n')))

with open("output.txt") as file:
    output_file = list(sorted(file.read().split('\n')))

print(all([input_file[i] == output_file[i] for i in range(len(input_file))]))
