def make_change(amount):
    """
    de1 is all changes for integer part while de2 is for decimal part
    for each part, you can call computation to calculate the smallest amount for each change
    """
    de1 = [100.00,50.00,20.00,10.00,5.00,2.00,1.00]
    de2 = [0.25, 0.10, 0.05, 0.01]

    integer,n = computation(de1,amount)
    if n>0:
        decimal,n = computation(de2, n)
        integer.update(decimal)

    changes = integer.copy()

    return changes

def computation(de,m):
    d = {}

    for i in range(0, len(de)):
        a = m // de[i]
        m = round(m - a * de[i],2)
        if a != 0.0:
            d[de[i]] = int(a)

    return d, m

def print_change(change):
    """
    Print change and the number of it.
    """
    
    for symbol in change.items():
        print("${:.2f}: {}".format(symbol[0], symbol[1]))
