from dataclasses import dataclass, field
from typing import Callable
from itertools import product


def equation_add(a: int, b: int):
    return a + b


def equation_mul(a: int, b: int):
    return a * b


def equation_cct(a: int, b: int):
    return int(f"{a}{b}")


@dataclass
class Operation:
    ops: list[Callable]


@dataclass
class Equation:
    answer: int
    numbers: list[int]
    size: int

    def __str__(self):
        return f"answer: {self.answer}, array: {self.numbers}"


@dataclass
class Equation_list:
    eqs: list[Equation] = field(default_factory=list)
    index: int = 0

    def __iter__(self):
        return self

    def __next__(self):
        try:
            result = self.eqs[self.index]
        except IndexError:
            raise StopIteration
        self.index += 1
        return result


def apply_operations(numbers: list[int], operations) -> int:
    if len(operations) + 1 != len(numbers):
        raise ValueError("Number of operations must be one less than number of numbers")
    result = numbers[0]
    for i, op in enumerate(operations):
        result = op(result, numbers[i + 1])
    return result


equations = Equation_list()

with open("./input.txt", "r") as f:
    for line in f.readlines():
        answer, rest = line.split(":")
        numbers = [int(x) for x in rest.strip().split(" ")]
        size = len(numbers)
        eq = Equation(answer=int(answer), numbers=numbers, size=size)
        equations.eqs.append(eq)

list_of_ops = [
    equation_add,
    equation_mul,
]

equations_not_found = Equation_list()
found_part1 = 0
found_part2 = 0
for item in equations:
    ops = list(product(list_of_ops, repeat=item.size - 1))
    for op in ops:
        result = apply_operations(item.numbers, op)
        if result == item.answer:
            found_part1 += result
            break

    equations_not_found.eqs.append(item)

list_of_ops.append(equation_cct)

for item in equations_not_found:
    ops = list(product(list_of_ops, repeat=item.size - 1))
    for op in ops:
        result = apply_operations(item.numbers, op)
        if result == item.answer:
            found_part2 += result
            break


print(f"Part1: {found_part1}")
print(f"Part2: {found_part2}")
