//C++ file to implement student class
//

#include<iostream>
#include<iomanip>
#include "student.h"
using namespace std;

//Class constructor, create the object
//
student::student(){
    cout << "Constructing class student" << endl;
}

//Class destructor, deallocates memory
//
student::~student(){
    cout << "destructing class student" << endl;
    delete [] grade_array;
}

//Display function diplays the name and grades for the student
//
void student::display(){
    //Print student name
    //
    cout << "Student name: " << name << endl;
    
    //Index through the array of grades
    //
    for(int i = 0 ;i < 20 ; i++){
        //Print all non-zero values
        //
        if( grade_array[i] != 0){
            cout << "grade " << i + 1 << ": " << grade_array[i] << endl;
        }
        else{
           break;
        }
    }
}

//Function to get the student's average grade
//
double student::get_average(){
    //Initialize values for the sum and count of the grades
    //
    int sum = 0;
    int grades = 0;
    
    //Index through all grades
    //
    for(int i = 0 ;i < 20 ; i++){
        //Sum and count valid grade values
        //
        if(0 < grade_array[i] && grade_array[i] <= 100){
            sum += grade_array[i];
            grades += 1;
        }
    }
    //Compute and return the average
    //
    avg = sum / grades;
    return avg;
}

//Function to populate the grade array
//
void student::add_grade(int grade){
    //Index through the allocated array
    //
    for (int i = 0 ; i < 20 ; i++){
        //Assign the value in place of a zero
        //
        if( grade_array[i] == 0 ){
            grade_array[i] = grade;
            break;
        }
    }
    return;
}

//Function to set the student name
//
void student::set_name(string input){
    name = input;
    return;
}

//Function to sort the grade array and get the max value
//
int student::get_max(){
    //Assign values for comparison
    //
    int comp1 = INT_MIN;
    int comp2 = INT_MIN;

    //Index through the grade array
    //
    for(int i = 0; i < 20 ; i++){
        int val = grade_array[i];
        //Compare the value of each line to the comparison variables
        //
        if(val != 0){
            //If the value is greater than comp1, assign comp2 to the value of comp1 and change comp1 to the value of the line
            //
            if(val > comp1){
                comp2 = comp1;
                comp1 = val;
            }
            //If the value is greater than comp2 and not equal to comp1 then we assign comp2 to the line's value
            //
            else if(val > comp2 && val != comp1){
                comp2 = val;
            }
        }
    }

    //return the highest grade
    //
    return grade_array[0];
}