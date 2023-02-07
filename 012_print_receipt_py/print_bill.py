def print_receipt(subtotal, tax_rate, tip_rate):
    """
    This function is used to print a certain format of receipt.
    """
    line = "==========================="

    tax = subtotal*tax_rate
    tip = subtotal*tip_rate
    
    print("{:>8s}: ${:>10.2f}".format("Subtotal", subtotal))
    print("{:>8s}: ${:>10.2f}".format("Tax",tax))
    print("{:>8s}: ${:>10.2f}".format("Tip",tip))
    print("{:>21.10s}".format(line))

    print("{:>8s}: ${:>10.2f}".format("Total", subtotal+tax+tip))    
