f1 = open("2.txt", "r")
monkeys: dict[str, str] = dict()
result_monkey = 0
for line in f1.readlines():
    name, value = line.strip().split(":")
    monkeys[name] = value.strip()

# tranform data
expression_1, expression_2 = monkeys["root"].split("+")
expression_1 = expression_1.strip()
expression_2 = expression_2.strip()

names_counter = 1
search_start_index = 0
while names_counter > 0:
    # finding closest name
    monkey_name = ""
    start_index = -1
    end_index = -1
    for i in range(search_start_index, len(expression_1)):
        if expression_1[i].isalpha():
            monkey_name += expression_1[i]
            if start_index == -1:
                start_index = i
        if not expression_1[i].isalpha() and start_index != -1:
            end_index = i
            break
    if end_index == -1:
        end_index = len(expression_1)

    # do not replace humn with its value
    if monkey_name == "humn":
        search_start_index = end_index
        names_counter -= 1
        continue

    expression_1 = expression_1[:start_index] + \
        f"({monkeys[monkey_name]})" + expression_1[end_index:]

    # if received expression has other names
    if not monkeys[monkey_name].isdecimal():
        names_counter += 2
    names_counter -= 1

names_counter = 1
search_start_index = 0
while names_counter > 0:
    # finding closest name
    monkey_name = ""
    start_index = -1
    end_index = -1
    for i in range(search_start_index, len(expression_2)):
        if expression_2[i].isalpha():
            monkey_name += expression_2[i]
            if start_index == -1:
                start_index = i
        if not expression_2[i].isalpha() and start_index != -1:
            end_index = i
            break
    if end_index == -1:
        end_index = len(expression_2)

    # do not replace humn with its value
    if monkey_name == "humn":
        search_start_index = end_index
        names_counter -= 1
        continue

    expression_2 = expression_2[:start_index] + \
        f"({monkeys[monkey_name]})" + expression_2[end_index:]

    # if received expression has other names
    if not monkeys[monkey_name].isdecimal():
        names_counter += 2
    names_counter -= 1

# expression_1 should always has "humn" in it
if search_start_index != 0:
    expression_1, expression_2 = expression_2, expression_1

target = eval(expression_2)
start_value = eval(expression_1.replace(
    "humn", monkeys["humn"]))
# check if given linear function is ascending
is_ascending_function = start_value < eval(
    expression_1.replace("humn", str(int(monkeys["humn"]) + 1)))

# finding a number, which humn need to yell using binary search
MAX_VALUE = 10**20
MIN_VALUE = -1 * MAX_VALUE
if is_ascending_function:
    if start_value < target:
        low = int(monkeys["humn"])
        high = MAX_VALUE
    else:
        high = int(monkeys["humn"])
        low = MIN_VALUE
    # binary search
    while True:
        current_num = (low + high) // 2
        current_value = eval(expression_1.replace("humn", str(current_num)))
        if current_value == target:
            print(current_num)
            break
        elif current_value < eval(expression_2):
            low = current_num + 1
        elif current_value > eval(expression_2):
            high = current_num - 1
else:
    if start_value < target:
        high = int(monkeys["humn"])
        low = MIN_VALUE
    else:
        low = int(monkeys["humn"])
        high = MAX_VALUE
    # binary search
    while True:
        current_num = (low + high) // 2
        current_value = eval(expression_1.replace("humn", str(current_num)))
        if current_value == target:
            print(current_num)
            break
        elif current_value < eval(expression_2):
            high = current_num - 1
        elif current_value > eval(expression_2):
            low = current_num + 1
