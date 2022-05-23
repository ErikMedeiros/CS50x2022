# https://cs50.harvard.edu/x/2022/psets/6/mario/more/

from cs50 import get_int

# Validate user input
height = get_int("Height: ")

while height < 1 or height > 8:
    height = get_int("Height")

for i in range(1, height + 1):
    print(" " * (height - i) + "#" * i + "  " + "#" * i)
