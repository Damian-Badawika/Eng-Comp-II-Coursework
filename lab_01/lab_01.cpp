/*
Lab 01

Damian Badawika
tuo69407@temple.edu
9/3/2023

*/

//Include some useful libraries
//
#include<iostream>
#include<fstream>
#include<limits.h>
#include<iomanip>
#include<math.h>
using namespace std;


int main(int argc, char** argv){

    // step 0 - you can ignore this bit
    string filename = "/data/courses/ece_3822/current/lab_01/data.txt";
    if (argc>1)
        filename = argv[1];

    // step 1 init variables
    double s = 0;
    int n = 0;
    double avg = 0;
    double var = 0;
    string line;
    int val;

    //Initialize variables for comparison to dataset values for sorting
    //
    double comp1 = INT_MIN;
    double comp2 = INT_MIN;

    // step 2 open file
    ifstream file_id(filename);
    
    // step 3 read values from file
    // this is just an example to demonstrate syntax; modify as you deem necessary!
    while (getline(file_id,line)){
        //Read each line of the dataset as a float, increment the line count and sum each value
        val = stof(line);
        n += 1;
        s += val;
        
        //Compare the value of each line to the comparison variables
        if(val > comp1){
            //If the value is greater than comp1, assign comp2 to the value of comp1 and change comp1 to the value of the line
            //
            comp2 = comp1;
            comp1 = val;
        }
        
        //If the value is greater than comp2 and not equal to comp1 then we assign comp2 to the line's value
        //
        else if ( val > comp2 && val != comp1){
            comp2 = val;
        }
    }

    //Compute the average
    //
    avg = s / n;
    
    // step 4 print value
    cout << "The average value ,accurate to two decimal places is: " << std::fixed << setprecision(2) << avg << endl;
    cout<< "square root of the product of the largest two values, accurate to two decimal places is: " << std::fixed << setprecision(2) << (sqrt((comp1 * comp2))) << endl;
    file_id.close();

    return 0;
}
