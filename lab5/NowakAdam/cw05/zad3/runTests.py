#! /usr/bin/python

# import sys
import os
import time



if __name__ == '__main__':


    numsOfProducers = [ 5]
    numsOfConsumers = [ 5]
    

    Ns = [5, 50, 100]

    for prNum, conNum in zip(numsOfProducers, numsOfConsumers):



        for N in Ns:

            print("producers: ", prNum, " consumers: ", conNum, " N: ", N)

            if os.fork() == 0:
                os.execl("./wrapper","wrapper" ,str(prNum), str(conNum), str(N) )
            else:
                os.wait()

            # verifySolution(prNum)

            with open("consumerFile.txt", "r") as conF:
                consumerLines = conF.readlines()

                for conLine in consumerLines:
                    print(conLine, end = "") 

            time.sleep(0.5)

            