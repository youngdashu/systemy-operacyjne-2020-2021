with open("zad4testshort.txt", "w") as f:
    for i in range(100):
        if i%2 == 0:
            f.write("ab"*2 + "cdf" + "ab" * 1 + "\n")
        else:
            f.write("ab" * 3 + "\n")