def max_seq(l):
    """
    max_seq returns a the maximum increasing contiguous subsequence in the list.

    Args:
    l(list): list of numbers

    Returns:
    the maxiumum increasing contiguous subsequence as a list. If the l is empty,
    an empty list is returned

    Raises:
    TypeError is the function contains an item that is not arithmetically
    compatible with ints and floats
    """
    size = len(l)
    temp = l
    sub = []
    last_sub=[]
    if comparable(l):
        if size>0:
            sub.append(l[0])
            for i in range(1,size):
                if temp[i] > temp[i-1]:
                    sub.append(temp[i])
                    if i == size-1 and len(sub)>len(last_sub):
                        last_sub = sub
                else:
                    if len(sub)>len(last_sub):
                        last_sub=sub
                    sub = []
                    sub.append(temp[i])
                    
        else: return l
    else:
        raise TypeError

    return last_sub

def comparable(l):
    count = 0
    for i in range(0,len(l)):
        if type(l[i])==int or type(l[i])==float:
            count += 1

    if count==len(l):
        return True
    else:
        return False
