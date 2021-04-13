with open("zad5test.txt" , "w") as f:
    for i in range(100_000):
        if i%2 == 0:
            f.write("a"*60 + "\n")
        else:
            f.write("1" * 20 + "\n")