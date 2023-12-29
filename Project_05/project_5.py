'''
Damian Badawika
damian.badawika@temple.edu
ECE 3822
Project 5 
12/11/2023

'''

import os
import math

class actor:
    
    def __init__(self,name = "", id = "", born = "", died = "",  roles = [], movies = [] ):
        
        self.name = name
        self.id = id
        self.born = born
        self.died = died
        self.roles = roles
        self.movies = movies

    def show_data(self):
        print(self.name, " ", self.id, " ", self.born, " ", self.died, " ", self.roles, " ", self.movies)

        pass

class movie:
    '''class of <movie>'''

    def __init__(self,title="",id="",cast=[], year = 0, genre = ""):
       self.title = title
       self.id = id
       self.cast = cast
       self.year = year
       self.genre = genre
       pass

    def show_data(self):
        print(self.id, " ", self.title, " ", self.year, " ", self.genre)

class linked_list:
    '''standard linked list class'''

    class node:
        def __init__(self,data=None,next=None):
            self.data = data
            self.next = next
    
    def __init__(self):
        self.head = None

    def insert(self,value):
        new_node = self.node(data=value,next=self.head)
        self.head = new_node

    def lookup(self,target=None,field=None,disp=False):
        curr_ptr = self.head
        ret_val = []

        while (curr_ptr is not None):
            if hasattr(curr_ptr.data,field) and \
                getattr(curr_ptr.data,field) == target:
                    ret_val.append(curr_ptr.data)
            curr_ptr = curr_ptr.next

        if disp and ret_val:
            for r in ret_val:
                r.show_data()
        elif disp and not ret_val:
            print(field, "=" , target, " not found")

        return ret_val
    
    def show_info(self):
        curr = self.head
        #print("info")
        
        while curr is not None:
            #print("shwing data")
            curr.data.show_data()
            curr = curr.next

class hash_table_movies:
    '''basic hash table designed to be inherited'''

    def __init__(self , array_len = 50):
        self.buffer = [linked_list() for i in range(array_len)]
        self.array_len = array_len

    def hash_function(self,hash_item=None):
        
        #initialize a value to help calculate the key
        s = 0

        #Convert the hash array to the sum of the ASCII values
        for ch in hash_item:
            s += ord(ch)
        
        #Find the key by multiplying the ASCII value by an arbitrary constant, modulus with one, multiplied by the array length, and rounded down
        key = math.floor(self.array_len*((s*0.61803) % 1))

        return key
    
    def insert(self,item):
        key = self.hash_function(item.title)
        self.buffer[key].insert(item)

    def lookup(self, target=None, disp=False):

        #Compute the target index using the hash function
        target_index = self.hash_function(target.lower())

        #Use the lookup function in the linked list class to find the target movie
        target_movie = self.buffer[target_index].lookup(target.lower(), "title",disp)

        return target_movie
    
    def display(self):
        for film in self.buffer:
            film.show_info()

class hash_table_actors:
    '''basic hash table designed to be inherited'''

    def __init__(self , array_len = 50):
        self.buffer = [linked_list() for i in range(array_len)]
        self.array_len = array_len

    def hash_function(self,hash_item=None):
        
        #initialize a value to help calculate the key
        s = 0

        #Convert the hash array to the sum of the ASCII values
        for ch in hash_item:
            s += ord(ch)
        
        #Find the key by multiplying the ASCII value by an arbitrary constant, modulus with one, multiplied by the array length, and rounded down
        key = math.floor(self.array_len*((s*0.61803) % 1))

        return key
    
    def insert(self,item):
        key = self.hash_function(item.name)
        self.buffer[key].insert(item)

    def lookup(self, target=None, disp=False):

        #Compute the target index using the hash function
        target_index = self.hash_function(target.lower())

        #Use the lookup function in the linked list class to find the target movie
        target_movie = self.buffer[target_index].lookup(target.lower(), "name",disp)

        return target_movie
    
    def display(self):
        for actor in self.buffer:
            actor.show_info()

