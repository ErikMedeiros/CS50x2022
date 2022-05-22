# https://cs50.harvard.edu/x/2022/psets/6/dna/

from csv import DictReader
from sys import argv, exit


def main():
    # Check for command-line usage
    if len(argv) != 3:
        print("Usage: python dna.py list.csv sequence.txt")
        exit(-1)

    # Read database file into a variable
    people = []
    with open(argv[1]) as csv_file:
        reader = DictReader(csv_file)

        for row in reader:
            person = row

            for key, value in row.items():
                if value.isdigit():
                    person[key] = int(value)

            people.append(person)

    # Read DNA sequence file into a variable
    with open(argv[2]) as txt_file:
        sequence = txt_file.read().rstrip("\n")

    # Find longest match of each STR in DNA sequence
    counts = {}
    for key in reader.fieldnames[1:]:
        counts[key] = longest_match(sequence, key)

    # Check database for matching profiles
    name = "No match"
    for person in people:
        iterator = iter(person)
        next(iterator)

        match = True
        for key in iterator:
            match = match and person[key] == counts[key]

            if not match:
                break

        if match:
            name = person["name"]
            break

    print(name)
    exit(0)


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
