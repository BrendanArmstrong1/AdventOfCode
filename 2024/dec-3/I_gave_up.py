import re

mul_regex = re.compile(r"mul\((\d+),(\d+)\)", re.MULTILINE)

# Part 1
with open("./input.txt", "r") as f:
    lines = f.readlines()
    sum = 0
    for line in lines:
        matches = mul_regex.findall(line)
        for match in matches:
            sum += int(match[0]) * int(match[1])

    print(sum)

print("don't()".find("do()"))

# Part 2
with open("./input.txt", "r") as f:
    lines = f.readlines()
    sum = 0
    for line in lines:
        dos = 0
        find = 0
        print(f"new line of len {len(line)}")

        # initial search
        dons = line.find("don't()")
        matches = mul_regex.findall(line[dos:dons])
        for match in matches:
            sum += int(match[0]) * int(match[1])

        # body search
        while (find := line[dons:].find("do()")) != -1:
            dos = find + 4 + dons
            dons = dos + line[dos:].find("don't()")
            if dons < dos:
                break
            matches = mul_regex.findall(line[dos:dons])
            for match in matches:
                sum += int(match[0]) * int(match[1])

        # final search
        matches = mul_regex.findall(line[dos:])
        for match in matches:
            sum += int(match[0]) * int(match[1])



    print(sum)
