def make_change(amount):
    """
    de is denominations for changes ordered ascending
    computation() is the function where recursion is happening to calculate numbers
    """
    de = [0.01, 0.05, 0.1, 0.25, 1.0, 2.0, 5.0, 10.0, 20.0, 50.0, 100.0]
    dict = {}

    changes = computation(de,amount, dict)
    return changes

# where recursion happens
def computation(de,m,dict):

    if de:
        n = de.pop()
        a = int(m // n)
        m = round(m - a * n,2)
        if a != 0.0:
            dict[n] = int(a)
        dict = computation(de, m, dict)
    else: return dict

    return dict

def print_change(change):
    """
    Print change and the number of it.
    """
    for symbol in change.items():
        print("${:.2f}: {}".format(symbol[0], symbol[1]))
