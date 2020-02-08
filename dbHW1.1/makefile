

# *****************************************************
# Variables to control Makefile operation

CXX = g++
CXXFLAGS = -Wall -g -std=c++17
PATH = lib/
# ****************************************************
# Targets needed to bring the executable up to date

main: main.o Manager.o DataBase.o Table.o
	$(CXX) $(CXXFLAGS) -o main main.o Manager.o DataBase.o Table.o

main.o: main.cpp $(PATH)Manager.h $(PATH)DataBase.h $(PATH)Table.h
	$(CXX) $(CXXFLAGS) -c main.cpp
    
Table.o: $(PATH)Table.h $(PATH)Table.cpp
	$(CXX) $(CXXFLAGS) -c $(PATH)Table.cpp

DataBase.o: $(PATH)DataBase.h $(PATH)Table.h $(PATH)DataBase.cpp
	$(CXX) $(CXXFLAGS) -c $(PATH)DataBase.cpp

Manager.o: $(PATH)Manager.h $(PATH)DataBase.h $(PATH)Table.h $(PATH)Manager.cpp
	$(CXX) $(CXXFLAGS) -c $(PATH)Manager.cpp
clean:
	-rm *.o
	