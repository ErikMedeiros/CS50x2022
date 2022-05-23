# https://cs50.harvard.edu/x/2022/psets/6/credit/

# Importing libraries
from re import match
from cs50 import get_string


def main():
    number = get_string("Number: ")

    # Filter user input
    while not number.isdigit():
        number = get_string("Number: ")

    # Default value
    card = "INVALID"

    if match(r"^\d{13}$|^\d{15,16}$", number):
        if luhns_algorithm(number):
            length = len(number)

            # Match card company
            if length == 13:
                if number[0] == '4':
                    card = "VISA"
            elif length == 15:
                if number[0] == '3':
                    if number[1] in ['4', '7']:
                        card = "AMEX"
            elif length == 16:
                if number[0] == '4':
                    card = "VISA"
                elif number[0] == '5':
                    if int(number[1]) in range(1, 6):
                        card = "MASTERCARD"

    print(card)


# Luhn's algorithm implementation
def luhns_algorithm(number):
    sumEven = sumOdd = 0

    for i, c in enumerate(reversed(number)):
        if i % 2 == 1:
            n = int(c) * 2
            sumOdd += n // 10 + n % 10
        else:
            sumEven += int(c)

    result = sumEven + sumOdd

    return result % 10 == 0


# Defining main
if __name__ == "__main__":
    main()
