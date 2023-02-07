def power(x, y):
    y -= 1
    if y<0:
        return 1
    else:
        if y == 0:
            return x
        else:
            z = power(x, y)
            z *= x
    return z
