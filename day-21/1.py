f1 = open("1.txt", "r")

monkeys: dict[str, str] = dict()
result_monkey = 0
for line in f1.readlines():
    name, value = line.strip().split(":")

    # how many monkeys yell the result of a math operation, excluding the root
    if not value.isdecimal() and name != "root":
        result_monkey += 1

    monkeys[name] = value.strip()

expression = monkeys["root"]
# replace monkey's name with its operation
for i in range(result_monkey):
    monkey_name = ""
    start_index = -1
    end_index = -1
    for i in range(len(expression)):
        if expression[i].isalpha():
            monkey_name += expression[i]
            if start_index == -1:
                start_index = i
        if not expression[i].isalpha() and start_index != -1:
            end_index = i
            break
    if end_index == -1:
        end_index = len(expression)
    expression = expression[:start_index] + \
        f"({monkeys[monkey_name]})" + expression[end_index:]
print(int(eval(expression)))
