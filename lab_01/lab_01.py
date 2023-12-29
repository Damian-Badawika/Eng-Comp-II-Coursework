'''
Lab 01

Damian Badawika
tuo69407@temple.edu
9/3/2023

'''

import sys
import math

def main(argv):

    # don't mess with this part
    filename = "/data/courses/ece_3822/current/lab_01/data.txt"
    if len(argv) > 1:
        filename = argv[1]

    # Declare variables for the data array, sum, and line count
    x = []
    n = 0
    sum = 0

    #Open the file specified in command line
    with open(filename) as f:
        #Index through each line
        for line in f:
            #Populate data array with values, sum them, and count lines
            x.append(int(line))
            sum += x[n]
            n += 1
            
    # Sort the data array, compute the average, and the square root of the product of the highest 2 values
    # Accurate to 2 decimal places, of course        
    x.sort()
    avg = sum / n
    val = math.sqrt(x[-2] * x[-1])

    #Print our values
    print("the average of the dataset, accurate to two decimal places is: ", round(avg, 2))
    print("the square root of the product of the largest two values, accurate to two decimal places is : ", round(val, 2))


if __name__=="__main__":
    main(sys.argv)