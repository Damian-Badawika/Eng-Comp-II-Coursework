''' lab_06.py

    Damian Badawika
    tuo69407@temple.edu

    Description:
    This file creates a hash table of <student>s and tests performance
    with some simple inserts and lookups in <main>.

    Usage:
    python lab_06.py
    
'''

#################################################################
class student:

    def __init__(self,last,first,zip,gpa):
        self.last  = last
        self.first = first
        self.zip   = zip
        self.gpa   = gpa

    def display(self):
        print(self.last, " ", self.first , " " , self.gpa , " " , self.zip)

#################################################################
class hash_table:

    # constructor
    def __init__(self,buff_len=10):
        self.buff_len = buff_len
        self.buffer = [None]*self.buff_len

    # all-important hash-function
    def hash_function(self , std=None , last=None , first=None):

        # if a student is provided as input, use names in student
        # for the hash function. otherwise use the provided first
        # and last names
        if std: last,first = std.last, std.first
        
        # concatenate the names
        total_name = last.lower()+first.lower()
        s = 0
       
        #COmpute a hash value for the student name
        for i in range(len(total_name)):
            s += ord(total_name[i]) * i        # ord(c) converts c into ascii value

        #Map that value to the length of the list
        index = s % self.buff_len

        return index
    
    # insert student into buffer
    def insert(self,std):

        #compute the index of the student to insert
        index = self.hash_function(std=std)

        #If statement to handle collisions
        while index < self.buff_len:
            if self.buffer[index] == None:  #Insert the student in an empty spot and end the function call
                 self.buffer[index] = std
                 return
            else: # increment the index if there is already a studetn in that spot
                index += 1

    # look up a student in the hash table by 'first' and 'last'
    def lookup(self,last,first,display=False):

        #declare variables for the target student and target index
        target_student = None
        target_index = self.hash_function(None, last, first) #Compute the target index

        #index through the hash table
        while target_index < self.buff_len:

            #If the target name is the same as th current name, the we have found the target stident
            if self.buffer[target_index] != None and self.buffer[target_index].last == last and self.buffer[target_index].first  == first:
                target_student = self.buffer[target_index]
                break   #found the student, end the loop

            #keep indexing if we haven't found them
            else:
                target_index += 1

        #Display data if the user wants
        if display: 
            print("\n")
            print("Search result:" ,end=" ")
            if target_student: 
                target_student.display()
            else: 
                print(last,first, "not found")
            print("\n")

        return target_student

    # display contents of the buffer
    def display(self):
        print("\n")
        print("Displaying complete contents of hash table:")
        for i,s in enumerate(self.buffer):
            print(i,end=" ")
            if s:
                s.display()
            else:
                print("")            
        print("\n")

def main():

    # create the hash table
    my_table = hash_table(buff_len = 15)

    # create two new students and insert them into the hash table
    my_table.insert( student( "Obeid" , "Iyad" , 19143 , 3.99) )
    my_table.insert( student("Eboid","Iyad",19143, 3.99))
    my_table.insert( student( "Obeid" , "Timmy", 19147 , 3.14) )
    my_table.insert( student( "Obeid" , "Timmy", 19147 , 3.14) )

    # look up a student and display results
    my_table.lookup("Eboid","Iyad",display=True)

    # display contents of hash table
    my_table.display()


if __name__=="__main__":
    main()
