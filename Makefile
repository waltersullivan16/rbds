CC = g++ -std=c++11 

planar: planar.o
	$(CC) $(CCFLAGS) -o planar planar.o -pthread

planar.o: planar.cpp
	$(CC) $(CCFLAGS) -c planar.cpp -pthread
