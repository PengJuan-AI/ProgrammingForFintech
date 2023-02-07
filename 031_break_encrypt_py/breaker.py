from curses.ascii import isalpha
import sys
from sys import argv

def breaker(s):

    dict = {}
    while True:
        c = f.read(1)
        if not c: break
        dict = count_word(dict,c)

    l = sorted(dict, key=dict.get, reverse=True)
    encrypt = l[0]
    if encrypt:
        e = 'e'
        e = ord(e)
        e -= ord('a')
        encrypt = ord(encrypt)
        encrypt -= ord('a')
        key = encrypt - e%26
    if key<0:
        key += 26
    if dict[l[0]] == dict[l[1]]:
        raise Exception(exit(1))

    print(key)
    return key


def count_word(dict, word):
    if word.isalpha():
        dict[word] = dict.get(word,0) + 1
    return dict

if __name__ == '__main__':
    if len(argv) != 2:
        print("Usage: python3 breaker.py input_file_name")
        sys.exit(1)

    try:
        with open(argv[1]) as f:
            key = breaker(f)
            assert 0<=key<26
    except FileNotFoundError:
        print("Unable to find:", argv[1])
        exit(1)
    except Exception as err:
        print("Unknown error:", err)
        print("Error Type:", type(err))
        exit(1)
