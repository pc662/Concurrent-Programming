1. Peter Chong      pc662@drexel.edu

2. make run: compile and run a simulation with 7 adults and 9 children
   make: compile the program for manual usage
   make clean: remove the compiled code 

3. I used many condition variables to protect the boat. I used them because it would hold the thread off from continuing until the driver thread had signaled that it was okay
for the passenger thread to move on and get off the boat. It was also a way for the passenger threads to signal to the driver of the boat that they've boarded and it is
alright to row back to the mainland

4. The last child thread would always be the driver and the passengers would just be any thread that made its way into the passenger seat first. This guarantees that the rules of
the boat are followed and no rules are really broken.

5. The passenger would always get dropped off at the mainland which leaves an empty spot by default. When the boat gets back to the island, there will always be one spot available
for a thread to occupy. 

6. I am certain everyone will get off the island because the condition variables tell any waiting threads to keep waiting until they are notified by the driver thread. No thread
will bust in line or hide really. I also kept a counter of the threads in a global variable, so the driver thread will exit the boat as well when it's on the mainland if that
counter is equal to 0.

7. The most challenging part of this assignment was learning how to really use condition variables since they combine locks that are sort of like lock_guards with a condition. Honestly,
there's a lot of depth to them and I wish I'd known more before I started this assignment because I really could've done something more, as I can be a slow learner.