class hash_table_roles:
    '''basic hash table designed to be inherited'''

    def __init__(self , array_len = 50):
        self.buffer = [linked_list() for i in range(array_len)]
        self.array_len = array_len

    def hash_function(self,hash_item=None):
        
        #initialize a value to help calculate the key
        s = 0

        #Convert the hash array to the sum of the ASCII values
        for ch in hash_item:
            s += ord(ch)
        
        #Find the key by multiplying the ASCII value by an arbitrary constant, modulus with one, multiplied by the array length, and rounded down
        key = math.floor(self.array_len*((s*0.61803) % 1))

        return key
    
    def insert(self,item):
        key = self.hash_function(item.name)
        self.buffer[key].insert(item)

    def lookup(self, target=None, disp=False):

        #Compute the target index using the hash function
        target_index = self.hash_function(target.lower())

        #Use the lookup function in the linked list class to find the target movie
        target_movie = self.buffer[target_index].lookup(target.lower(), "name",disp)

        return target_movie
    
    def display(self):
        for actor in self.buffer:
            actor.show_info()

class hash_table_movies_ID:
    '''basic hash table designed to be inherited'''

    def __init__(self , array_len = 50):
        self.buffer = [linked_list() for i in range(array_len)]
        self.array_len = array_len

    def hash_function(self,hash_item=None):
        
        #initialize a value to help calculate the key
        s = 0

        #Convert the hash array to the sum of the ASCII values
        for ch in hash_item:
            s += ord(ch)
        
        #Find the key by multiplying the ASCII value by an arbitrary constant, modulus with one, multiplied by the array length, and rounded down
        key = math.floor(self.array_len*((s*0.61803) % 1))

        return key
    
    def insert(self,item):
        key = self.hash_function(item.id)
        self.buffer[key].insert(item)

    def lookup(self, target=None, disp=False):

        #Compute the target index using the hash function
        target_index = self.hash_function(target)

        #Use the lookup function in the linked list class to find the target movie
        target_movie = self.buffer[target_index].lookup(target, "id",disp)

        return target_movie
    
    def display(self):
        for film in self.buffer:
            film.show_info()

class hash_table_actors_ID:
    '''basic hash table designed to be inherited'''

    def __init__(self , array_len = 50):
        self.buffer = [linked_list() for i in range(array_len)]
        self.array_len = array_len

    def hash_function(self,hash_item=None):
        
        #initialize a value to help calculate the key
        s = 0

        #Convert the hash array to the sum of the ASCII values
        for ch in hash_item:
            s += ord(ch)
        
        #Find the key by multiplying the ASCII value by an arbitrary constant, modulus with one, multiplied by the array length, and rounded down
        key = math.floor(self.array_len*((s*0.61803) % 1))

        return key
    
    def insert(self,item):
        key = self.hash_function(item.id)
        self.buffer[key].insert(item)

    def lookup(self, target=None, disp=False):

        #Compute the target index using the hash function
        target_index = self.hash_function(target)

        #Use the lookup function in the linked list class to find the target movie
        target_movie = self.buffer[target_index].lookup(target, "id",disp)

        return target_movie
    
    def display(self):
        for actor in self.buffer:
            actor.show_info()


def load_movies():
    '''
    Loads the data file. 

    #  pick the file
    '''

    fname = "movies.tsv"
    # prepend directory
    path = "/home/tuo69407/ece_3822/project_5/project_5_data"
    fullfilename = os.path.join(path ,fname)

    # read the values from the file into memory
    with open(fullfilename) as f:
        movies_hash = hash_table_movies(len(f.readlines()))
        f.seek(0)
        i = 0
        #print(f.readlines())
        for line in f.readlines():
            #data.append(line)
            #print(line)
            if(i > 0):
                id = line.split("\t")[0]
                #print(id)
                title = line.split("\t")[2]
                #print(title)
                year = line.split("\t")[5]
                #print(year)
                genre = line.split("\t")[8]
                #print(genre)
            
                this_movie = movie(title.lower(), id, [], int(year), genre.lower())
                movies_hash.insert(this_movie)
            i += 1
            #print(film)
        #movies_hash.display()
    
    # return the graph
    return movies_hash

def load_actors():
    '''
    Loads the data file. 

    #  pick the file
    '''

    fname = "names.tsv"
    # prepend directory
    path = "/home/tuo69407/ece_3822/project_5/project_5_data"
    fullfilename = os.path.join(path ,fname)

    # read the values from the file into memory
    with open(fullfilename) as f:
        actors_hash = hash_table_actors(len(f.readlines()))
        f.seek(0)
        i = 0
        #print(f.readlines())
        for line in f.readlines():
            #data.append(line)
            #print(line)
            if(i > 0):
                id = line.split("\t")[0]

                name = line.split("\t")[1]

                birth_year = line.split("\t")[2]

                death_year = line.split("\t")[3]
                
                profession = line.split("\t")[4]

                movies = line.split("\t")[5]
                
                this_actor = actor(name.lower(), id, birth_year, death_year, profession, movies)
                actors_hash.insert(this_actor)
            i += 1
            #print(film)
        #movies_hash.display()
    
    # return the graph
    return actors_hash


