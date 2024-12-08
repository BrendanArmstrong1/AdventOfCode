from dataclasses import dataclass, field
from itertools import combinations


@dataclass
class Matrix:
    _cols: int = 0
    _rows: int = -1
    number_of_antinodes: int = 0
    seen_antinodes: set[tuple[int, int]] = field(default_factory=set)
    antenna_dict: dict[str, list[tuple[int, int]]] = field(default_factory=dict)
    mat_antenna: list[list[str]] = field(default_factory=list)
    mat_antinod: list[list[str]] = field(default_factory=list)

    @property
    def cols(self):
        return self._cols

    @property
    def rows(self):
        return self._rows

    @cols.setter
    def cols(self, size: int):
        self._cols = size

    @rows.setter
    def rows(self, size: int):
        self._rows = size

    def matrix_initialize_row(self):
        self.mat_antenna.append([" " for _ in range(self.cols + 1)])
        self.mat_antinod.append([" " for _ in range(self.cols + 1)])
        self.rows += 1

    def set_antenna(self, idx, value):
        if not isinstance(idx, tuple):
            idx = tuple(idx)
        x, y = idx
        self.mat_antenna[y][x] = value

    def set_antinode(self, idx, value):
        if not isinstance(idx, tuple):
            idx = tuple(idx)
        x, y = idx
        if x < 0 or x > self.cols:
            return
        if y < 0 or y > self.rows:
            return

        if value == "#":
            if idx not in self.seen_antinodes:
                self.number_of_antinodes += 1
                self.seen_antinodes.add(idx)
        self.mat_antinod[y][x] = value

    def set_both(self, idx, antenna, antinode):
        self.set_antenna(idx, antenna)
        self.set_antinode(idx, antinode)

    def print_antenna(self):
        for i in range(self.rows):
            print(self.mat_antenna[i])

    def print_antinode(self):
        for i in range(self.rows):
            print(self.mat_antinod[i])

    def index_antennas(self):
        for j, row in enumerate(self.mat_antenna):
            for i, col in enumerate(row):
                if col != ".":
                    coords = self.antenna_dict.setdefault(col, [])
                    coords.append((i, j))

    def calculate_antinode_coords(
        self, first: tuple[int, int], second: tuple[int, int]
    ) -> list[tuple[int, int]]:
        node_locations = []

        x1, y1 = first
        x2, y2 = second

        node_locations.append((x1, y1))
        node_locations.append((x2, y2))

        delta_x = -((x2 - x1) // -1)
        delta_y = -((y2 - y1) // -1)

        new_x = x1 - delta_x
        new_y = y1 - delta_y
        node_locations.append((new_x, new_y))

        while (
            (new_x := new_x - delta_x) >= 0
            and new_x <= self.cols
            and (new_y := new_y - delta_y) >= 0
            and new_y <= self.rows
        ):
            node_locations.append((new_x, new_y))

        new_x = x2 + delta_x
        new_y = y2 + delta_y
        node_locations.append((new_x, new_y))

        while (
            (new_x := new_x + delta_x) >= 0
            and new_x <= self.cols
            and (new_y := new_y + delta_y) >= 0
            and new_y <= self.rows
        ):
            node_locations.append((new_x, new_y))


        return node_locations

    def create_antinodes(self):
        for coords in self.antenna_dict.values():
            # print(coords)
            combos = list(combinations(coords, 2))
            for combo in combos:
                new_coords = self.calculate_antinode_coords(combo[0], combo[1])
                # print(f"{combo} -> {new_coords}")
                for new_coord in new_coords:
                    self.set_antinode(new_coord, "#")
            # print("")


mat = Matrix()

with open("./input.txt", "r") as f:
    for jdx, line in enumerate(f.readlines()):
        line = line.strip()
        mat.cols = len(line) - 1
        mat.matrix_initialize_row()
        for idx, char in enumerate(line):
            mat.set_both((idx, jdx), char, ".")


mat.index_antennas()
mat.create_antinodes()
print(mat.number_of_antinodes)
