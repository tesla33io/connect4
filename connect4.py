#!/usr/bin/env python3

from typing import List, Literal
import random as rnd
import copy

from rich.console import Console
from rich.table import Table
from rich.text import Text
from rich import box

class Board:

    cols:       int # Width
    rows:       int # Height
    __board:    List[List[int]]
    __prev:     List[List[int]] # prev board state
    con:        Console
    s_empty:    str = "" # Style of empty cells
    s_p1:       str = "bold red" # Style of Player 1 cells
    s_p2:       str = "bold yellow" # Style of Player 2 cells
    s_new:      str = "bold green" # Style of most recent move
    c_empty:    str = " " # Char representing empty space
    c_p1:       str = "x" # Char representing Player 1
    c_p2:       str = "+" # Char representing Player 2
    
    def __init__(self, rows: int = 6, cols: int = 7) -> None:
        self.rows = rows
        self.cols = cols
 
        # self.__board = [[0 if rnd.randint(0, 100) < 50 else rnd.choice([1, 2]) for _ in range(self.cols)] for _ in range(self.rows)]
        self.__board = [[0 for _ in range(self.cols)] for _ in range(self.rows)]
        self.__prev = self.__board

        self.con = Console()

    def display_board(self) -> None:
        table = Table(show_header=False, show_edge=True, box=box.SQUARE,
                      border_style="blue", row_styles=["", ""])

        for _ in range(self.cols):
            table.add_column(justify="center")

        for (ir, row) in enumerate(self.__board):
            f_row = []
            for (ic, cell) in enumerate(row):
                if self.__prev[ir][ic] != self.__board[ir][ic]:
                    f_row.append(Text(self.c_p1 if cell == 1 else self.c_p2 if cell == 2 else self.c_empty, style=self.s_new))
                    continue
                match cell:
                    case 0:
                        f_row.append(Text(self.c_empty, style=self.s_empty))
                    case 1:
                        f_row.append(Text(self.c_p1, style=self.s_p1))
                    case 2:
                        f_row.append(Text(self.c_p2, style=self.s_p2))
            table.add_row(*f_row)

        self.con.print(table)

    def make_a_turn(self, player: Literal[1, 2], col: int) -> bool:
        self.__prev = copy.deepcopy(self.__board)
        success = False
        if col > self.cols or col < 0:
            raise Exception(f"Invalid column number {col}")
        for row in range(self.rows):
            if self.__board[self.rows - row - 1][col] == 0:
                self.__board[self.rows - row - 1][col] = player
                success = True
                break
        if not success:
            self.con.print(f"Column {col} is already full, peek another one!")
        return success

    def get_board(self) -> List[List[int]]:
        return self.__board


if __name__ == "__main__":
    b = Board(10, 10)
    player = 1
    while True:
        b.con.clear()
        b.display_board()
        b.con.print(f"Player {player}'s turn")
        col = int(input("col? "))
        if not b.make_a_turn(player, col):
            continue
        player = 2 if player == 1 else 1
