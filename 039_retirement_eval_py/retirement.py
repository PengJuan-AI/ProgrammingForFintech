import sys
from sys import argv
import os

class Equity:
    def __init__(self,y, m, p, dd, lp):
        self.year = "{:4d}".format(y)
        self.month = "{:02d}".format(m)
        self.price = float(p)
        self.last_price = float(lp)
        self.dividend = float(dd)

    def ror(self):
        a = self.price/self.last_price-1
        b = (self.dividend/12)/self.price
        return a+b

    def date(self):
        return str(self.year)+'.'+str(self.month)

class Bond:
    def __init__(self, y, m, r):
        self.year = y
        self.month = m
        self.rate = float(r)

    def ror(self):
        return self.rate/12/100

    def date(self):
        return str(self.year)+'.'+str(self.month)

def examine_date_format(date):
    if len(date)!=7:
        return False
    year_month = date.split('.')
    if len(year_month[0])==4 and len(year_month[1])==2:
        if year_month[0]<'1792' or year_month[0]>'2022':
            return False
        elif year_month[1]<'01' or year_month[1]>'12':
            return False
        else:
            return True
    else:
        return False

def examine_date_validation(start, end, eqs, bonds):
    """examine the start date and end date is within the validate range"""
    
    if start>end:
        return False
    elif end<eqs[0].date() or start>eqs[-1].date():
        return False
    elif start<eqs[0].date() or end>eqs[-1].date():
        return False
    else:
        return True


def read_file(filename, cls):
    """
    Read file of s&p500_data or bonds_data, create responding class and put them in responding lists.
    Before read files, examine if they exist.
    Before create class, examine if the format of the date of each line in file is correct.
    Examine if they are continuous dates.
    """
    last = 0
    eqs = []
    bonds = []
    last_year=0
    last_month=0
    if not os.path.exists(filename):
        return False

    with open(filename) as f:
        for line in f.readlines():
            info = line.strip().split(',')
            if info[0]=='Date':
                continue
            else:
                # date validation
                if not examine_date_format(info[0]):
                    return False
                # Split year and month
                y_m = info[0].split('.')
                year = int(y_m[0])
                month = int(y_m[1])
                if last_year==0: last_year=year
                else:
                    if year-last_year==0 or year-last_year==1:
                        last_year = year
                    else:
                        return False

                if last_month==0: last_month=month
                else:
                    if (month==1 and last_month==12) or (month-last_month==1):
                        last_month = month
                    else:
                        return False


                if cls=="Equity":
                        equity = Equity(year, month, info[1], info[2],last)
                        last = info[1]
                        eqs.append(equity)
                elif cls=="Bond":
                    bond = Bond(year, month, info[1])
                    bonds.append(bond)

    if cls == "Equity":
        return eqs
    elif cls == "Bond":
        return bonds

def strategy1(eq, capital, contribution):
    # Strategy 1
    cumulative = capital*(1+eq.ror())+contribution
    return cumulative

def strategy2(bond, capital, contribution):
    # Strategy 2
    cumulative = capital*(1+bond.ror())+contribution
    return cumulative

def strategy3(eq, bond, capital, contribution, allocaiton):
    # Strategy 3
    cumulative = capital*(1+eq.ror())*allocaiton+capital*(1+bond.ror())*(1-allocaiton)+contribution
    return cumulative

def calculate_result(eqs, bonds, start_date, end_date):
    result = {}
    size = len(eqs)
    capital = 0
    contribution = 100

    c1 = capital
    c2 = capital
    c3 = capital
    allocation = 1
    # Exclude the initial date
    if not examine_date_validation(start_date, end_date, eqs, bonds):
        sys.exit(1)

    for i in range(0, size):
        # eq_date = eqs[i].date()
        if eqs[i].date() >= start_date and bonds[i].date() >= start_date:
            # every new year
            if eqs[i].month == '01':
                if allocation != 0:
                    allocation -= 0.02
                contribution *= (1 + 0.025)

            c1 = strategy1(eqs[i], c1, contribution)
            c2 = strategy2(bonds[i], c2, contribution)
            c3 = strategy3(eqs[i], bonds[i], c3, contribution, allocation)

            result[eqs[i].date()] = [c1, c2, c3]

            if eqs[i].date() >= end_date and bonds[i].date() >= end_date:
                break
    # print(result)
    return result

def create_result_file(dict):
    filename = 'portfolio.csv'

    f = open(filename, 'wt')
    # print header
    print("Date,StrategyOne,StrategyTwo,StrategyThree", file=f)
    for item in dict.items():
        print("{},{:.2f},{:.2f},{:.2f}".format(item[0],item[1][0],item[1][1],item[1][2]), file=f)
    f.close()


def process(sp_file, bond_file, start_date, end_date):

    eqs = read_file(sp_file, "Equity")
    if not eqs:
        exit(2)

    bonds = read_file(bond_file, "Bond")
    if not bonds:
        exit(3)

    if not examine_date_format(start_date):
        sys.exit(1)

    if not examine_date_format(end_date):
        sys.exit(1)

    result = calculate_result(eqs, bonds, start_date, end_date)
    create_result_file(result)


if __name__ == '__main__':

    if len(argv) != 5:
        sys.exit(1)

    process(argv[1], argv[2], argv[3], argv[4])
