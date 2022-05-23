# https://cs50.harvard.edu/x/2022/psets/6/readability/

from cs50 import get_string


def main():
    text = get_string("Text: ")
    grade_level = round(readability(text))

    if grade_level < 1:
        print("Before Grade 1")
    elif grade_level > 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade_level}")


def readability(text):
    letters, words, sentences = 0, 1, 0

    for c in text:
        if c.isspace():
            words += 1
        elif c in ["!", "?", "."]:
            sentences += 1
        elif c.isalpha():
            letters += 1

    # Average number of letters per 100 words
    L = (letters / words) * 100
    # Average number of sentences per 100 words
    S = (sentences / words) * 100

    # Coleman-Liau index
    return 0.0588 * L - 0.296 * S - 15.8


# Defining main
if __name__ == "__main__":
    main()
