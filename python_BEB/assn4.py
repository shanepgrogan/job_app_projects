# assn4.py

# defining classes and functions

class Station:
    def __init__(self, name, nums):
        self.name = name
        self.numbers = nums
        self.collision = False
        self.wait = 0
        self.retransmit_num = 0
        self.transmit_success = False
        self.done = False
        self.transmit_slot = None

# this will change the setting of all stations based one whether there was
# a collision also returns true if there is at least 1 collision, and we
# store that bool in a variable to determine whether to increase the 
# current_number (i.e. the index to select from the lists of random numbers)
def compare_for_collision(stations):
    N = len(stations)
    collide = False
    for i in range(N):
        for j in range(i+1, N):
            s1 = stations[i]
            s2 = stations[j]
            if s1.wait == s2.wait and s1.done == False and s2.done == False:
                s1.collision = True
                s2.collision = True
                collide = True
    return collide

# sets all stations collision attribute to False
def collision_reset(stations):
    for s in stations:
        s.collision = False

# Input processing

fh = open("Input.txt")
N = int(fh.readline())
print("The number of stations in the network under investigation is:\n" + str(N) + "\n")

stations = []
print("The random numbers used by the stations are:")
for i in range(N):
    
    string = fh.readline()
    print(string[:-1])
    
    num_list = [int(s) for s in string.split(",")]
    name = "Station" + str(i+1)
    
    s = Station(name, num_list)
    stations.append(s)

print("\n")

# Program

# holds the current index in the list of random numbers,
# the current timeslot, and a list of the stations that have
# either successfully transmitted or have failed to do so
current_number = 0
timeslot = 0
final_states = []

# while loop iterates while the final_state list is not full
while(len(final_states) < N):

    comp = compare_for_collision(stations)

    for s in stations:

        if not s.done:
        
            if s.retransmit_num == 5:
             
                s.transmit_slot = timeslot + s.wait
                s.done = True
                final_states.append(s)

            elif s.collision:
        
                s.wait += s.numbers[current_number]
                s.retransmit_num += 1

            elif s.wait > 0:
        
                s.wait -= 1
            
            else:
        
                s.transmit_success = True
                s.transmit_slot = timeslot
                s.done = True
                final_states.append(s) 
                
    if comp:
        
        current_number += 1
    
    timeslot += 1
    
    collision_reset(stations)
    
for s in stations:
    if(s.transmit_success):
        success = "Success"
    else:
        success = "Failure"
    print(s.name + ": " + success)
    print("Timeslot for Last Retransmission: " + str(s.transmit_slot))
    print("Total Number of Retransmission: " + str(s.retransmit_num) + "\n")
