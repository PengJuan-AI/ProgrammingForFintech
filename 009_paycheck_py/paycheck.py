# paycheck program
h = input("How many hours didi the employee work?")
pr = input("What is the employees pay rate?")
taxr = 0.2

#convertion
h = float(h)
pr = float(pr)

# conditions
if h>40:
    total_pay = 40*pr + (h-40)*(1.5*pr)
else:
    total_pay = h*pr

print("Total pay: ",total_pay)

tax = total_pay*taxr
print("Taxes: ",tax)

net_pay = total_pay-tax
print("Net pay: ",net_pay)

