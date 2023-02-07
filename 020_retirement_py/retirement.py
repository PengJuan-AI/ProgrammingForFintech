def retirement(start_age, initial_savings, working_info, retired_info):
    """
    Prints the current status of an individual's retirement account.
    The dictionaries both have these fields:
        "months","contribution","rate_of_return"

    Args:
       start_age (int): At what age (in months) does the individual start
       initial_savings (float): initial savings in dollars
       working_info (dict): information about working
       retired_into (dict): information about retirement

    Returns:
    None
    """
    working_life = working_info['months']
    retored_life = retired_info['months']

    age = start_age
    capital = initial_savings

    while working_life:
        result(age, capital)
        capital = computation(capital,working_info['rate_of_return'], working_info['contribution'])
        working_life -= 1
        age += 1

    while retored_life:
        result(age, capital)
        capital = computation(capital, retired_info['rate_of_return'], retired_info['contribution'])
        retored_life -= 1
        age += 1


def computation(capital,rate, contribution):
    return capital*(1+rate)+contribution

def result(age, capital):
    print("Age {:3d} month {:2d} you have ${:,.2f}".format(age//12, age%12, capital))

if __name__ == '__main__':
    w_m = 489
    w_saving = 1000
    w_r = 0.045
    r_m = 384
    r_expenditure = -4000
    r_r = 0.01
    age = 327
    savings = 21345

    working = {"months":int(w_m), "contribution":float(w_saving),  "rate_of_return":float(w_r)}
    retired = {"months":int(r_m), "contribution":float(r_expenditure),  "rate_of_return":float(r_r)}

    retirement(age, savings, working, retired)
