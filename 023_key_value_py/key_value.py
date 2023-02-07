import sys
from sys import argv

def read_key_values(filename):
    """
    Reads a key-value delimited file (separated by first =) into a dictionary

    Args:
    filename(str): name of the file to read
    
    Returns:
    dictionary of the read items
    """
    """read key-value file and create a responding dictionary"""
    kvs_dict = {}
    with open(filename) as f:
        for line in f:
            l = line.strip().split('=')
            kvs_dict[l[0]] = l[1]

    return kvs_dict


def create_output_filename(name):
    """
    create the output file name.  Given an input filename such as "input.txt",
    return "input.txt.counts"
    """
    return name+".counts"


def process_key_file(filename,key_values):
    """
    Loads in a key file and produces a dictionary of the count of the values 
    If a key is not found in key_values use "<unknown>"

    Args:
    filename(str): file containing keys to process
    key_values(dict): existing keys to load
    """
    """if a value is not in count dictionary, then assignment 1 to it. Otherwise, puls 1"""
    count_dict = {}
    unknown = '<unknown>'
    with open(filename) as f:
        for line in f:
            line = line.strip()
            if line in key_values:
                value = key_values[line]
                # print("key is ",line)
                # print("value is ",value)
                if value in count_dict:
                    count_dict[value] += 1
                else:
                    count_dict[value] = 1
            else:
                if unknown in count_dict:
                    count_dict[unknown] += 1
                else:
                    count_dict[unknown] = 1

        return count_dict

def write_output(filename,counts):
    """
    Sort the output value the highest count descending. If two values are
    equal, arbitrarily choose 1
    """
    l = sorted(counts, key=counts.get, reverse=True)
    
    f = open(filename,'wt')
    for i in range(0,len(l)):
        f.write("{}: {}\n".format(l[i], counts[ l[i] ]))

    f.close()

def process(args):
    """
    Implement your algorithm in this function
    """
    # print(args)   #Uncomment if you want to validate/see the command-line arguments
    l = len(args)
    # key-value
    kv_file = args[1]
    kvs_dict = read_key_values(kv_file)

    for i in range(2,l):
        count_dict = process_key_file(args[i], kvs_dict)
        output_filename = create_output_filename(args[i])
        write_output(output_filename, count_dict)

# __name__ == "__main__" and argv explained in the "modules" notebook
if __name__ == "__main__":
    if len(argv) < 3:
        print("Usage: python3 key_value.py file1_name file2_name ...")
        sys.exit(-1)
    process(argv)
