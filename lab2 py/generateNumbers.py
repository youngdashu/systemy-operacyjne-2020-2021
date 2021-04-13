import random

def generate(fileLen):

    res = open("zad3test.txt", "w")

    for i in range(0, fileLen):
        res.write(str(random.randint(1, 100_000_000_00)) + "\n")

generate(100_000)
