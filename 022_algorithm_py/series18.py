def series18(N):
    """Implement your function below"""
    x = N*(-N)

    for i in range(1,N*3+1):
        print(x, end=' ')
        x = x+(i*2-1)
