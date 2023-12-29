#ifndef STUDENT_H
#define STUDENT_H

#include<string>
#include<limits.h>
using namespace std;


class student{

    //Private Class values, user no touch!
    private:
    //Allocating memory for the array of the student's grades
    //
    int* grade_array = new int[20];
    
    //Variables for name, max, and average
    //
    string name;
    int max;
    double avg;

    public:

    // DON'T CHANGE THESE FUNCTION PROTOTYPES
    student();
    void set_name(string);
    void add_grade(int);
    int get_max();
    double get_average();
    void display();
    ~student();

};

#endif 