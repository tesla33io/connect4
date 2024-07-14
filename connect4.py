#!/usr/bin/env python3

from typing import List
import random as rnd

from rich.console import Console
from rich.table import Table
from rich.text import Text
from rich import box

class Board:

    cols:       int # Width
    rows:       int # Height
    __board:    List[List[int]]
    con:        Console
    s_empty:    str = "" # Style of empty cells
    s_p1:       str = "bold red" # Style of Player 1 cells
    s_p2:       str = "bold yellow" # Style of Player 2 cells
    c_empty:    str = " " # Char representing empty space
    c_p1:       str = "x" # Char representing Player 1
    c_p2:       str = "+" # Char representing Player 2
    
    def __init__(self, rows: int = 6, cols: int = 7) -> None:
        self.rows = rows
        self.cols = cols
 
        self.__board = [[0 if rnd.randint(0, 100) < 50 else rnd.choice([1, 2]) for _ in range(self.cols)] for _ in range(self.rows)]

        self.con = Console()

    def display_board(self) -> None:
        table = Table(show_header=False, show_edge=True, box=box.SQUARE,
                      border_style="blue", row_styles=["", ""])

        for _ in range(self.cols):
            table.add_column(justify="center")

        for row in self.__board:
            f_row = []
            for cell in row:
                match cell:
                    case 0:
                        f_row.append(Text(self.c_empty, style=self.s_empty))
                    case 1:
                        f_row.append(Text(self.c_p1, style=self.s_p1))
                    case 2:
                        f_row.append(Text(self.c_p2, style=self.s_p2))
            table.add_row(*f_row)

        self.con.print(table)

if __name__ == "__main__":
    b = Board(10, 10)
    b.display_board()
