from sys import argv
import sys

def parse_state_information(filename):
    """
    Opens the state information file named in filename, loads all of the 
    values, placing them in a single data structure. Returns that data 
    structure.  You may created nested data structures.
    """
    dict = {}
    with open(filename) as f:
        for line in f.readlines():
            l = line.strip().split(':')
            state = l[0]
            l = l[1:]
            data = [int(x) for x in l]
            dict[state] = data

    print_state_information(dict)
    return dict

def print_state_information(state_info):
    """
    For the state_info data structure (produced as a result),  
    print all statues in alphabetical order using the string:
    "{}: Population - {:,d}, Electoral Votes: {:d}"
    """
    states = sorted(state_info)

    for state in states:
        print("{}: Population - {:,d}, Electoral Votes: {:d}".format(state, state_info[state][0],state_info[state][1]) )


def parse_vote_information(filename):
    """
    Opens the vote information file and returns the information 
    in a data structure
    """
    dict = {}
    with open(filename) as f:
        for line in f.readlines():
            l = line.strip().split(':')
            dict[l[0]] = int(l[1])

    return dict



def count_electoral_votes(state_info,vote_info):
    """
    Counts and returns the number of electoral votes received by 
    Candidate A in the election.

    For our purposes, Candidate A receives ALL electoral votes for a
    state if Candidate A receives strictly more than 50% of the votes in
    that State.  [Yes, we know that in the US there are a few states
    with more complex rules, but we will ignore them.  We will also
    ignore the electoral complexities of what would happen if a
    candidate received exactly 50%, and in this case, just say that
    Candidate A does not receive those electoral votes.  We are also
    assuming everyone in every state votes--while this doesn't happen in
    a real election, it is what we are doing here].
    """
    electoral_votes = 0
    states = list(vote_info.keys())
    for state in states:
        pct = vote_info[state]/state_info[state][0]
        if pct>0.5:
            electoral_votes+=state_info[state][1]

    return electoral_votes

def determine_winner(state_info, candidate_a_electoral_votes):
    """
    Determines whether Candidate A or Candidate B won based upon who
    won the majority of the electoral votes. If there is a tie, return None.
    Returns "A", "B", or None    the last one is the value None
    """
    total_electoral_votes = 0
    for value in state_info.values():
        total_electoral_votes+=value[1]
    pct = candidate_a_electoral_votes/total_electoral_votes
    if pct>0.5:
        return "A"
    elif pct==0.5:
        return None
    else:
        return "B"


def print_winner(winner_name, number_of_votes):
    """
    Prints the winner.  If Candidate A or B wins, print
    "Candidate {} wins the election with {:d} votes" using the winner_name
    and number of Electoral Collage.

    If neither won the vote, print "It's a tie in the Electoral Collage."
    """
    if winner_name=="A":
        print("Candidate {} wins the election with {:d} votes".format(winner_name, number_of_votes))
    elif winner_name=="B":
        print("Candidate {} wins the election with {:d} votes".format(winner_name, number_of_votes))
    else:
        print("It's a tie in the Electoral Collage.")


def determine_recounts(state_info, vote_info):
    """
    Produces a list of strings, where each string represents information
    about a state the requires a recount. Recounts are required when a 
    Candidate A is within +/ 0.5% of 50% of the votes.  So 49.50% or 50.50%
    require a recount, while 49.49% and 50.51% do not require a recount.
    
    Only include states that require a recount in the result. For each state
    that requires a recount, include a line of the form:
    "{} requires a recount (Candidate A has {:.2f}% of the vote)".
    """
    recount_list = []
    states = list(vote_info.keys())
    for state in states:
        pct = vote_info[state] / state_info[state][0]
        if pct > 0.495 and pct<0.505:
            recount_list.append("{} requires a recount (Candidate A has {:.2f}% of the vote)".format(state, pct*100))

    save_recounts(recount_list)
    return recount_list


def save_recounts(recount_list):
    """
    saves each entry of the list to a file named "recounts.txt".  The
    entries must be printed in alphabetical order.
    """
    filename = "recounts.txt"
    recount_list.sort()

    f = open(filename, 'wt')
    for i in range(0, len(recount_list)):
        print(recount_list[i],file=f)
    f.close()

def determine_largest_win(state_info, vote_info):
    """
    Determines in which state Candidate A won the largest percentage 
    of the vote.

    returns a string with the following format:
    "Candidate A won {} with {:.2f}% of the vote"

    where the first {} should be the name of the state, and the {.2f} 
    should be the percentage of the vote won.  For example, it might return
    "Candidate A won California with 73.24% of the vote"

    None is returned if candidate A did not win a state
    """
    max = 0
    flag = 1
    electoral_votes = count_electoral_votes(state_info, vote_info)
    total = Total_electoral_votes(state_info)
    states = list(vote_info.keys())
    for state in states:
        pct = vote_info[state] / state_info[state][0]
        if flag:
            max = pct
            state_largest_win = state
            flag = 0
            continue
        if pct>max:
            max = pct
            state_largest_win = state

    if max!=0:
        return "Candidate A won {} with {:.2f}% of the vote".format(state_largest_win, max*100)
    else:
        return None

def Total_electoral_votes(state_info):

    total_electoral_votes = 0
    for value in state_info.values():
        total_electoral_votes += value[1]

    return total_electoral_votes

def process(state_info_filename, voter_info_filename):
    """
    Implements the "Several steps exist for this assignment" section
    """
    dict_state = parse_state_information(state_info_filename)
    dict_votes = parse_vote_information(voter_info_filename)

    total_electoral_votes = Total_electoral_votes(dict_state)

    electoral_votes = count_electoral_votes(dict_state, dict_votes)
    winner = determine_winner(dict_state, electoral_votes)
    if winner=="A":
        print_winner("A", electoral_votes)
    elif winner=="B":
        print_winner("B", total_electoral_votes-electoral_votes)
    else:
        print_winner(None, 0)
    
    determine_recounts(dict_state, dict_votes)
    print(determine_largest_win(dict_state, dict_votes))



if __name__ == "__main__":
    """implement checking command line arguments, call process()"""
    if len(argv) != 3:
        print("Usage: python3 minesweeper.py state_info_filename voter_info_filename")
        sys.exit(1)

    process(argv[1], argv[2])

