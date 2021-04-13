with open("zad2test.txt", "w") as f:
    for i in range(100_000):
        if i%2 == 0:
            f.write("abcde"*50 + "\n")
        else:
            f.write("abcde" * 50 + "f" + "\n")




