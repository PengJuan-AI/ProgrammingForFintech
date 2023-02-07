def compute_average(l):
    """
    Computes the average of list, ignoring any entries that 
    are not numbers (floats or ints)

    Args:
    l(list): list of items to compute the average
 
    returns:
    average of the numbers in the list
    
    raises:
    ValueError if the argument is not a list or if the list does not contain any numbers
    """
    # TODO: Implement function
    total = 0
    num = 0
    not_number = 0
    i = 0

    while True:
        
        # If the argument is not list
        if type(l)!=list:
            raise ValueError
        # if the list is empty
        if len(l) == 0:
            raise ValueError
        if i == len(l):
            break
        # if the list does not contain any numbers
        if type(l[i])!=int and type(l[i])!=float:
            not_number += 1
            if not_number==len(l):
                raise ValueError
            else:
                i+=1
                continue
        total += l[i]
        num+=1
        i+=1

    return total/num
