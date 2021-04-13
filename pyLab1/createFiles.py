import string
import random

alph = list(string.ascii_lowercase)

def createFiles():

    tests = [i for i in range(1, 4)]

    # numOfPairsInTest = [3, 30, 300]

    numOfLinesInFile = [5, 50, 500]
    lengthOfTest = ["short", "med", "long"]

    fileNameTemplate = ["./przykladyTxt/"]

    for test in tests:

        # for pairs in numOfPairsInTest:

        for lines, length in zip( numOfLinesInFile, lengthOfTest):

            fileNameA = fileNameTemplate[:]
            fileNameB = fileNameTemplate[:]

            fileNameA.append("test")
            fileNameA.append(str(test))
            fileNameA.append("_")
            fileNameA.append("a")
            fileNameA.append(length)
            fileNameA.append(".txt")

            fileNameB.append("test")
            fileNameB.append(str(test))
            fileNameB.append("_")
            fileNameB.append("b")
            fileNameB.append(length)
            fileNameB.append(".txt")

            a = ''.join(fileNameA)
            b = ''.join(fileNameB)

            numOfPairsInTest = [3, 30, 300]
            length = ["short", "med", "long"]

            
                        

                    

            # fa = open(a, "w")
            # fb = open(b, "w")
            
            # for j in range(lines):
            #     fa.write(alph[j%len(alph)] * 100 + "\n")
            #     fb.write(alph[random.randint(0, len(alph) - 1)] * 100 + "\n")

            # fa.close()
            # fb.close()

def createArgs():

    numOfPairsInTest = [3, 30, 300]
    tests = [1, 2, 3]
    length = ["short", "med", "long"]

    for pairs, test in zip( numOfPairsInTest, tests):

        for l in length:

            if test == 1:

                test1Args = open("test1Args.txt" , "w")

                test1Args.write("\"merge_files\"," + "\"./przykladyTxt/test1_ashort.txt:./przykladyTxt/test1_bshort.txt\"," * pairs + "\n\n")
                # print("")
                test1Args.write("\"merge_files\"," + "\"./przykladyTxt/test1_amed.txt:./przykladyTxt/test1_bmed.txt\"," * pairs + "\n\n" )
                # print("")
                test1Args.write("\"merge_files\"," + "\"./przykladyTxt/test1_along.txt:./przykladyTxt/test1_blong.txt\"," * pairs + "\n\n" )
                # print("")

                test1Args.close()

            elif test == 2:
                print("\"merge_files\"," + "\"./przykladyTxt/test2_ashort.txt:./przykladyTxt/test2_bshort.txt\"," * pairs)
                print("")
                print("\"merge_files\"," + "\"./przykladyTxt/test2_amed.txt:./przykladyTxt/test2_bmed.txt\"," * pairs)
                print("")
                print("\"merge_files\"," + "\"./przykladyTxt/test2_along.txt:./przykladyTxt/test2_blong.txt\"," * pairs)
                print("")

            elif test == 3:
                print("\"merge_files\"," + "\"./przykladyTxt/test3_ashort.txt:./przykladyTxt/test3_bshort.txt\"," * pairs)
                print("")
                print("\"merge_files\"," + "\"./przykladyTxt/test3_amed.txt:./przykladyTxt/test3_bmed.txt\"," * pairs)
                print("")
                print("\"merge_files\"," + "\"./przykladyTxt/test3_along.txt:./przykladyTxt/test3_blong.txt\"," * pairs)
                print("")





# createFiles()

createArgs()
                

