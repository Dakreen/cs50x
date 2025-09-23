# DNA.py
# CS50 Problem Set 6
#
# This program identifies to whom a DNA sequence belongs.
# It reads a CSV database of individuals and their STR counts,
# then compares the longest run of each STR in a DNA sequence
# to find a matching profile.

import csv
import sys


def main():
    # Check for proper command-line usage
    if not command_line_check():
        sys.exit(1)

    # Read database file into a variable
    str_list, db_list = database_loader(sys.argv[1])

    # Read DNA sequence file into a variable
    str_seq = sequence_loader(sys.argv[2])

    # Find longest match of each STR in DNA sequence
    str_match = get_match(str_list, str_seq)

    # Check database for matching profiles
    result, name = check_db(str_match, db_list)
    if result:
        print(name)
    else:
        print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs
    for i in range(sequence_length):

        # Count consecutive runs starting at position i
        count = 0

        while True:
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If a match, increase count
            if sequence[start:end] == subsequence:
                count += 1
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    return longest_run


def command_line_check():
    # Expect program name + 2 arguments
    if len(sys.argv) == 3:
        return True
    else:
        print("Usage: dna.py database.csv sequence.txt")
        return False


def database_loader(db):
    # Open CSV file and read rows into list of dicts
    with open(db) as file:
        db_list = []
        reader = csv.DictReader(file)
        for row in reader:
            db_list.append(row)
        # fieldnames[0] = "name", others are STRs
        return reader.fieldnames[1:], db_list


def sequence_loader(seq):
    # Open sequence file and read contents into string
    with open(seq) as file:
        text = file.read()
        return text


def get_match(str_list, str_seq):
    # For each STR, compute the longest run in the sequence
    result_list = {}
    for name in str_list:
        match = longest_match(str_seq, name)
        result_list[name] = match
    return result_list


def check_db(match, db):
    # Compare STR counts against each person in database
    for i in range(len(db)):
        check = False
        count = 0
        for name in match:
            if check and count == len(match) - 1:
                if int(db[i][name]) == match[name]:
                    return check, db[i]["name"]
            elif int(db[i][name]) == match[name]:
                check = True
                count += 1
            else:
                check = False
                break
    return check, None


# Run program
main()