alph = ["a", "b", "c"]
with open("zad1atest.txt", "w") as f:
    for i in range(5000):
        
        f.write(alph[i%len(alph)] * 100 + "\n")


with open("zad1btest.txt", "w") as f:
    for i in range(5000):
        
        f.write("1" * 100 + "\n")