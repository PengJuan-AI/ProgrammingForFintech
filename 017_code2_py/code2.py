def print_triangle(size):
    """
    prints a triangle of a specific height and width
    
    args:
    size(int): height and width of the triangle
 
    returns:
    number of asterisks printed 
    """
    # start with star_count being 0
    start_count = 0
    # count from 0 (inclusive) to size (exclusive), for each number i that you count
    for i in range(0,size):
        #count from 0 (inclusive) to i (inclusive), for each number j that you count
        for j in range(0,i+1):
            #print a "*"
            if j == i:
                print('*', end="\n")
            else:
                print('*', end="")
            #increment star_count
            start_count += 1
        #when you finish counting on j, print a new line
    return start_count
    # when you finish counting on i, your answer is star_count


print("Here is a triangle with height 4")
num_stars = print_triangle(4)
print("That triangle had {:d} total stars".format(num_stars));

# now print "Here is a triangle with height 7"
# then call printTriangle, passing in 7, and assign the result to numStars
# finally, print "That triangle had {:d} total stars", such that the {:d} 
# prints the value of numStars

print("Here is a triangle with height 7")
num_stars = print_triangle(7)
print("That triangle had {:d} total stars".format(num_stars));