def load_movies_ID():
    '''
    Loads the data file. 

    #  pick the file
    '''

    fname = "movies.tsv"
    # prepend directory
    path = "/home/tuo69407/ece_3822/project_5/project_5_data"
    fullfilename = os.path.join(path ,fname)

    # read the values from the file into memory
    with open(fullfilename) as f:
        movies_hash = hash_table_movies_ID(len(f.readlines()))
        f.seek(0)
        i = 0
        #print(f.readlines())
        for line in f.readlines():
            #data.append(line)
            #print(line)
            if(i > 0):
                id = line.split("\t")[0]
                #print(id)
                title = line.split("\t")[2]
                #print(title)
                year = line.split("\t")[5]
                #print(year)
                genre = line.split("\t")[8]
                #print(genre)
            
                this_movie = movie(title.lower(), id, [], int(year), genre.lower())
                movies_hash.insert(this_movie)
            i += 1
            #print(film)
        #movies_hash.display()
    
    # return the graph
    return movies_hash

def load_actors_ID():
    '''
    Loads the data file. 

    #  pick the file
    '''

    fname = "names.tsv"
    # prepend directory
    path = "/home/tuo69407/ece_3822/project_5/project_5_data"
    fullfilename = os.path.join(path ,fname)

    # read the values from the file into memory
    with open(fullfilename) as f:
        actors_hash = hash_table_actors_ID(len(f.readlines()))
        f.seek(0)
        i = 0
        #print(f.readlines())
        for line in f.readlines():
            #data.append(line)
            #print(line)
            if(i > 0):
                id = line.split("\t")[0]

                name = line.split("\t")[1]

                birth_year = line.split("\t")[2]

                death_year = line.split("\t")[3]
                
                #profession = line.split("\t")[4]

                #movies = line.split("\t")[5]
                
                this_actor = actor(name.lower(), id, birth_year, death_year, [], [])
                actors_hash.insert(this_actor)
            i += 1
            #print(film)
        #movies_hash.display()
    
    # return the graph
    return actors_hash


def load_roles():
    '''
    Loads the data file. 

    #  
    '''
    movies_hash = load_movies_ID()
    actors_hash = load_actors_ID()

    fname = "starring_roles.tsv"
    # prepend directory
    path = "/home/tuo69407/ece_3822/project_5/project_5_data"
    fullfilename = os.path.join(path ,fname)

    # read the values from the file into memory
    with open(fullfilename) as f:
        roles_hash = hash_table_roles(len(f.readlines()))
        f.seek(0)
        i = 0
        #print(f.readlines())
        for line in f.readlines():
            #data.append(line)
            #print(line)
            if(i > 0):
                movie_id = line.split("\t")[0]

                name_id = line.split("\t")[2]

                #cat = line.split("\t")[3]

                role = line.split("\t")[5]
                
                this_actor = actors_hash.lookup(name_id)

                for i in range(len(this_actor)):
                    # print(len(this_actor))
                    # print(i)
                    # print(this_actor[i].name)

                    this_actor[i].movies.append(movies_hash.lookup(movie_id))
                    this_actor[i].roles.append(role)
                    roles_hash.insert(this_actor[i])
            i += 1
            #print(film)
        #movies_hash.display()
    
    # return the graph
    return roles_hash

def main():
    '''
    Usage:
   
        '''
    
    #Problem 1 Code
    # movies_hash = load_movies()
    # movies_hash.lookup("Dream Status", True)
    # movies_hash.lookup("A Letter from Beirut", True)
    # movies_hash.lookup("Joe momma", True)

    #Problem 2 Code
    # actors_hash = load_actors()
    # actors_hash.lookup("Ewan Mcgregor", True)
    # actors_hash.lookup("Clint Eastwood", True)
    # actors_hash.lookup("Chief queef", True)

    #Problem 3 Code
    roles_hash = load_roles()
    roles_hash.lookup("Ewan Mcgregor", True)

main()
