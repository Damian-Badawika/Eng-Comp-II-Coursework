# note -> delete the "pass" statements. Those are placeholders
# until you replace them with actual code

class student:
    grade_array = []

    #Class Constructor, create an object of type student
    #
    def __init__(self):
        print("Creating class student")

    #Function to set the name of the student
    #
    def set_name(self,name):
        self.name = name

    #Function to add a grade for a student
    #
    def add_grade(self,grade):
        self.grade_array.append(grade)

    #Function to find the student's highest grade
    #
    def get_max(self):
        self.grade_array.sort()
        return self.grade_array[-1]

    #Function to take the student's average grade
    #
    def get_average(self):
        #Declare sum and grade count variables to compute the average
        sum = 0
        count = 0
        
        #Index through the array, sum and count the grades
        for grade in self.grade_array:
            sum += grade
            count += 1
        
        #Compute and return the average
        avg = sum / count
        return avg

    #Display name and grades for the student
    #
    def display(self):
        print("Student name: ", self.name)

        #Index through and print each grade
        for grade in self.grade_array:
            print("Grade ", self.grade_array.index(grade) + 1,":", grade)
        pass  
