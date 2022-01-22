1. Peter Chong     pc662@drexel.edu

2. To run the code, do:
    make (compiles and gives a goat executable)
    make run (compiles and ruins ./goats 12 21)
    make clean (To remove the executable)

3. I used semaphores and incorporated the lightswitch class shown in class, as well as some regular mutex locks for printing out to console. The semaphores are there to lock 
the turnstile and to know that the bridge is empty. The lightswitch class is there to know if a goat on the east has entered and will keep incrementing if more goats from the east
enter and if the last one leaves, releases the lock for the west goats. The west goats however, can hold onto the turnstile so that the east goats will stop coming in if the west
goats are waiting.

4. I allowed multiple goats on the bridge by creating a sort of turnstile on the west and east side. The west side would be the writer side and the east side would be the reader side.
That means that east to west would be reader and if a goat on the west side is in queue, it will wait for all the east side to cross before another east can come through.

5. The rope is fair because it still allows goats from the west to cross, as well as the east goats to cross. However, the priority is with the writers, or west side, because 
the west side 

6. Deadlocks should not happen with this program, and starvation is usually a result of deadlocking. I also used turnstiles in order for the west side to be able to cross 
once they are done their task, letting all current readers or east side goats to come through before they can go. 

7. The most challenging part of this assignment was trying to think of another design for this homework, even though I was not able to incorporate it in time, it is something that
I will be keeping in the back of my mind.